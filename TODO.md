### coverage
-   module tests
    -   complete Mapper
    -   premake: apply decent CAPACITY (5 times all types)

### systemtests
-   main
    -   Ctrl loop
-   gen_data
    - parameter n
    - -h
-   sleep by select
-   use GenProjData to run tests

### vscode
-   white preview

### PC setup
-   StarUML
-   move linux?

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
- StaticArray of I_ELEM
- Size by byte union
    - ClassBytes Template

### Dispatcher class -> Mapper (V)
- reduction to Mapper

### Provider / Mapper Class (V)
- change:
    -   Provider gets ProjItem
    -   adds to Mapper with position, ComAddr
    -   Mapper checks position sync
    -   Mapper interface: ComAddr, position


## general issues
-   why does VS react differently on TestSteps line type?
    - use unsigned (instead of short)


sudo apt-get update
sudo apt-get install gcc
sudo apt-get install build-essential
