# how to build and run
## linux make / gcc
### simple make (make folder)
- list configurations
````shell
make$ make help
````
- clean and build a config
````shell
make$ make clean config=release
make$ make -j config=release
````
- find binaries in build folder
````shell
make$ cd ../build/linux/release
build/linux/release$ ls
````
### buildAndRun.sh
````shell
scripts$ ./buildAndRun.sh
````
### run gcov
````shell
scripts$ ./runGcov.sh
````
### buid & run system tests
````shell
scripts$ ./runSystemTests.sh
````
### buid & run valgrind tests
````shell
scripts$ ./runValgrind.sh
````
## msbuild / visual studio
- requires [premake5](https://premake.github.io/)

### create solution for your VS version
````shell
scripts> premake5 --help
scripts> premake5 vsNNNN
````
### just build
````shell
scripts> cd ../vs
vs> msbuild -m DSTW.sln -p:configuration=release
````
- find binaries in build/windows folder
````shell
vs> cd ../build/windows/release
build\windows\release> dir /B *.exe
````
### build & run system tests
````shell
scripts> runSystemTests.cmd
````
