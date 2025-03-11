@echo off
rem ========================================================================
rem Bullseye coverage: CLI options
rem ========================================================================
call %~dp0_setup.cmd %*

echo - setup
cov01 -q --push

if not exist %vsSolution% (
    echo %vsSolution% not found
    echo use premak5 vs... in make folder to generate it
    exit /b 1
)

del /Q %buildLog%>NUL 2>&1
md %reportsDir% >NUL 2>&1

set clean=0
if not exist %covfile% set clean=1
if "%1" == "-c" set clean=1

if %clean% == 1 (
    echo - clean
    del /Q %covfile% >NUL 2>&1
    %vsCall% -t:Clean >NUL
)

echo - build

cov01 -q --off
%vsCall% -t:testenv >> %buildLog% 2>&1
exit /b %errorlevel%
