#!/usr/bin/env python3
import re
import datetime
import os 
from sys import argv
from subprocess import run

SAVE_PATH= 'outputs'
IN_PATH= 'inputs'

helpstr = '''usage: %s [-ABCDEF] <executable> [<ascii comment>]*
runs executable over all inputs or just the selected (-ABCDEF) switches

input files are taken from:
%s
inputs are expected to be named A.in (for example)

output is stored inside:
%s
This can be changed in source code

it creates a subfolder there named as timestamp and creates txt with your <ascii comment>
''' % (argv[0], IN_PATH, SAVE_PATH)

exec_time = datetime.datetime.now().strftime("%Y-%m-%d_%H-%M-%S")

if re.match('^-[A-F]{,6}$',argv[1]):
    run_set = set(argv[1][1:])
    executable =  argv[2]
    comment = ''.join(argv[3:])
else:
    run_set = set('ABCDEF')
    executable = argv[1]
    comment = ''.join(argv[2:])

D = os.path.join(SAVE_PATH,exec_time+comment.replace(' ',''))
os.mkdir(D)

with open(os.path.join(D, 'comment.txt'), 'w') as f:
    f.write(comment)

for i in run_set: 
    outputf = os.path.join(D,i+'.out')
    inputf = os.path.join(IN_PATH, i+'.in')
    run(['bash','-c' ,'./%s < %s > %s ' % (executable, inputf, outputf) ])

