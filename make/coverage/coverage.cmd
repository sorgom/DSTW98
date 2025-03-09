@echo off
SETLOCAL
cd /d %~dp0
set myDir=%cd%
cd ..
set makeDir=%cd%
cd ..
set repoDir=%cd%
set buildDir=%cd%\build
set reportsDir=%cd%\reports
set exeDir=%buildDir%\windows\bullseye

rem determine relevant files
set vsSolution=%makeDir%\DSTW.sln
set report=%reportsDir%\coverage.txt
set todoTxt=%reportsDir%\todo.txt
rem set coverage file (%covfile% is evaluated by bullseye)
set covfile=%buildDir%\coverage.cov

rem setup coverage behavior (%covcopt% is evaluated by bullseye)
rem - top level directory for coverage output
rem - macro instrumentation on
set covcopt=--srcdir %repoDir% --macro

rem exclude file generated with coverage browser
set excludeFile=%myDir%\exclude.txt
rem coverage minimal values (otherwise script returns error)
rem (function,decision in %)
set covMin=100,100

rem msbuild call
rem could be called with any configuration
rem but it makes sense to separate instrumented and non instrumented builds
rem in the solution file
set vsCall=msbuild -m %vsSolution% -p:configuration=bullseye

set elevel=0

md %buildDir% %reportsDir% >NUL 2>&1

rem save current instrumentation state
cov01 -q --push

set clean=0
if not exist %covfile% set clean=1
if "%1" == "-c" set clean=1

if %clean% == 1 (
    echo - clean
    %vsCall% -t:Clean
    DEL /Q %covfile% >NUL 2>&1
)

rem activate coverage instrumentation
rem coverage instrumented build:
rem application and tests
cov01 -q --on
%vsCall% -t:"moduletests,moduletestsIL"
if %errorlevel% NEQ 0 goto err

if not exist %covfile% (
    echo %covfile% not found
    goto err
)

echo - run
rem rewind coverage file if it was not removed before
covclear -q
for %%t in (moduletests moduletestsIL) do (
    %exeDir%\%%t.exe
    if %errorlevel% NEQ 0 goto err
)

echo - report
rem exclude parts from coverage report
rem by exclude file generated using coverage browser
covselect -qd --import %excludeFile%

rem bullseye reporting is a bit crappy
rem as far as relative paths are concerned
rem so we have to change the directory
rem to where the coverage file is
rem to get a decent looking report
cd %buildDir%
covdir -q --by-name > %report%
type %report%

covdir -q --checkmin %covMin% -f %covfile%
if %errorlevel% NEQ 0 covbr -qu -f %covfile% > %todoTxt%

:end
rem restore previous instrumentation state
cov01 -q --pop
exit /b %elevel%

:err
set elevel=1
goto end
