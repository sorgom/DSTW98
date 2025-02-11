#   ============================================================
#   all pre-commit script calls in one
#   ============================================================
#   created by Manfred Sorgo

from modGenCloc import genCloc

print("* genCloc")
genCloc(['application', 'testing/testenv', 'testing/tests/moduletests', 'testing/tests/moduletestsIL', 'testing/tests/systemtests', 'specification'])
