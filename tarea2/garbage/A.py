import sys
import random 
from operator import xor
import string
import mmap
import os

def main():
    seed= sys.argv[1]  
    shareSeed(seed)  
    readSeed() #B
    random.seed(seed)

    while True:              
        message = input('Enter your message: ') 
        key = string.ascii_lowercase
        key = ''.join(random.choice(key) for i in range(len(message)))
        encrypted = encrypt(message,key) 
        decrypted = decrypt(encrypted,key)   
        #shareEncrypted(encrypted)
    
#Encrypt character by character using XOR
def encrypt(message,key):
    encrypted = [ format((ord(a) ^ ord(b)),'b') for (a,b) in zip(message, key) ] 
    encrypted = " ".join(encrypted)
    print('encrypted con join: ',encrypted, end='\n\n')
    return encrypted

#Decrypt character by character using XOR (B)
#la idea es que  B tenga key = ''.join(random.choice(key) for i in range(len(message))) y llame esta funcion
def decrypt(encrypted,key):
    encrypted = encrypted.split()
    decrypted = [ chr(int(a, 2) ^ ord(b)) for (a,b) in zip(encrypted, key) ]
    decrypted = "".join(decrypted)
    print('decrypted in B: ', decrypted, end='\n\n') 

#Initialize file with seed 
def shareSeed(seed):  
    with open("shared", "wb") as f:
        f.write(seed.encode('ascii'))

#Read the seed (B)
def readSeed():
    with open("shared", "r+b") as f:
        mm = mmap.mmap(f.fileno(), 0,mmap.MAP_SHARED,mmap.PROT_READ)
        print('\nSeed in B', mm.readline().decode('ascii'),sep=' ', end='\n')
        mm.close()

#Share token 
def shareEncrypted(encrypted):
    with open("shared", "r+b") as f:
        mm = mmap.mmap(f.fileno(), 1,mmap.MAP_SHARED,mmap.PROT_WRITE)
        mm.write(encrypted.encode('ascii'))
        mm.close()



main()


#thing_index = thing_list.index(elem) if elem in thing_list else -1


        #Debug
        #print('\nmessage in A: ', message, ', # chr', len(message), type(message), sep=' ', end='\n\n' )
        #print('key in A: ', key, type(key), ', # chr', len(message), type(message), sep=' ', end='\n\n' ) 
        #print('encrypted in A: ',encrypted, end='\n\n')

