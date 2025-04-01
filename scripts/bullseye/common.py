import atexit
from os import chdir, getcwd, system, environ, unlink, name as oname
from os.path import dirname, abspath, join, isfile
from subprocess import Popen, PIPE
from sys import path as sysPath

isWin = oname == 'nt'
osSub = 'windows' if isWin else 'linux'

chdir(dirname(abspath(__file__)))
myDir = getcwd()
chdir('../..')
repo = getcwd()
buildDir = join(repo, 'build')
binDir = join(buildDir, osSub, 'bullseye')
makeDir = join(repo, 'make')
vsDir = join(repo, 'vs')
vsSolution = join(vsDir, 'DSTW.sln')
excludeFile = join(myDir, 'exclude.txt')
coverageMd = join(repo, 'testing', 'coverage_bullseye.md')
covMinima = '100,100'

sysPath.append(join(repo, 'submodules', 'sompy', 'somutil'))
from docopts import docopts

opts = None

def call(cmd:str, ef=True):
    res = system(cmd)
    if res != 0 and ef:
        print('call failed:', cmd)
        exit(1)
    return res

def build(*targets):
    """build targets"""
    if isWin:
        c = ','.join(targets)
        call(f'msbuild -m {vsSolution} -t:"{c}" -p:configuration=bullseye')
    else:
        call(f'make -j -C {makeDir} {" ".join(targets)} config=bullseye')

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

def genMd():
    """generate markdown coverage report"""
    chdir(buildDir)
    tsts = ['moduletests', 'systemtests']
    srcs = [covFile(tst) for tst in tsts]
    for src in srcs:
        if not isfile(src): return

    trg = 'merged'
    trgf = covFile(trg)
    call(f'covmerge -qcf {trgf} {" ".join(srcs)}')

    with open(coverageMd, 'w') as fh:
        fh.write('# current Bullseye coverage\n')
        tsts.append(trg)
        srcs.append(trgf)
        for what, src in zip(tsts, srcs):
            with Popen(f'covdir -q --by-name -f {src}'.split(), stdout=PIPE, universal_newlines=True) as proc:
                print(f'### {what}', '```', proc.stdout.read(), '```', sep='\n', file=fh)

        ret = system(f'covdir -q --checkmin {covMinima} -f {trgf}')
        fh.write(f'checkmin {covMinima} {"passed" if ret == 0 else "failed"}\n')
        fh.close()
        print('\n->', coverageMd)

def report():
    """report coverage"""
    chdir(buildDir)
    call(f'covselect -qd --import {excludeFile}')
    call('covdir -q --by-name')
    if opts.get('m'): genMd()

def rm(file):
    """remove file"""
    if isfile(file): unlink(file)

def covFile(what:str):
    """return coverage file name"""
    return f'{what}_{osSub}.cov'

def start(what:str, doc:str):
    """common start for coverage"""
    global opts
    opts = getHelp(doc)

    if isWin and not isfile(vsSolution):
        print(f'{vsSolution} not found', 'use premake5 to generate', sep='\n')
        exit(1)

    environ['PATH'] = f"{binDir}{';' if isWin else ':'}{environ['PATH']}"

    environ['COVCOPT'] = f'--srcdir {repo} --macro -q'

    myCovFile = join(buildDir, covFile(what))
    environ['COVFILE'] = myCovFile

    atexit.register(covRestore)
    call('cov01 -q --push')
    setCov(False)
    if opts.get('c') or not isfile(myCovFile):
        rm(myCovFile)
        build('clean')

    build('submodules')
