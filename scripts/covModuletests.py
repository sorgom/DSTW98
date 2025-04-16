"""build run module tests with Bullseye coverage"""
from covCommon import *

covStart('moduletests')

covBuild('moduletests', 'moduletestsIL', cov=1)

call('covclear -q')
call('moduletests')
call('moduletestsIL')

covReport()
