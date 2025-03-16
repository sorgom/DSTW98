# how to build and run
## linux make / gcc
### simple make (make folder)
- list configurations
````shell
DSTW/make$> make help
````
- clean and build a config
````shell
DSTW/make$> make clean config=ci
DSTW/make$> make -j config=ci
````
- find binaries in build folder
````shell
DSTW/make$> cd ../build/linux/ci
DSTW/build/linux/bin$> ls
````
### buildAndRun.sh
````shell
DSTW/scripts$> ./buildAndRun.sh
````
### run gcov
````shell
DSTW/scripts$> ./runGcov.sh
````
### buid & run system tests
````shell
DSTW/scripts$> ./runSystemTests.sh
````
### buid & run valgrind tests
````shell
DSTW/scripts$> ./runValgrind.sh
````
## msbuild / visual studio
- requires [premake5](https://premake.github.io/)

### create solution for your VS version
````shell
DSTW\scripts> premake5 --help
DSTW\scripts> premake5 vsNNNN
````
### just build
````shell
DSTW\scripts> cd ../vs
DSTW\vs> msbuild -m DSTW.sln -p:configuration=ci
````
- find binaries in build/windows folder
````shell
DSTW\vs> cd ../build/windows/ci
DSTW\build\windows\ci> dir /B *.exe
````
### build & run system tests
````shell
DSTW\scripts> ./runSystemTests.cmd
````
