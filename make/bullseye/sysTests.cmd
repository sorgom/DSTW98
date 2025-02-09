@echo off
rem ========================================================================
rem Bullseye coverage: build and run module tests (requires VS shell)
rem ========================================================================

SETLOCAL
set _me=%~n0
call %~dp0_options.cmd %*
if %errorlevel% neq 0 exit /b 0

call %myDir%\_build.cmd --off "dstw_gen,dstw_stop,systemtests"
if %errorlevel% NEQ 0 exit /b 1

call %myDir%\_build.cmd --on dstw_runtime
if %errorlevel% NEQ 0 exit /b 1

cd /d %buildDir%

DEL /Q %projFile% >NUL 2>&1

set app=%exeDir%\dstw_runtime.exe

echo - launch application without data
%app% %projFile%

echo - gen data
%exeDir%\dstw_gen.exe %projFile% >NUL

echo - launch application without parameter
%app%%

set /a "myID=%random%"
set tmpFile=%buildDir%\run.%myID%.tmp

echo - launch application
start /B %myDir%\_runapp.cmd %app% %projFile%

timeout /t 2 /nobreak >NUL 2>&1
if not exist %tmpFile% (
    echo - application not started
    exit /b 1
)

echo - run tests
%exeDir%\systemtests.exe -b -v > %testReport% 2>&1
if %errorlevel% == 0 del %testReport%

echo - stop application ...
%exeDir%\dstw_stop.exe

:wait
timeout /t 1 /nobreak >NUL 2>&1
if exist %tmpFile% goto wait

call %myDir%\_report.cmd
