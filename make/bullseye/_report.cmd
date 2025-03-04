@echo off
if "%_me%" == "" exit /b 1
rem ========================================================================
rem Bullseye coverage: reporting
rem ========================================================================

del /Q %buildLog% >NUL 2>&1

if exist %testLog% (
    echo - test errors
    type %testLog%
    exit /b 1
)

covselect -qd --import %excludeFile%

cd %dstwDir%
if %_gentodo% (
    echo - todo
    covbr -qu --srcdir . > %covTodoTxt%
    %pyDir%\covbr2html\covbr2html.py -co %ReportsDir% %covTodoTxt%
)

echo - report
covdir -q --by-name --srcdir . >> %covLog%

type %covLog%
