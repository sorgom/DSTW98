### TCP
-   improve client select, greater buffer

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
sudo apt install net-tools
```

9. find home drive, sample:
C:\Users\MS\AppData\Local\Packages\CanonicalGroupLimited.Ubuntu22.04LTS_79rhkp1fndgsc\LocalState\rootfs\home\ms

10. subst
```
subst U: /D
subst U: C:\Users\MS\AppData\Local\Packages\CanonicalGroupLimited.Ubuntu22.04LTS_79rhkp1fndgsc\LocalState\rootfs\home\ms
```
### install Docker Desktop Win
Install from the command line

After downloading Docker Desktop Installer.exe

-   rename "Docker Desktop Installer.exe" to Docker_Desktop_Installer.exe

run the following command in a terminal to install Docker Desktop:

```shell
Docker_Desktop_Installer.exe install
```

If you’re using PowerShell you should run it as:

```shell
Start-Process Docker_Desktop_Installer -Wait install
```

If using the Windows Command Prompt:

```shell
start /w "" Docker_Desktop_Installer install
```

By default, Docker Desktop is installed at C:\Program Files\Docker\Docker.

The ``install`` command accepts the following flags:
-    ``--quiet``: Suppresses information output when running the installer

-    ``--accept-license``: Accepts the Docker Subscription Service Agreement now, rather than requiring it to be accepted when the application is first run

-   ``--no-windows-containers``: Disables the Windows containers integration. This can improve security. For more information, see Windows containers.

-   ``--backend=<backend name>``: Selects the default backend to use for Docker Desktop, ``hyper-v``, windows or ``wsl-2`` (default)

-   ``--installation-dir=<path>``: Changes the default installation location (C:\Program Files\Docker\Docker)

- ``--always-run-service``: After installation completes, starts com.docker.service and sets the service startup type to Automatic. This circumvents the need for administrator privileges, which are otherwise necessary to start com.docker.service. com.docker.service is required by Windows containers and Hyper-V backend.

#### Sample cmd shell
(Powershell did not work)
```shell
cd /d K:/MyDownloads
start /w "" Docker_Desktop_Installer install --installation-dir=D:/programs/docker --accept-license --no-windows-containers --always-run-service
```
Docker installation output:
```shell
CommandLine: "K:\MyDownloads\Docker_Desktop_Installer.exe" "install" -package "res:DockerDesktop" --installation-dir="D:\programs\docker" --accept-license --no-windows-containers --always-run-service --relaunch-as-admin
```

#### docker run options
```
-i, --interactive                 Keep STDIN open even if not attached

--mount mount                     Attach a filesystem mount to the
                                  container
--name string                     Assign a name to the container

-rm                               Automatically remove the
                                  container and its associated
                                  anonymous volumes when it exits

-t, --tty                         Allocate a pseudo-TTY
```
