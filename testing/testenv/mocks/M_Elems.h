//  ============================================================
//  numbered elements
//  ============================================================
//  created by Manfred Sorgo

#ifndef M_ELEMS_H
#define M_ELEMS_H

#include "M_Elem.h"
#include <testlib/TestArray.h>
#include <CFG/Setup.h>
#include <sstream>

namespace test
{
    typedef TestArray<M_Elem, CAPACITY> A_Elems;

    class M_Elems : public A_Elems
    {
    public:
        INSTANCE_DEC(M_Elems)

    private:
        M_Elems() : A_Elems()
        {
            std::ostringstream os;
            for (size_t n = 0; n < CAPACITY; ++n)
            {
                add(M_Elem(n));
            }
        }
    };

} // namespace

#endif // _H
