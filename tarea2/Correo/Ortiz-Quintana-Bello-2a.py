#!/usr/bin/python3
import os, sys, random, string, sysv_ipc

seed = sys.argv[1]

nombre_pipe = "pypethon"

random.seed(seed) 

def encrypt(message):
    key = string.ascii_lowercase
    key = ''.join(random.choice(key) for i in range(len(message))) 
    encrypted = [ format((ord(a) ^ ord(b)),'b') for (a,b) in zip(message, key) ] 
    encrypted = " ".join(encrypted)
    encrypted = encrypted + '\n'
    return encrypted

if not os.path.exists(nombre_pipe):
    os.mkfifo(nombre_pipe)

#comparto el nombre de la tuberia en memoria compartida
memory = sysv_ipc.SharedMemory(1, sysv_ipc.IPC_CREX, 666,  len(nombre_pipe) )
memory.write(nombre_pipe) #usuario debe terner permisos en /dev/shm
memory.detach()

#Paso mensajes
while 1:
    mensaje = input("Para salir presione ENTER\nEscriba el mensaje que desea enviar: ")
    pypethon = open(nombre_pipe,'w')
    pypethon.write(encrypt(mensaje))
    pypethon.close()
    if mensaje == '': break

memory.remove()
os.remove(nombre_pipe)

