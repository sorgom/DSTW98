@echo off
SETLOCAL

cd /d %~dp0
set myDir=%cd%
cd ..
set dstwDir=%cd%

set image=ubuntu_env:0.1
set mounts=--mount type=bind,source=%dstwDir%,target=/dstw
set portsmap=-p 8080:8080/tcp -p 8081:8081/tcp -p 8082:8082/tcp

docker run -it --rm --name=dstw %mounts% %portsmap% %image%
