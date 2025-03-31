"""ms build run system tests with Bullseye coverage"""
from common import start, call, build, setCov, report, rm, buildDir
from os import chdir
from subprocess import Popen

start('systemtests', __doc__)

setCov(False)
build('dstw_gen', 'dstw_stop', 'systemtests')

setCov(True)
build('dstw_runtime')

projFile = 'dstw.proj'
chdir(buildDir)
rm(projFile)

call('dstw_runtime')
call('dstw_runtime X', False)

call('dstw_gen')
call('dstw_runtime X')

bg = Popen('dstw_runtime X X', shell=False)
call('systemtests')
call('dstw_stop')
bg.wait()

report()
