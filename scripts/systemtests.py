"""build and run system tests linux / windows"""
from common import start, call, build
from subprocess import Popen

start()
build('dstw_gen', 'dstw_runtime', 'dstw_stop', 'systemtests')
#  generate project file
call('dstw_gen')
#  call runtime in background
bg = Popen('dstw_runtime X X'.split())
#  run system tests via tcp
call('systemtests')
#  stop runtime via tcp
call('dstw_stop')
#  wait for background process to finish
bg.wait()
