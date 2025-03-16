# valgrind report
2025-03-16

## TEST: memory leaked app
```
====== Memcheck, a memory error detector
====== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
====== Using Valgrind-3.19.0 and LibVEX; rerun with -h for copyright info
====== Command: /git/DSTW98/build/linux/memleak/memleak
======
======
====== HEAP SUMMARY:
======     in use at exit: 100 bytes in 1 blocks
======   total heap usage: 2 allocs, 1 frees, 72,804 bytes allocated
======
====== 100 bytes in 1 blocks are definitely lost in loss record 1 of 1
======    at 0x484320F: operator new[](unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
======    by 0x10914A: ??? (in /git/DSTW98/build/linux/memleak/memleak)
======    by 0x4A96249: (below main) (libc_start_call_main.h:58)
======
====== LEAK SUMMARY:
======    definitely lost: 100 bytes in 1 blocks
======    indirectly lost: 0 bytes in 0 blocks
======      possibly lost: 0 bytes in 0 blocks
======    still reachable: 0 bytes in 0 blocks
======         suppressed: 0 bytes in 0 blocks
======
====== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

## TEST: runtime no action
```
====== Memcheck, a memory error detector
====== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
====== Using Valgrind-3.19.0 and LibVEX; rerun with -h for copyright info
====== Command: /git/DSTW98/build/linux/ci/dstw_runtime
======
ERR: 0
======
====== HEAP SUMMARY:
======     in use at exit: 0 bytes in 0 blocks
======   total heap usage: 2 allocs, 2 frees, 76,800 bytes allocated
======
====== All heap blocks were freed -- no leaks are possible
======
====== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## TEST: runtime read
```
====== Memcheck, a memory error detector
====== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
====== Using Valgrind-3.19.0 and LibVEX; rerun with -h for copyright info
====== Command: /git/DSTW98/build/linux/ci/dstw_runtime X
======
ERR: 0
======
====== HEAP SUMMARY:
======     in use at exit: 0 bytes in 0 blocks
======   total heap usage: 4 allocs, 4 frees, 85,464 bytes allocated
======
====== All heap blocks were freed -- no leaks are possible
======
====== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## TEST: runtime read, run, stop
```
====== Memcheck, a memory error detector
====== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
====== Using Valgrind-3.19.0 and LibVEX; rerun with -h for copyright info
====== Command: /git/DSTW98/build/linux/ci/dstw_runtime X X
======
ERR: 0
======
====== HEAP SUMMARY:
======     in use at exit: 0 bytes in 0 blocks
======   total heap usage: 4 allocs, 4 frees, 85,464 bytes allocated
======
====== All heap blocks were freed -- no leaks are possible
======
====== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## TEST: runtime read, run, system tests, stop
```
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

====== Memcheck, a memory error detector
====== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
====== Using Valgrind-3.19.0 and LibVEX; rerun with -h for copyright info
====== Command: /git/DSTW98/build/linux/ci/dstw_runtime X X
======
ERR: 0
======
====== HEAP SUMMARY:
======     in use at exit: 0 bytes in 0 blocks
======   total heap usage: 4 allocs, 4 frees, 85,464 bytes allocated
======
====== All heap blocks were freed -- no leaks are possible
======
====== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
