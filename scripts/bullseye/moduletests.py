"""ms build run module tests with Bullseye coverage"""
from common import start, call, build, setCov, report

start('moduletests')

setCov(True)
build('moduletests', 'moduletestsIL')

call('covclear -q')
call('moduletests')
call('moduletestsIL')

report()
