//  ============================================================
//  base CppUTest test group
//  ============================================================
//  created by Manfred Sorgo

#ifndef TESTGROUPBASE_H
#define TESTGROUPBASE_H

#include <ifs/values.h>
#include <mocks/M_Instances.h>
#include <SYS/IL.h>
#include <testlib/TestLib.h>
#include <testlib/testValues.h>
#include <TestSteps/TestSteps.h>

namespace test
{
    class TestGroupBase : public Utest
    {
    protected:
        inline void teardown()
        {
            CHECK_N_CLEAR()
        }

    };

} // namespace
#endif // _H
