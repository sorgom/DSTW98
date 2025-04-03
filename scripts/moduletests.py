"""build and run module tests linux / windows"""
from common import start, call, build

start()
build('moduletests', 'moduletestsIL')
call('moduletests')
call('moduletestsIL')
