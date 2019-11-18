import random 
from operator import xor
import string

def main():
    readSeed()
    
#Read the seed (B)
def readSeed():
    with open("shared", "r+b") as f:
        mm = mmap.mmap(f.fileno(), 0)
        print('\nSeed in B', mm.readline().decode('ascii'),sep=' ', end='\n')
        mm.close()



#Decrypt character by character using XOR
def decrypt(encrypted,key):
    decrypted = [ chr(ord(a) ^ ord(b)) for (a,b) in zip(encrypted, key) ]
    decrypted = "".join(decrypted)
    print('decrypted in B: ', decrypted, end='\n\n') 
