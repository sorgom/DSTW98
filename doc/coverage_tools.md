# code coverage tools
## bullseye
Bullseye coverage turned out a most excellent tool.

It analyses:
-   analyses source and header coverage
-   every condition of logical and / or
-   every item of multiple case statement
-   for loops

It can generate several outputs from simple text to html documentation.

It's available for Windows and Linux.

Bullseye is not for free - but they provide a free trial period.

- [current text report](coverage_bullseye.md)

## gcov
Gcov comes with gnu compiler collection (gcc) and therefore is available
-   on a standard linux
-   for the github CI

It
-   provides a very limited impression of the source code coverage
-   is quite useless with headers

It requires explicit _if else_ blocks. Therefore one has to attach an _else_ block with a (dummy) statement to every _if_ block.

sample:
```cpp
    if (mIndx.size() > id)
    {
        tele.name = mIndx.at(id).name;
        IL::getCom().send(tele);
    }
    else
    { pass(); }
```
