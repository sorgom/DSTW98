@echo off
rem ========================================================================
rem Bullseye coverage: build and run module tests (requires VS shell)
rem ========================================================================
SETLOCAL
set _me=%~n0
call %~dp0_options.cmd %*
if %errorlevel% neq 0 exit /b 0

call %myDir%\_build.cmd --on "moduletests,moduletestsIL"
if %errorlevel% NEQ 0 exit /b 1

if not exist %covfile% (
    echo %covfile% not found
    exit /b 1
)

rem rewind coverage file if it was not removed before
call covclear -q

echo - run
set elevel=0
for %%t in (moduletests moduletestsIL) do (
    echo -- %%t
    %exeDir%\%%t.exe -b -v >> %testLog% 2>&1
    if %elevel% NEQ 0 set /A elevel=elevel+1
)
if %elevel% == 0 del /Q %testLog%

call %myDir%\_report.cmd
