//  ============================================================
//  main with memory leak
//  ============================================================
//  created by Manfred Sorgo
#include <testlib/TestLib.h>

int main()
{
#ifdef MEM_LEAK
    CHAR* p = new CHAR[100];
    test::play(p);
#endif
    return 0;
}
