@echo off
echo run > %tmpfile%
call %*
del /Q %tmpfile% 2>nul
exit 0
