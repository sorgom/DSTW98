"""ms build run module tests with Bullseye coverage"""
from common import start, call, build, setCov, exec, report

start('moduletests', __doc__)

setCov(True)
build('moduletests', 'moduletestsIL')

call('covclear -q')
exec('moduletests')
exec('moduletestsIL')

report()
