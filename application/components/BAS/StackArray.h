//  ============================================================
//  defintion of interface I_Array to apply:
//  - bubble sort
//  - b-tree search
//  - uniqueness check / duplicates count
//  ============================================================
#ifndef STACK_ARRAY_H
#define STACK_ARRAY_H

#include <ifs/DataTypes.h>
#include <BAS/coding.h>
#include <cstring>
#include <new>

template <class T, size_t CAP>
class I_Array
{
public:
    inline static size_t capacity()
    {
        return CAP;
    }

    //  current number of objects
    virtual size_t size() const = 0;

    //  object access by position
    virtual const T& at(size_t pos) const = 0;

    inline bool hasSpace() const
    {
        return size() < CAP;
    }
};

template <class T, size_t CAP, size_t SIZE = sizeof(T)>
class StackArray :
    public I_Array<T, CAP>
{
public:
    inline StackArray() : mSize(0) {}

    inline size_t size() const
    {
        return mSize;
    }

    const T& at(size_t pos) const
    {
        return *reinterpret_cast<const T*>(mData[pos]);
    }

    T& at(size_t pos)
    {
        return *reinterpret_cast<T*>(mData[pos]);
    }

    template <class DT>
    inline const T& add(const DT& obj)
    {
        std::memcpy(mData[mSize++], &obj, sizeof(DT));
        return static_cast<const T&>(obj);
    }

    inline void clear()
    {
        mSize = 0;
    }

    inline const BYTE* data() const
    {
        return mData;
    }

    inline size_t dsize() const
    {
        return mSize * SIZE;
    }

    NOCOPY(StackArray)

protected:
    typedef BYTE Segment[SIZE];
    Segment mData[CAP];
    size_t mSize;
};

template <class T, size_t CAP, class KEY>
class StackIndex
{
public:
    typedef I_Array<T, CAP> Array;

    inline StackIndex(const Array& array) : mArray(array) {}

    bool index()
    {
        sort();
        return dupCnt() == 0;
    }

    inline void clear()
    {
        std::memset(mIdx, 0, sizeof(mIdx));
    }

    //  find data position by key
    //  requires that index() has been called once before
    const PosRes find(KEY key) const
    {
        bool found = false;
        size_t pos = 0;
        if (size() > 0)
        {
            size_t left = 0;
            size_t right = size() - 1;
            while ((left <= right) and (not found))
            {
                const int mid = left + (right - left) / 2;
                const KEY km = getKey(mid);
                if (key > km)
                {
                    left = mid + 1;
                }
                else if (km > key)
                {
                    if (mid == 0)
                    {
                        break;
                    }
                    right = mid - 1;
                }
                else
                {
                    found = true;
                    pos = mIdx[mid];
                }
            }
        }
        return PosRes(found, pos);
    }

protected:
    virtual KEY getKey(const T&) const = 0;

private:
    const Array& mArray;
    size_t mIdx[CAP];

    inline size_t size() const
    {
        return mArray.size();
    }

    inline KEY getKey(size_t pos) const
    {
        return getKey(mArray.at(mIdx[pos]));
    }

    inline bool gt(size_t a, size_t b) const
    {
        return getKey(a) > getKey(b);
    }

    void sort()
    {
        for (size_t n = 0; n < size(); ++n)
        {
            mIdx[n] = n;
        }
        bool swapped = true;
        for (size_t n = size(); swapped and n > 1; --n)
        {
            swapped = false;
            for (size_t a = 0, b = 1; b < n; ++a, ++b)
            {
                if (gt(a, b))
                {
                    const size_t t = mIdx[a];
                    mIdx[a] = mIdx[b];
                    mIdx[b] = t;
                    swapped = true;
                }
            }
        }
    }
    size_t dupCnt()
    {
        size_t dups = 0;
        for (size_t a = 0, b = 1; b < size(); ++a, ++b)
        {
            if (not gt(b, a))
            {
                ++dups;
            }
        }
        return dups;
    }

    NODEF(StackIndex)
    NOCOPY(StackIndex)
};
#endif // H_
