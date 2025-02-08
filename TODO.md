### doc
-   mocking image

### coverage
-   module tests (V)
    -   complete Mapper
    -   premake: apply decent CAPACITY (5 times all types)
-   merge results

### systemtests
-   main
    -   Ctrl loop (V)
-   gen_data
    - parameter n
    - -h
-   sleep by select
-   use GenProjData to run tests

### gcov

### vscode
-   white preview

### PC setup
-   StarUML
-   move linux?
-   chrome for sombeam
-   valgrind


# Transfer from C++ 2017 to C++98
## 98
-   replace standard in premake (V)

## coding (helpers)
-   replace BaseTypes (V)
-   replace enums by static const UINT8 (V)
-   replace static asserts by 98 compatible (V)

## static storage
### ByteArray / StackArray / Index
### general
#### CAPACITY
- use CAPACITY for all StaticArray classes (V)
## one polymorphic Provider (V)
### Provider class
- StaticArray of I_ELEM (V)
- Size by byte union (V)
    - ClassBytes Template

### Dispatcher class -> Mapper (V)
- reduction to Mapper (V)

### Provider / Mapper Class (V)
- change:
    -   Provider gets ProjItem
    -   adds to Mapper with position, ComAddr
    -   Mapper checks position sync
    -   Mapper interface: ComAddr, position


## general issues
-   why does VS react differently on TestSteps line type?
    - use unsigned (instead of short)

### howto
sudo apt-get update
sudo apt-get install gcc
sudo apt-get install build-essential

sudo apt-get install valgrind
sudo apt-get install cloc

vs code: GitHub Markdown Preview
https://marketplace.visualstudio.com/items?itemName=bierner.github-markdown-preview
