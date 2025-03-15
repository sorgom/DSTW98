@echo off
rem ========================================================================
rem Bullseye coverage: generate md file
rem ========================================================================
SETLOCAL
set _me=%~n0
call %~dp0_setup.cmd

set md=%dstwDir%\testing\coverage_bullseye.md
set srcs=modTests.cov sysTests.cov

set trg=merged.cov
set covMin=100,100

cd /d %buildDir%

for %%s in (%srcs%) do (
    if not exist %%s (
        echo not found: %%s
        exit /b 1
    )
)
DEL /Q %trg% >NUL 2>&1

covmerge -qcf %trg% %srcs%

echo # current bullseye coverage > %md%
echo %DATE% >> %md%

for %%s in (%srcs% %trg%) do (
    echo. >> %md%
    echo ### %%s >> %md%
    echo ``` >> %md%
    covdir -q --by-name -f %%s >> %md%
    echo ``` >> %md%
)

set result=failed
covdir -q --checkmin %covMin% -f %trg%
if %errorlevel% == 0 set result=passed
echo. >> %md%
echo covmin %covMin% %result% >> %md%

type %md%
