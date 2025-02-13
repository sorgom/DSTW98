@echo off
if "%_me%" == "" exit /b 1
rem ========================================================================
rem Bullseye coverage: common setup
rem ========================================================================
cd /d %~dp0
set myDir=%cd%
cd ..
set makeDir=%cd%
cd ..
set dstwDir=%cd%
set buildDir=%cd%\build
set subsDir=%cd%\submodules
set reportsDir=%cd%\reports

set pyDir=%subsDir%\sompy
set vsSolution=%makeDir%\DSTW.sln
set exeDir=%buildDir%\windows\bullseye
set buildLog=%reportsDir%\build_%_me%.txt
set covLog=%reportsDir%\coverage_%_me%.txt
set testLog=%reportsDir%\test_errors_%_me%.txt

set covcopt=--srcdir %dstwDir% --macro
set covfile=%reportsDir%\%_me%.cov
set excludeFile=%myDir%\_exclude.txt
set covTodoTxt=%buildDir%\todo_%_me%.txt

set optsTxt=%myDir%\_options.txt
set vsCall=msbuild -m %vsSolution% -p:configuration=bullseye
set tmpCmd=%buildDir%\tmp.cmd
set projFile=dstw.proj

md %buildDir% >NUL 2>&1
