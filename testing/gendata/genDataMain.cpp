//  ============================================================
//  sample proj data generator
//  ============================================================
//  created by Manfred Sorgo

#include <testlib/GenProjData.h>

int main()
{
    test::GenProjData<> data("dstw.proj");
    data.dump();
    return 0;
}
