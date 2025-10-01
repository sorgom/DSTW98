@echo off
SETLOCAL
cd /d %~dp0
set myDir=%cd%
cd ../..
set repoDir=%cd%
set buildDir=%repoDir%\build
set compDir=%repoDir%\application\components
set reportsDir=%repoDir%\reports
set vsDir=%repoDir%\vs
set exeDir=%buildDir%\windows\release

set vsSolution=%vsDir%\DSTW.sln
set report=%reportsDir%\moduletests_coverage.txt
set todoTxt=%reportsDir%\moduletests_todo.txt
set COVFILE=%buildDir%\moduletests.cov

set COVCOPT=--srcdir %compDir% --macro
set excludeFile=%myDir%\exclude.txt
set projectCoverageGoal=100,98

set buildCall=msbuild -m %vsSolution% -p:configuration=release

set elevel=0

md %buildDir% %reportsDir% >NUL 2>&1
DEL /Q %report% %todoTxt% >NUL 2>&1

cov01 -q --push

set clean=0
if not exist %COVFILE% set clean=1
if "%1" == "-c" set clean=1
if %clean% == 1 (
    %buildCall% -t:Clean
    DEL /Q %COVFILE% >NUL 2>&1
)

cov01 -q --on
%buildCall% -t:moduletests
if %errorlevel% NEQ 0 goto err

if not exist %COVFILE% (
    echo %COVFILE% not found
    goto err
)

covclear -q
%exeDir%\moduletests.exe
if %errorlevel% NEQ 0 goto err

covselect -qd --import %excludeFile%

cd %buildDir%
covdir -q --by-name > %report%
type %report%

covdir -q --checkmin %projectCoverageGoal%
set elevel=%errorlevel%

covdir -q --checkmin 100,100
if %errorlevel% NEQ 0 covbr -qu > %todoTxt%

:end
cov01 -q --pop
exit /b %elevel%

:err
set elevel=1
goto end
