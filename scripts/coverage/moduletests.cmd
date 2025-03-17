@echo off
SETLOCAL
cd /d %~dp0
set myDir=%cd%
cd ../..
set repoDir=%cd%
set buildDir=%repoDir%\build
set reportsDir=%repoDir%\reports
set vsDir=%repoDir%\vs
set exeDir=%buildDir%\windows\bullseye

set vsSolution=%vsDir%\DSTW.sln
set report=%reportsDir%\moduletests_coverage.txt
set todoTxt=%reportsDir%\moduletests_todo.txt
set covfile=%buildDir%\moduletests.cov

set covcopt=--srcdir %repoDir% --macro
set excludeFile=%myDir%\exclude.txt
set covMinima=100,100

set vsCall=msbuild -m %vsSolution% -p:configuration=bullseye

set elevel=0

md %buildDir% %reportsDir% >NUL 2>&1
DEL /Q %report% %todoTxt% >NUL 2>&1

cov01 -q --push

set clean=0
if not exist %covfile% set clean=1
if "%1" == "-c" set clean=1
if %clean% == 1 (
    %vsCall% -t:Clean
    DEL /Q %covfile% >NUL 2>&1
)

cov01 -q --off
%vsCall% -t:submodules
if %errorlevel% NEQ 0 goto err

cov01 -q --on
%vsCall% -t:"moduletests,moduletestsIL"
if %errorlevel% NEQ 0 goto err

if not exist %covfile% (
    echo %covfile% not found
    goto err
)

covclear -q
for %%t in (moduletests moduletestsIL) do (
    %exeDir%\%%t.exe
    if %errorlevel% NEQ 0 goto err
)

covselect -qd --import %excludeFile%

cd %buildDir%
covdir -q --by-name > %report%
type %report%

covdir -q --checkmin %covMinima%
set elevel=%errorlevel%
if %elevel% NEQ 0 covbr -qu -f %covfile% > %todoTxt%

:end
cov01 -q --pop
exit /b %elevel%

:err
set elevel=1
goto end
