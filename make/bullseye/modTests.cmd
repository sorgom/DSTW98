@echo off
rem ========================================================================
rem Bullseye coverage: build and run module tests (requires VS shell)
rem ========================================================================
SETLOCAL
set _me=%~n0
call %~dp0_options.cmd %*
if %errorlevel% neq 0 goto err

cov01 -q --on
%vsCall% -t:"moduletests,moduletestsIL" >> %buildLog% 2>&1
if %errorlevel% NEQ 0 goto err

if not exist %covfile% (
    echo %covfile% not found
    goto err
)

del /Q %buildLog% >NUL 2>&1

covclear -q

echo - run
for %%t in (moduletests moduletestsIL) do (
    %exeDir%\%%t.exe
    if %errorlevel% NEQ 0 goto err
)

covselect -qd --import %excludeFile%
covdir -q --by-name --srcdir .

:err
cov01 -q --pop
