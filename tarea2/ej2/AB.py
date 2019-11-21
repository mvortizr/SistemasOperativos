#!/usr/bin/python3
import os, sys, random, string

seed = sys.argv[1]

random.seed(seed) 

def main():
    pypethonB, pypethonA = os.pipe() 
    processid = os.fork()
    if processid:
        def decrypt(encrypted):
            key = string.ascii_lowercase
            encrypted = encrypted.split()
            key = ''.join(random.choice(key) for i in range(len(encrypted)))
            decrypted = [ chr(int(a, 2) ^ ord(b)) for (a,b) in zip(encrypted, key) ]
            decrypted = "".join(decrypted)
            return decrypted
        # Close write fd because parent not going to write
        os.close(pypethonA)
        pypethonB = os.fdopen(pypethonB, 'r')
        #Read from pipe   
        mensaje = pypethonB.read()    
        print ("Mensaje encriptado:",  mensaje)
        print("Mensaje desencriptado:", decrypt(mensaje))        
        sys.exit(0)
    else:
        def encrypt(message):
            key = string.ascii_lowercase
            key = ''.join(random.choice(key) for i in range(len(message))) 
            encrypted = [ format((ord(a) ^ ord(b)),'b') for (a,b) in zip(message, key) ] 
            encrypted = " ".join(encrypted)
            encrypted = encrypted + '\n'
            return encrypted
        # Close read end cause child not going to read from pipe
        os.close(pypethonB)    
        pypethonA = os.fdopen(pypethonA, 'w')
        #Write to pipe
        pypethonA.write(encrypt(input("Escribe el mensaje:")))
        pypethonA.close()    
        sys.exit(0)

main()