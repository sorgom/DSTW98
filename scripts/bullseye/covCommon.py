import atexit
from os import chdir, getcwd, system, environ, unlink, name as oname, makedirs
from os.path import dirname, isfile
from subprocess import Popen, PIPE
from sys import argv

isWin = oname == 'nt'
osSub = 'windows' if isWin else 'linux'

chdir(dirname(__file__))
myDir = getcwd()
chdir('../..')
repo = getcwd()
buildDir    = f'{repo}/build'
binDir      = f'{buildDir}/{osSub}/bullseye'
makeDir     = f'{repo}/make'
reportsDir  = f'{repo}/reports'
vsDir       = f'{repo}/vs'
vsSolution  = f'{vsDir}/DSTW.sln'
excludeFile = f'{myDir}/covExclude.txt'

what = 'NN'

#   basics
def call(cmd:str, check=True):
    """call command and check return code"""
    res = system(cmd)
    if check and res != 0:
        print(f'call failed:', cmd)
        exit(1)

def procOut(cmd:str):
    """call command and return output"""
    with Popen(cmd.split(), stdout=PIPE, universal_newlines=True) as proc:
        return proc.stdout.read()

def rm(file):
    """remove file if exists"""
    if isfile(file): unlink(file)

#  specific
def build(*targets, cov=0):
    """build targets windows or linux"""
    call(f'cov01 -q{cov}')
    if isWin:
        c = ','.join(targets)
        call(f'msbuild -m {vsSolution} -t:"{c}" -p:configuration=bullseye')
    else:
        call(f'make -j -C {makeDir} {" ".join(targets)} config=bullseye')

def covRestore():
    """restore cov01 setting"""
    call('cov01 -q --pop')

def report():
    """report coverage"""
    chdir(buildDir)
    call(f'covselect -qd --import {excludeFile}')
    txt = procOut(f'covdir -q --by-name')
    reportFile = f'{reportsDir}/coverage_{what}_{osSub}.txt'
    with open(reportFile, 'w') as fh:
        fh.write(txt)
    print(txt)

def covFile(what:str):
    """coverage file name"""
    return f'{what}_{osSub}.cov'

def start(me:str):
    """common start for coverage"""
    global what
    what = me

    makedirs(reportsDir, exist_ok=True)

    if isWin and not isfile(vsSolution):
        print(f'{vsSolution} not found', 'use premake5 to generate', sep='\n')
        exit(1)

    environ['PATH'] = f"{binDir}{';' if isWin else ':'}{environ['PATH']}"

    environ['COVCOPT'] = f'--srcdir {repo} --macro -q'

    myCovFile = f'{buildDir}/{covFile(what)}'
    environ['COVFILE'] = myCovFile

    atexit.register(covRestore)
    call('cov01 -q --push')
    if '-c' in argv or not isfile(myCovFile):
        rm(myCovFile)
        build('clean')

    build('submodules')
