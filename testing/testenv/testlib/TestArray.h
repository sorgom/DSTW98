//  ============================================================
//  array for testing purposes
//  (no production code in test environment)
//  ============================================================
#ifndef TEST_ARRAY_H
#define TEST_ARRAY_H

#include <BAS/coding.h>
#include <cstring>

namespace test
{
    template <class T, size_t CAP>
    class TestArray
    {
    public:
        inline TestArray() : mSize(0) {}

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

        inline void add(const T& obj)
        {
            std::memcpy(mData[mSize++], &obj, sizeof(T));
        }

        inline void clear()
        {
            mSize = 0;
            std::memset(mData, 0, sizeof(mData));
        }

        NOCOPY(TestArray)
    private:
        typedef BYTE Segment[sizeof(T)];
        Segment mData[CAP];
        size_t mSize;
    };
} // namespace
#endif // H_
