import atexit
from os import chdir, getcwd, system, environ, remove, name as oname
from os.path import dirname, abspath, join, isfile
from sys import path as sysPath

isWin = oname == 'nt'
osSubdir = 'windows' if isWin else 'linux'

chdir(dirname(abspath(__file__)))
myDir = getcwd()
chdir('../..')
repo = getcwd()
buildDir = join(repo, 'build')
binDir = join(buildDir, osSubdir, 'bullseye')
vsDir = join(repo, 'vs')
vsSolution = join(vsDir, 'DSTW.sln')
excludeFile = join(myDir, '_exclude.txt')

sysPath.append(join(repo, 'submodules', 'sompy', 'somutil'))
from docopts import docopts

def call(cmd:str, ef=True):
    res = system(cmd)
    if res != 0 and ef:
        print('call failed:', call)
        exit(1)
    return res

def build(*targets):
    """build targets"""
    call(f'msbuild -m {vsSolution} -t:"{','.join(targets)}" -p:configuration=bullseye')

def covRestore():
    """restore cov01 setting"""
    call('cov01 -q --pop')

def setCov(on:bool=True):
    """set coverage on or off"""
    call(f'cov01 -q --{"on" if on else "off"}')

def getHelp(doc:str):
    """get help"""
    help = doc + f"""

usage: this script [options]
options:
    -c  clean
    -m  generate merged report
    -h  this help
"""
    opts, _ = docopts(help)
    return opts

def report():
    """report coverage"""
    chdir(buildDir)
    call(f'covselect -qd --import {excludeFile}')
    call('covdir -q --by-name')

def rm(file):
    """remove file"""
    if isfile(file):
        remove(file)

def start(what:str, doc:str):
    """common start for coverage"""
    opts = getHelp(doc)

    if isWin and not isfile(vsSolution):
        print(f'{vsSolution} not found', 'use premake5 to generate', sep='\n')
        exit(1)

    environ['PATH'] = f"{binDir}{';' if isWin else ':'}{environ['PATH']}"

    environ['COVCOPT'] = f'--srcdir {repo} --macro -q'

    covFile = join(buildDir, f'{what}.cov')
    environ['COVFILE'] = covFile

    atexit.register(covRestore)
    call('cov01 -q --push')
    setCov(False)
    if opts.get('c') or not isfile(covFile):
        rm(covFile)
        build('clean')

    build('submodules')
