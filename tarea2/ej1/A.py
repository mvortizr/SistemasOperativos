import sys
import random 
from operator import xor
import string

def main():
    while True: 
        #Read seed from command line
        seed= sys.argv[1] 
        #TODO Send seed to B
        
        #Using seed 
        random.seed(seed) 
               
        #Asking input from user
        message = input('Enter your message: ') 

        #Generate a random string with the same length 
        key = string.ascii_lowercase
        key = ''.join(random.choice(key) for i in range(len(message)))

        #Debbuging
        print('\nmessage in A: ', message, ', # chr', len(message), type(message), sep=' ', end='\n\n' )
        print('key in A: ', key, type(key), ', # chr', len(message), type(message), sep=' ', end='\n\n' ) 
        encrypt(message,key)
    

#Encrypt character by character using XOR
def encrypt(message,key):
    encrypted = [ chr(ord(a) ^ ord(b)) for (a,b) in zip(message, key) ] 
    print('encrypted in A: ',encrypted, end='\n\n')
    decrypt(encrypted,key)

#Decrypt character by character using XOR
def decrypt(encrypted,key):
    decrypted = [ chr(ord(a) ^ ord(b)) for (a,b) in zip(encrypted, key) ]
    decrypted = "".join(decrypted)
    print('decrypted in A: ', decrypted, end='\n\n') 



main()



#thing_index = thing_list.index(elem) if elem in thing_list else -1

