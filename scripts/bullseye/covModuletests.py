"""build run module tests with Bullseye coverage"""
from covCommon import start, call, build, report

start('moduletests')

build('moduletests', 'moduletestsIL', cov=1)

call('covclear -q')
call('moduletests')
call('moduletestsIL')

report()
