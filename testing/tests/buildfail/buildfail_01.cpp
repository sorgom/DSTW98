#ifdef STATIC_FAIL

#include <codebase/checks.h>
#include <BAS/StackArray.h>

// base
struct A
{
    int a;
};

// derived (bigger)
struct B : A
{
    int b;
};

// same size as A but not derived
struct C
{
    int c;
};

// failure: size check
SIZE_CHECK(B, sizeof(A))

void buildfail_01()
{
    StackArray<A, 1> s;

    B b;
    // failure: size check
    s.add(b);

    C c;
    // failure: not derived
    s.add(c);
}
#endif
