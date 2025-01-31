@echo off
if "%_me%" == "" exit /b 1
rem ========================================================================
rem Bullseye coverage: reporting
rem ========================================================================

del /Q %buildCtrl% >NUL 2>&1

if exist %testReport% (
    echo - test errors
    type %testReport%
    exit /b 1
)

if %_update% exit /b 0

set covMin=%minFunctionCov%,%minDecisionCov%

covselect -qd --import %excludeFile%

if %_genhtml% (
    echo - html
    covhtml -q --allNum %covHtmlDir%
)
cd %dstwDir%
if %_gentodo% (
    echo - todo
    covbr -qu --srcdir . > %covTodoTxt%
    %pyDir%\covbr2html\covbr2html.py -co %myReportsDir% %covTodoTxt%
)
if %_genmd% call %myDir%\_cov2md.cmd

echo - report

echo ### %_me% > %covCtrl%
echo ``` >> %covCtrl%
call covdir -q --by-name --srcdir . >> %covCtrl%

set _result=failed
call covdir -q --checkmin %covMin%
if %errorlevel% == 0 set _result=passed
echo covmin %covMin% %_result% >> %covCtrl%
echo ``` >> %covCtrl%
type %covCtrl%
