#include <testlib/wait.h>

#ifdef _WIN32
#include <windows.h>
void wait(const UINT32 ms)
{
    Sleep(ms);
}

#else
#include <unistd.h>
void wait(const UINT32 ms)
{
    usleep(ms * 1000);
}

#endif
