# valgrind report
2025-03-03

## TEST: memory leaked app
```
==5946== Memcheck, a memory error detector
==5946== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==5946== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==5946== Command: /git/DSTW98/build/linux/memleak/memleak
==5946==
==5946==
==5946== HEAP SUMMARY:
==5946==     in use at exit: 100 bytes in 1 blocks
==5946==   total heap usage: 2 allocs, 1 frees, 72,804 bytes allocated
==5946==
==5946== 100 bytes in 1 blocks are definitely lost in loss record 1 of 1
==5946==    at 0x484A2F3: operator new[](unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==5946==    by 0x10918D: ??? (in /mnt/c/git/DSTW98/build/linux/memleak/memleak)
==5946==    by 0x4AB6D8F: (below main) (libc_start_call_main.h:58)
==5946==
==5946== LEAK SUMMARY:
==5946==    definitely lost: 100 bytes in 1 blocks
==5946==    indirectly lost: 0 bytes in 0 blocks
==5946==      possibly lost: 0 bytes in 0 blocks
==5946==    still reachable: 0 bytes in 0 blocks
==5946==         suppressed: 0 bytes in 0 blocks
==5946==
==5946== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

## TEST: runtime no action
```
==5948== Memcheck, a memory error detector
==5948== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==5948== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==5948== Command: /git/DSTW98/build/linux/ci/dstw_runtime
==5948==
ERR: 0
==5948==
==5948== HEAP SUMMARY:
==5948==     in use at exit: 0 bytes in 0 blocks
==5948==   total heap usage: 2 allocs, 2 frees, 76,800 bytes allocated
==5948==
==5948== All heap blocks were freed -- no leaks are possible
==5948==
==5948== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## TEST: runtime read
```
==5949== Memcheck, a memory error detector
==5949== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==5949== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==5949== Command: /git/DSTW98/build/linux/ci/dstw_runtime X
==5949==
ERR: 0
==5949==
==5949== HEAP SUMMARY:
==5949==     in use at exit: 0 bytes in 0 blocks
==5949==   total heap usage: 4 allocs, 4 frees, 85,464 bytes allocated
==5949==
==5949== All heap blocks were freed -- no leaks are possible
==5949==
==5949== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## TEST: runtime read, run, stop
```
==5950== Memcheck, a memory error detector
==5950== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==5950== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==5950== Command: /git/DSTW98/build/linux/ci/dstw_runtime X X
==5950==
listen: 8081
listen: 8082
listen: 8083
ERR: 0
==5950==
==5950== HEAP SUMMARY:
==5950==     in use at exit: 0 bytes in 0 blocks
==5950==   total heap usage: 4 allocs, 4 frees, 85,464 bytes allocated
==5950==
==5950== All heap blocks were freed -- no leaks are possible
==5950==
==5950== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## TEST: runtime read, run, system tests, stop
```
==5954== Memcheck, a memory error detector
==5954== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==5954== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==5954== Command: /git/DSTW98/build/linux/ci/dstw_runtime X X
==5954==
TEST(SYST_01, T01)
STEP(PRE)
STEP(1) send ping telegram
STEP(2) process GUI commands
STEP(2.1)
STEP(2.2)
STEP(2.3)
STEP(2.4)
STEP(2.5)
STEP(2.6)
STEP(3) process field telegrams
STEP(3.1)
STEP(3.2)
STEP(3.3)
STEP(3.4)
STEP(3.5)
STEP(3.6)
STEP(4) process reGui command via Ctrl
 - 0 ms

OK (1 tests, 1 ran, 38 checks, 0 ignored, 0 filtered out, 0 ms)

listen: 8081
listen: 8082
listen: 8083
ERR: 0
==5954==
==5954== HEAP SUMMARY:
==5954==     in use at exit: 0 bytes in 0 blocks
==5954==   total heap usage: 4 allocs, 4 frees, 85,464 bytes allocated
==5954==
==5954== All heap blocks were freed -- no leaks are possible
==5954==
==5954== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
