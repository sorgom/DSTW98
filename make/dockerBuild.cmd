@echo off
SETLOCAL

cd /d %~dp0
docker build -t ubuntu_env:0.1 .
