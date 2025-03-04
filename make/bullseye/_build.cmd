@echo off
if "%_me%" == "" exit /b 1
rem ========================================================================
rem Bullseye coverage: build step
rem ========================================================================

SETLOCAL
cov01 -q %1
shift

set elevel=0
echo -- %1
call %vsCall% -t:%1 >> %buildLog% 2>&1
set elevel=%errorlevel%
if %elevel% NEQ 0 echo - build error %1
cov01 -q --off
exit /b %elevel%
