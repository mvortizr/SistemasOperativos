#!/usr/bin/python3
import os, sys, random, string, sysv_ipc

seed = sys.argv[1]

random.seed(seed) 

def decrypt(encrypted):
    key = string.ascii_lowercase
    encrypted = encrypted.split()
    key = ''.join(random.choice(key) for i in range(len(encrypted)))
    decrypted = [ chr(int(a, 2) ^ ord(b)) for (a,b) in zip(encrypted, key) ]
    decrypted = "".join(decrypted)
    return decrypted

memory = sysv_ipc.SharedMemory(1)

nombre_pipe = memory.read()
memory.detach()
while 1:
    pypethon = open(nombre_pipe,'r')
    mensaje = pypethon.read()
    mensajeReal = decrypt(mensaje)
    pypethon.close()
    if mensajeReal == '': 
        print("Se ha cerrado A")
        break
    print("Mensaje encriptado: " + mensaje)
    print("Mensaje original: " + mensajeReal)
    

