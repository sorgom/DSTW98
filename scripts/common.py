#   common functions for building and running tests
#   linux / windows
from os import chdir, getcwd, system, environ, name as oname, unlink
from os.path import dirname, isfile
from subprocess import Popen, PIPE
from sys import argv

isWin = oname == 'nt'
osSub = 'windows' if isWin else 'linux'
cfg = None

chdir(dirname(__file__))
myDir = getcwd()
chdir('..')
repo = getcwd()
buildDir    = f'{repo}/build'
makeDir     = f'{repo}/make'
vsSolution  = f'{repo}/vs/DSTW.sln'

if isWin and not isfile(vsSolution):
    print(f'{vsSolution} not found', 'use premake5 to generate', sep='\n')
    exit(1)

#   setup
def setup(config:str):
    global cfg
    cfg = config
    binDir = f'{buildDir}/{osSub}/{cfg}'
    #   extend PATH with bin directory
    environ['PATH'] = f"{binDir}{';' if isWin else ':'}{environ['PATH']}"

#   call command and check return code
def call(cmd:str, check=True):
    res = system(cmd)
    if check and res != 0:
        print('call failed:', cmd)
        exit(1)

#   remove file if exists
def rm(file):
    if isfile(file): unlink(file)

#   call command and return output
def procOut(cmd:str):
    with Popen(cmd.split(), stdout=PIPE, universal_newlines=True) as proc:
        return proc.stdout.read()

#   build targets windows (msbuild) or linux (make)
def build(*targets):
    if isWin:
        c = ','.join(targets)
        call(f'msbuild -m {vsSolution} -t:"{c}" -p:configuration={cfg}')
    else:
        call(f'make -s -j -C {makeDir} {" ".join(targets)} config={cfg}')

def start():
    setup('release')
    if '-c' in argv:
        build('clean')
