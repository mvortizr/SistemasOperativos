#!/usr/bin/python3
import sys, random, string

seed = sys.argv[1]

random.seed(seed) 

def encrypt(message):
    key = string.ascii_lowercase
    key = ''.join(random.choice(key) for i in range(len(message))) 
    encrypted = [ format((ord(a) ^ ord(b)),'b') for (a,b) in zip(message, key) ] 
    encrypted = " ".join(encrypted)
    encrypted = encrypted + '\n'
    return encrypted

print(encrypt(input()))
