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
#include <type_traits>


//  basic array interface
template <class T, size_t CAP>
class I_Array
{
public:
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
    inline StackArray() : mData{}, mSize(0) {}

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

    //  add element by copying an object
    template <class DT>
    inline void cpy(const DT& obj)
    {
        static_assert(sizeof(DT) <= SIZE);
        static_assert(std::is_base_of<T, DT>::value);
        std::memcpy(mData[mSize++], &obj, sizeof(DT));
    }

    //  add element with type and construction arguments
    template <class DT, typename... Args>
    inline void add(const Args&... args)
    {
        static_assert(sizeof(DT) <= SIZE);
        static_assert(std::is_base_of<T, DT>::value);
        new (mData[mSize++]) DT(args...);
    }

    inline void clear()
    {
        mSize = 0;
        std::memset(mData, 0, sizeof(mData));
    }

    NOCOPY(StackArray)
private:
    using Segment = BYTE[SIZE];
    Segment mData[CAP];
    size_t mSize;
};

template <class T, size_t CAP, class KEY>
class StackIndex
{
protected:
    virtual KEY getKey(const T&) const = 0;

public:
    using Array = I_Array<T, CAP>;

    inline StackIndex(const Array& array) : mArray(array) {}

    bool index()
    {
        sort();
        return dupCnt() == 0;
    }

    //  find data position by key
    //  requires that sort() or index() has been called once before
    const PosRes find(KEY key) const
    {
        return search(key);
    }

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

    const PosRes search(KEY key) const
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

    NODEF(StackIndex)
    NOCOPY(StackIndex)
};
#endif // H_
