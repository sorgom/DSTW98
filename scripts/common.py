from os import chdir, getcwd, system, environ, name as oname
from os.path import dirname
from subprocess import Popen
from sys import argv

isWin = oname == 'nt'
osSub = 'windows' if isWin else 'linux'
cfg = 'release'

chdir(dirname(__file__))
myDir = getcwd()
chdir('..')
repo = getcwd()
binDir      = f'{repo}/build/{osSub}/{cfg}'
makeDir     = f'{repo}/make'
vsSolution  = f'{repo}/vs/DSTW.sln'

#   call command and check return code
def call(cmd:str):
    if system(cmd) != 0:
        print(f'call failed:', cmd)
        exit(1)

#   build targets windows or linux
def build(*targets):
    if isWin:
        c = ','.join(targets)
        call(f'msbuild -m {vsSolution} -t:"{c}" -p:configuration={cfg}')
    else:
        call(f'make -s -j -C {makeDir} {" ".join(targets)} config={cfg}')

def start():
    environ['PATH'] = f"{binDir}{';' if isWin else ':'}{environ['PATH']}"
    if '-c' in argv:
        build('clean')
