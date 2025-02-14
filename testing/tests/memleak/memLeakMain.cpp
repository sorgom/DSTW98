//  ============================================================
//  main with memory leak
//  ============================================================
//  created by Manfred Sorgo
#include <BAS/coding.h>

int main(int argc, char**)
{
    if (argc > 1)
    {
        CHAR* p = new CHAR[100];
        use(p);
    }
    return 0;
}
