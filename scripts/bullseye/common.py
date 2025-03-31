import atexit
from os import chdir, getcwd, system, environ, remove
from os.path import dirname, abspath, join, isfile
from sys import path as sysPath

chdir(dirname(abspath(__file__)))
myDir = getcwd()
chdir('../..')
repo = getcwd()
buildDir = join(repo, 'build')
binDir = join(buildDir, 'windows', 'bullseye')
vsDir = join(repo, 'vs')
vsSolution = join(vsDir, 'DSTW.sln')
excludeFile = join(myDir, '_exclude.txt')

sysPath.append(join(repo, 'submodules', 'sompy', 'somutil'))
from docopts import docopts

covFile = None

def call(cmd:str):
    if system(cmd) != 0:
        print('call failed:', call)
        exit(1)

def build(*targets):
    """build vs solution with target"""
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
    -h  this help

requires {vsSolution} (generated with premake5)
"""
    opts, _ = docopts(help)
    return opts

def exec(cmd:str):
    """execute command"""
    call(join(binDir, cmd))

def report():
    """report coverage"""
    chdir(buildDir)
    call(f'covselect -qd --import {excludeFile}')
    call('covdir -q --by-name')

def start(what:str, doc:str):
    """common start for coverage"""
    global covFile
    opts = getHelp(doc)

    if not isfile(vsSolution):
        print(f'{vsSolution} not found', 'use premake5 to generate', sep='\n')
        exit(1)

    environ['COVCOPT'] = f'--srcdir {repo} --macro -q'

    covFile = join(buildDir, f'{what}.cov')
    environ['COVFILE'] = covFile

    atexit.register(covRestore)
    call('cov01 -q --push')
    setCov(False)
    if opts.get('c') or not isfile(covFile):
        if isfile(covFile):
            remove(covFile)
        build('clean')

    build('submodules')
