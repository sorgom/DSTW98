@echo off
rem ========================================================================
rem Bullseye coverage: build and run system tests (requires VS shell)
rem ========================================================================

SETLOCAL
set _me=%~n0
call %~dp0_start.cmd %*
if %errorlevel% neq 0 goto end

cov01 -q --off
%vsCall% -t:"dstw_gen,dstw_stop,systemtests" >> %buildLog% 2>&1
if %errorlevel% NEQ 0 goto end

cov01 -q --on
%vsCall% -t:dstw_runtime >> %buildLog% 2>&1
if %errorlevel% NEQ 0 goto end

del /Q %buildLog% >NUL 2>&1

covclear -q

DEL /Q %projFile% >NUL 2>&1

set app=%exeDir%\dstw_runtime.exe

echo - launch with no action
%app%

echo - launch application with read but no data
%app% X

echo - gen data
%exeDir%\dstw_gen.exe >NUL

echo - launch application with read and data
%app% X

set /a "myID=%random%"
set tmpFile=%buildDir%\run.%myID%.tmp

echo - launch application with read and loop
start /B %myDir%\_runapp.cmd %app% X X

timeout /t 2 /nobreak >NUL 2>&1
if not exist %tmpFile% (
    echo - application not started
    goto end
)

echo - run tests
%exeDir%\systemtests.exe -b
if %errorlevel% neq 0 goto end

echo - stop application ...
%exeDir%\dstw_stop.exe

:wait
timeout /t 1 /nobreak >NUL 2>&1
if exist %tmpFile% goto wait

covselect -qd --import %excludeFile%
covdir -q --by-name

:end
cov01 -q --pop
