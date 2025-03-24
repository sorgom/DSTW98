# how to build and run
## linux make / gcc
### simple make (make folder)
- list configurations
````shell
DSTW98/make$> make help
````
- clean and build a config
````shell
DSTW98/make$> make clean config=release
DSTW98/make$> make -j config=release
````
- find binaries in build folder
````shell
DSTW98/make$> cd ../build/linux/release
DSTW98/build/linux/release$> ls
````
### buildAndRun.sh
````shell
DSTW98/scripts$> ./buildAndRun.sh
````
### run gcov
````shell
DSTW98/scripts$> ./runGcov.sh
````
### buid & run system tests
````shell
DSTW98/scripts$> ./runSystemTests.sh
````
### buid & run valgrind tests
````shell
DSTW98/scripts$> ./runValgrind.sh
````
## msbuild / visual studio
- requires [premake5](https://premake.github.io/)

### create solution for your VS version
````shell
DSTW98\scripts> premake5 --help
DSTW98\scripts> premake5 vsNNNN
````
### just build
````shell
DSTW98\scripts> cd ../vs
DSTW98\vs> msbuild -m DSTW.sln -p:configuration=release
````
- find binaries in build/windows folder
````shell
DSTW98\vs> cd ../build/windows/release
DSTW98\build\windows\release> dir /B *.exe
````
### build & run system tests
````shell
DSTW98\scripts> runSystemTests.cmd
````
