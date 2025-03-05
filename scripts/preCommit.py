#   ============================================================
#   all pre-commit script calls in one
#   ============================================================
#   created by Manfred Sorgo

from modGenCloc import genCloc

genCloc(['specification', 'application', 'testing'])
