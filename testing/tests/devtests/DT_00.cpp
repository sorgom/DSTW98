//  ============================================================
//  test of mocks
//  ============================================================
//  created by Manfred Sorgo

#include <testlib/CppUTest.h>
#include <TestSteps/TestSteps.h>
#include <codebase/BaseTypes.h>
#include <BAS/coding.h>
#include <codebase/Mem.h>

#include <iostream>

TEST_GROUP(DT_00)
{
protected:
    bool ok;
    inline void setup()
    {
        ok = true;
    }
    void check(bool cond, CONST_C_STRING ccond)
    {
        if (not cond)
        {
            std::cout << "check failed: " << ccond << '\n';
            ok = false;
        }
    }
};

#define STATIC_ASSERT(COND) check(COND, #COND);

//  call mock explicitly
TEST(DT_00, T01)
{
    STEP(1)
    #include <ifs/DataTypes.h>
}
