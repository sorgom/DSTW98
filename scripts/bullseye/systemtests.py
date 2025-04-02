"""ms build run system tests with Bullseye coverage"""
from common import start, call, build, setCov, report, rm, buildDir
from os import chdir
from subprocess import Popen

projFile = 'dstw.proj'

start('systemtests')

setCov(False)
build('dstw_gen', 'dstw_stop', 'systemtests')

setCov(True)
build('dstw_runtime')

chdir(buildDir)
rm(projFile)

#   call runtime with no action
call('dstw_runtime')

#   call runtime with read and no project file
#   expect error 103
call('dstw_runtime X', 103)

#   generate project file
call('dstw_gen')
#   call runtime with read and project file
call('dstw_runtime X')

#   call runtime with read and tcp loop in background
bg = Popen('dstw_runtime X X'.split(), shell=False)

#   run system tests via tcp
call('systemtests')

#   stop runtime via tcp
call('dstw_stop')

#   wait for background process to finish
bg.wait()

report()
