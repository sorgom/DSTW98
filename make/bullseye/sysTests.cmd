@echo off
rem ========================================================================
rem Bullseye coverage: build and run module tests (requires VS shell)
rem ========================================================================

SETLOCAL
set _me=%~n0
call %~dp0_options.cmd %*
if %errorlevel% neq 0 goto err

cov01 -q --off
%vsCall% -t:"dstw_gen,dstw_stop,systemtests" >> %buildLog% 2>&1
if %errorlevel% NEQ 0 goto err

cov01 -q --on
%vsCall% -t:dstw_runtime >> %buildLog% 2>&1
if %errorlevel% NEQ 0 goto err

del /Q %buildLog% >NUL 2>&1

covclear -q

cd /d %buildDir%

DEL /Q %projFile% >NUL 2>&1

set app=%exeDir%\dstw_runtime.exe

echo - launch with no action
%app%

echo - launch application with read but no data
%app% X

echo - gen data
%exeDir%\dstw_gen.exe >NUL

echo - launch application with read and data
%app%%

set /a "myID=%random%"
set tmpFile=%buildDir%\run.%myID%.tmp

echo - launch application with read and loop
start /B %myDir%\_runapp.cmd %app% X X

timeout /t 2 /nobreak >NUL 2>&1
if not exist %tmpFile% (
    echo - application not started
    goto err
)

echo - run tests
%exeDir%\systemtests.exe
if %errorlevel% neq 0 goto err

echo - stop application ...
%exeDir%\dstw_stop.exe

:wait
timeout /t 1 /nobreak >NUL 2>&1
if exist %tmpFile% goto wait

covselect -qd --import %excludeFile%
covdir -q --by-name --srcdir .

:err
cov01 -q --pop
