# valgrind report
2025-03-04

## TEST: memory leaked app
```
==35== Memcheck, a memory error detector
==35== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==35== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==35== Command: /dstw/build/linux/memleak/memleak
==35==
==35==
==35== HEAP SUMMARY:
==35==     in use at exit: 100 bytes in 1 blocks
==35==   total heap usage: 2 allocs, 1 frees, 73,828 bytes allocated
==35==
==35== 100 bytes in 1 blocks are definitely lost in loss record 1 of 1
==35==    at 0x48485C3: operator new[](unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==35==    by 0x10918D: ??? (in /dstw/build/linux/memleak/memleak)
==35==    by 0x4B051C9: (below main) (libc_start_call_main.h:58)
==35==
==35== LEAK SUMMARY:
==35==    definitely lost: 100 bytes in 1 blocks
==35==    indirectly lost: 0 bytes in 0 blocks
==35==      possibly lost: 0 bytes in 0 blocks
==35==    still reachable: 0 bytes in 0 blocks
==35==         suppressed: 0 bytes in 0 blocks
==35==
==35== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

## TEST: runtime no action
```
==37== Memcheck, a memory error detector
==37== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==37== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==37== Command: /dstw/build/linux/ci/dstw_runtime
==37==
ERR: 0
==37==
==37== HEAP SUMMARY:
==37==     in use at exit: 0 bytes in 0 blocks
==37==   total heap usage: 2 allocs, 2 frees, 77,824 bytes allocated
==37==
==37== All heap blocks were freed -- no leaks are possible
==37==
==37== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## TEST: runtime read
```
==38== Memcheck, a memory error detector
==38== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==38== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==38== Command: /dstw/build/linux/ci/dstw_runtime X
==38==
ERR: 0
==38==
==38== HEAP SUMMARY:
==38==     in use at exit: 0 bytes in 0 blocks
==38==   total heap usage: 4 allocs, 4 frees, 86,488 bytes allocated
==38==
==38== All heap blocks were freed -- no leaks are possible
==38==
==38== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## TEST: runtime read, run, stop
```
==39== Memcheck, a memory error detector
==39== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==39== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==39== Command: /dstw/build/linux/ci/dstw_runtime X X
==39==
listen: 8091
listen: 8092
listen: 8093
ERR: 0
==39==
==39== HEAP SUMMARY:
==39==     in use at exit: 0 bytes in 0 blocks
==39==   total heap usage: 4 allocs, 4 frees, 86,488 bytes allocated
==39==
==39== All heap blocks were freed -- no leaks are possible
==39==
==39== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## TEST: runtime read, run, system tests, stop
```
==43== Memcheck, a memory error detector
==43== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==43== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==43== Command: /dstw/build/linux/ci/dstw_runtime X X
==43==
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

listen: 8091
listen: 8092
listen: 8093
ERR: 0
==43==
==43== HEAP SUMMARY:
==43==     in use at exit: 0 bytes in 0 blocks
==43==   total heap usage: 4 allocs, 4 frees, 86,488 bytes allocated
==43==
==43== All heap blocks were freed -- no leaks are possible
==43==
==43== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
