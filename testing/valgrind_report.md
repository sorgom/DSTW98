# valgrind report
2025-03-05

## TEST: memory leaked app
```
==36== Memcheck, a memory error detector
==36== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==36== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==36== Command: /git/DSTW98/build/linux/memleak/memleak
==36==
==36==
==36== HEAP SUMMARY:
==36==     in use at exit: 100 bytes in 1 blocks
==36==   total heap usage: 2 allocs, 1 frees, 73,828 bytes allocated
==36==
==36== 100 bytes in 1 blocks are definitely lost in loss record 1 of 1
==36==    at 0x48485C3: operator new[](unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==36==    by 0x10918D: ??? (in /git/DSTW98/build/linux/memleak/memleak)
==36==    by 0x4B051C9: (below main) (libc_start_call_main.h:58)
==36==
==36== LEAK SUMMARY:
==36==    definitely lost: 100 bytes in 1 blocks
==36==    indirectly lost: 0 bytes in 0 blocks
==36==      possibly lost: 0 bytes in 0 blocks
==36==    still reachable: 0 bytes in 0 blocks
==36==         suppressed: 0 bytes in 0 blocks
==36==
==36== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

## TEST: runtime no action
```
==38== Memcheck, a memory error detector
==38== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==38== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==38== Command: /git/DSTW98/build/linux/ci/dstw_runtime
==38==
ERR: 0
==38==
==38== HEAP SUMMARY:
==38==     in use at exit: 0 bytes in 0 blocks
==38==   total heap usage: 2 allocs, 2 frees, 77,824 bytes allocated
==38==
==38== All heap blocks were freed -- no leaks are possible
==38==
==38== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## TEST: runtime read
```
==39== Memcheck, a memory error detector
==39== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==39== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==39== Command: /git/DSTW98/build/linux/ci/dstw_runtime X
==39==
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

## TEST: runtime read, run, stop
```
==40== Memcheck, a memory error detector
==40== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==40== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==40== Command: /git/DSTW98/build/linux/ci/dstw_runtime X X
==40==
listen: 8091
listen: 8092
listen: 8093
ERR: 0
==40==
==40== HEAP SUMMARY:
==40==     in use at exit: 0 bytes in 0 blocks
==40==   total heap usage: 4 allocs, 4 frees, 86,488 bytes allocated
==40==
==40== All heap blocks were freed -- no leaks are possible
==40==
==40== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## TEST: runtime read, run, system tests, stop
```
==44== Memcheck, a memory error detector
==44== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==44== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==44== Command: /git/DSTW98/build/linux/ci/dstw_runtime X X
==44==
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
==44==
==44== HEAP SUMMARY:
==44==     in use at exit: 0 bytes in 0 blocks
==44==   total heap usage: 4 allocs, 4 frees, 86,488 bytes allocated
==44==
==44== All heap blocks were freed -- no leaks are possible
==44==
==44== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
