"""write merged Bullseye coverage markdown report"""
from covCommon import call, repo, buildDir, covFile, procOut
from os import chdir, system
from os.path import isfile, isdir

covMinima   = '100,100'
coverageMd  = f'{repo}/testing/coverage_bullseye.md'

if not isdir(buildDir): exit()
chdir(buildDir)
tsts = ['moduletests', 'systemtests']
srcs = [covFile(tst) for tst in tsts]
for src in srcs:
    if not isfile(src): exit()

trg = 'merged'
trgf = covFile(trg)
call(f'covmerge -qcf {trgf} {" ".join(srcs)}')

with open(coverageMd, 'w') as fh:
    fh.write('# current Bullseye coverage\n')
    tsts.append(trg)
    srcs.append(trgf)
    for what, src in zip(tsts, srcs):
        print(f'### {what}', '```',
              procOut(f'covdir -q --by-name -f {src}'), '```', sep='\n', file=fh)

    ret = system(f'covdir -q --checkmin {covMinima} -f {trgf}')
    fh.write(f'checkmin {covMinima} {"passed" if ret == 0 else "failed"}\n')
    fh.close()
    print ('->', coverageMd)
