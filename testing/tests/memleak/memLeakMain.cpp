//  ============================================================
//  main with memory leak
//  ============================================================
//  created by Manfred Sorgo
#include <BAS/coding.h>

int main()
{
#ifdef MEM_LEAK
    CHAR* p = new CHAR[100];
    use(p);
#endif
    return 0;
}
