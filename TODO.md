-   howto launch cmd
-   CppUTestSteps:
    -   redirect L_ macros to base ones
    -   add PARAM and other macros
-   CFG/Capcity.h
-   sompy: cleanMdj, cleanSvg line endings

### doc
-   mocking image (V)


### vscode
-   white preview: documet how

### PC setup
-   StarUML
-   move linux?
-   chrome for sombeam
-   valgrind


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

[see instruction](https://www.public-health.uiowa.edu/it/support/kb48549/)
## How to Install WSL and Ubuntu on Windows 10
### Install Windows Subsystem for Linux (WSL) on Windows
1. Open PowerShell as an administrator
2. ``Enable-WindowsOptionalFeature -Online -FeatureName Microsoft-Windows-Subsystem-Linux``
3. Restart the computer when prompted.

### Install Ubuntu
1.  Open the Microsoft Store (search for "store" from the start menu)
2.  Search the store for "Ubuntu"
3.  Install Ubuntu (it is not necessary to sign in to the store)
4.  Launch Ubuntu
5.  Enter a username. This will create a local user account and you will be automatically logged in to Ubuntu as this user.
6.  Enter a password for the user and enter a second time to confirm.
7.  Update all Ubuntu software packages with ``sudo apt update && sudo apt upgrade -y``
8.  setup development environment
```
sudo apt-get install gcc
sudo apt-get install build-essential
sudo apt-get install cloc
```
