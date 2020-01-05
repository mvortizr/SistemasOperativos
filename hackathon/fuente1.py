#!/usr/bin/python
from random import *
import sys


seed(int(sys.argv[1]))

for i in range(0,int(sys.argv[2])):
    a = randint(0,100)
print (a)

