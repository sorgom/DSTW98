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
set buildDir=%dstwDir%\build
set reportsDir=%dstwDir%\reports
set vsDir=%dstwDir%\vs
set vsSolution=%vsDir%\DSTW.sln
set exeDir=%buildDir%\windows\bullseye

set buildLog=%reportsDir%\build_%_me%.txt
set covcopt=--srcdir %dstwDir% --macro
set covfile=%reportsDir%\%_me%.cov
set excludeFile=%myDir%\_exclude.txt

set vsCall=msbuild -m %vsSolution% -p:configuration=bullseye
set projFile=dstw.proj
