@echo off
SETLOCAL

cd /d %~dp0
set myDir=%cd%
cd ..
set dstwDir=%cd%

set image=ubuntu_env:0.1
set mounts=--mount type=bind,source=%dstwDir%,target=/dstw
set portsmap=-p 127.0.0.1:8081:8091/tcp -p 127.0.0.1:8082:8092/tcp -p 127.0.0.1:8083:8093/tcp

docker run -it --rm --name=dstw %mounts% %portsmap% %image%
