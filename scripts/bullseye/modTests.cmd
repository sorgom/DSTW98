@echo off
rem ========================================================================
rem Bullseye coverage: build and run module tests (requires VS shell)
rem ========================================================================
SETLOCAL
set _me=%~n0
call %~dp0_start.cmd %*
if %errorlevel% neq 0 goto end

cov01 -q --on
%vsCall% -t:"moduletests,moduletestsIL" >> %buildLog% 2>&1
if %errorlevel% NEQ 0 goto end

if not exist %covfile% (
    echo %covfile% not found
    goto end
)

del /Q %buildLog% >NUL 2>&1

covclear -q

echo - run
for %%t in (moduletests moduletestsIL) do (
    %exeDir%\%%t.exe
    if %errorlevel% NEQ 0 goto end
)

covselect -qd --import %excludeFile%
covdir -q --by-name

:end
cov01 -q --pop
