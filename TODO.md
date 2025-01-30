# Transfer from C++ 2017 to C++98

## coding (helpers)
-   replace BaseTypes
-   replace enums by static const UINT8
-   replace static asserts by module tests
-   getn -> macros ?

## static storage
### ByteArray / StackArray / Index

## one polymorphic Provider
### Provider class
- StaticArray of I_ELEM
- Size by byte union
    - ClassBytes Template

### Dispatcher class
- reduction to

## general issues
-   why does VS react differently on TestSteps line type?
    - use unsigned (instead of short)
