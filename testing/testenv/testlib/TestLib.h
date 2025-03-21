//  ============================================================
//  basic test features
//  ============================================================
//  created by Manfred Sorgo

#ifndef TEST_LIB_H
#define TEST_LIB_H

#include <ifs/DataTypes.h>
#include <ifs/I_Elem.h>
#include <codebase/nocopy.h>

namespace test
{
    //  preset ComAddr for testing
    void genComAddr(ComAddr& cName, UINT32 num, CONST_C_STRING addr = "ELEM");

    const ComAddr& genComAddr(UINT32 num, CONST_C_STRING addr = "ELEM");

    inline bool operator==(const ComAddr& n1, const ComAddr& n2)
    {
        return std::memcmp(n1.chars, n2.chars, ComAddrSize) == 0;
    }

    //  avoid "not used" warning
    template<class T>
    void play(const T&)
    {}

    //  exchangeable non const reference
    template <class T>
    class Ref
    {
    public:
        inline Ref(T& obj):
            mPtr(&obj)
        {}
        inline T& ref() const
        {
            return *mPtr;
        }
        inline void set(T& ref)
        {
            mPtr = &ref;
        }
        NOCOPY(Ref)
        NODEF(Ref)
    private:
        T* mPtr;
    };

    //  check if element is of type T
    template <class T>
    inline bool istype(const I_Elem& elem)
    {
        return dynamic_cast<const T*>(&elem) != nullptr;
    }
    #define L_CHECK_ELEM_TYPE(TYPE, ELEM) L_CHECK_TRUE(istype<TYPE>(ELEM))
}

//  limits for test values
#ifndef _MSC_VER

    #ifndef UINT8_MAX
    #define UINT8_MAX 0xFF
    #endif

    #ifndef INT16_MIN
    #define INT16_MIN -0x7FFF
    #endif

    #ifndef INT16_MAX
    #define INT16_MAX 0x7FFF
    #endif

    #ifndef INT32_MIN
    #define INT32_MIN -0x7FFFFFFF
    #endif

    #ifndef INT32_MAX
    #define INT32_MAX 0x7FFFFFFF
    #endif
#endif

#endif // _H
