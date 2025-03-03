@echo off
rem ====================================
rem run system tests in windows
rem ====================================
rem created by ChatGPT
SETLOCAL
cd /d %~dp0
set myDir=%cd%
cd ..
set buildDir=%cd%\build
set bindir=windows\ci

cd %myDir%
echo - build
msbuild DSTW.sln -p:configuration=ci -t:dstw_gen,dstw_runtime,systemtests,dstw_stop >NUL
if %errorlevel% neq 0 exit /b %errorlevel%

set tmpfile=tmp_%random%.txt
del /Q %tmpfile% 2>nul

cd %buildDir%
echo - run
rem gen required proj data file
%binDir%\dstw_gen.exe
rem start app in background
start /B %myDir%\runSub.cmd %binDir%\dstw_runtime.exe X
timeout /t 2 /nobreak >NUL 2>&1
if not exist %tmpFile% (
    echo - application not started
    exit /b 1
)
rem run tests
%binDir%\systemtests.exe -b -v
set ret=%errorlevel%
rem stop app anyway
%binDir%\dstw_stop.exe
:wait
timeout /t 1 /nobreak >NUL
if exist %tmpfile% goto wait

exit /b %ret%
