@echo off
rem ========================================================================
rem Bullseye coverage: build and run module tests (requires VS shell)
rem Jenkins version
rem - one script for all
rem - no options
rem - no clean
rem - exits with error if coverage minimal values are not met
rem ========================================================================
SETLOCAL
rem determine relevant directories
cd /d %~dp0
set myDir=%cd%
cd ..
set makeDir=%cd%
cd ..
set dstwDir=%cd%
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
set covcopt=--srcdir %dstwDir% --macro

rem exclude file generated with coverage browser
set excludeFile=%myDir%\_exclude.txt
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

echo - build
rem turn off coverage instrumentation
rem it is not necessary to exclude parts from coverage instrumentation
rem but makes sense with test environment and CppUTest framework
cov01 -q --off
%vsCall% -t:testenv
set elevel=%errorlevel%
if %elevel% NEQ 0 goto end

rem activate coverage instrumentation
rem coverage instrumented build:
rem application and tests
cov01 -q --on
%vsCall% -t:"moduletests,moduletestsIL"
set elevel=%errorlevel%
if %elevel% NEQ 0 goto end

if not exist %covfile% (
    echo %covfile% not found
    set elevel=1
    goto end
)

echo - run
rem rewind coverage file if it was not removed before
covclear -q

%exeDir%\moduletests.exe -b -v
set elevel=%errorlevel%
if %elevel% NEQ 0 goto end

for %%t in (moduletests moduletestsIL) do (
    echo -- %%t
    %exeDir%\%%t.exe -b -v
    set elevel=%errorlevel%
    if %elevel% NEQ 0 goto end
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

covdir -q --checkmin %covMin% -f %covfile%
set elevel=%errorlevel%
set _result=passed
if %elevel% NEQ 0 (
    set _result=failed
    covbr -qu -f %covfile% > %todoTxt%
)
echo covmin %covMin% %_result% >> %report%

type %report%

echo.
echo to clean the project use:
echo %vsCall% -t:Clean

:end
rem restore previous instrumentation state
cov01 -q --pop
exit /b %elevel%
