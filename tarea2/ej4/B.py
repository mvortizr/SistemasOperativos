#!/usr/bin/python3
import sys, random, string

seed = sys.argv[1]

random.seed(seed) 

def decrypt(encrypted):
    key = string.ascii_lowercase
    encrypted = encrypted.split()
    key = ''.join(random.choice(key) for i in range(len(encrypted)))
    decrypted = [ chr(int(a, 2) ^ ord(b)) for (a,b) in zip(encrypted, key) ]
    decrypted = "".join(decrypted)
    return decrypted

mensaje = input()

print("Mensaje encriptado: " + mensaje)
print("Mensaje originar: "+ decrypt(mensaje))
    

