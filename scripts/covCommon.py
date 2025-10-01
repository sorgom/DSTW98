import atexit
from common import *
from os import chdir, environ, makedirs
from os.path import isfile
from sys import argv

what = 'NN'

reportsDir  = f'{repo}/reports'
excludeFile = f'{myDir}/covExclude.txt'

#   restore cov01 setting
def covRestore():
    call('cov01 -q --pop')

#   report coverage
def covReport():
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

def covBuild(*targets, cov=0):
    call(f'cov01 -q{cov}')
    build(*targets)

def covStart(me:str):
    """common start for coverage"""
    global what
    what = me

    setup('bullseye')

    makedirs(reportsDir, exist_ok=True)

    environ['COVCOPT'] = f'--srcdir {repo} --macro -q'

    myCovFile = f'{buildDir}/{covFile(what)}'
    environ['COVFILE'] = myCovFile

    atexit.register(covRestore)
    call('cov01 -q --push')
    if '-c' in argv or not isfile(myCovFile):
        rm(myCovFile)
        covBuild('clean')

    covBuild('submodules')
