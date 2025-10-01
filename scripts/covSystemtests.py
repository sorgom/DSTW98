"""build and run system tests with Bullseye coverage"""
from covCommon import *
from os import chdir
from subprocess import Popen

projFile = 'dstw.proj'

covStart('systemtests')

covBuild('dstw_gen', 'dstw_stop', 'systemtests')
covBuild('dstw_runtime', cov=1)

chdir(buildDir)
rm(projFile)

#   call runtime with no action
call('dstw_runtime')

#   call runtime with read and no project file
#   which should fail
call('dstw_runtime X', False)

#   generate project file
call('dstw_gen')
#   call runtime with read and project file
call('dstw_runtime X')

#   call runtime with read and tcp loop in background
bg = Popen('dstw_runtime X X'.split())

#   run system tests via tcp
call('systemtests')

#   stop runtime via tcp
call('dstw_stop')

#   wait for background process to finish
bg.wait()

covReport()
