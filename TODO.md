# Transfer from C++ 2017 to C++98
## 98
-   replace standard in premake

## coding (helpers)
-   replace BaseTypes (V)
-   replace enums by static const UINT8 (V)
-   replace static asserts by 98 compatible (V)

## static storage
### ByteArray / StackArray / Index
### general
#### CAPACITY
- use CAPACITY for all StaticArray classes (V)
## one polymorphic Provider
### Provider class
- StaticArray of I_ELEM
- Size by byte union
    - ClassBytes Template

### Dispatcher class
- reduction to Mapper

### Provider / Mapper Class
- change:
    -   Provider gets ProjItem
    -   adds to Mapper with position ComAddr
    -   Mapper checks position sync
    -   Mapper interface: ComAddr, position

## general issues
-   why does VS react differently on TestSteps line type?
    - use unsigned (instead of short)
