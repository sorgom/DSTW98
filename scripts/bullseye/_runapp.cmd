@echo off
if "%tmpFile%" == "" exit /b 1
rem ========================================================================
rem system tests: run app in background
rem ========================================================================
echo running > %tmpFile%
%*
rm -f %tmpFile%
exit 0
