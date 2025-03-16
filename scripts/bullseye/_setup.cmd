@echo off
if "%_me%" == "" exit /b 1
rem ========================================================================
rem Bullseye coverage: common setup
rem ========================================================================
cd /d %~dp0
set myDir=%cd%
cd ../..
set repoDir=%cd%
set buildDir=%repoDir%\build
set vsDir=%repoDir%\vs
set vsSolution=%vsDir%\DSTW.sln
set exeDir=%buildDir%\windows\bullseye

set buildLog=%buildDir%\build_%_me%.txt
set covcopt=--srcdir %repoDir% --macro
set covfile=%buildDir%\%_me%.cov
set excludeFile=%myDir%\_exclude.txt

set tmpFile=%buildDir%\%_me%.tmp
set vsCall=msbuild -m %vsSolution% -p:configuration=bullseye
set projFile=dstw.proj
