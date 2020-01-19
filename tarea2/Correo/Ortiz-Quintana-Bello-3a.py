#!/usr/bin/python3
import os, sys, random, string

seed = sys.argv[1]
#se ejecuta en bash $ mkfifo pypethon
nombre_pipe = "pypethon"
random.seed(seed) 

def encrypt(message):
    key = string.ascii_lowercase
    key = ''.join(random.choice(key) for i in range(len(message))) 
    encrypted = [ format((ord(a) ^ ord(b)),'b') for (a,b) in zip(message, key) ] 
    encrypted = " ".join(encrypted)
    encrypted = encrypted + '\n'
    return encrypted

if os.path.exists(nombre_pipe):
    #Paso mensajes
    while 1:
        mensaje = input("Para salir presione ENTER\nEscriba el mensaje que desea enviar: ")
        pypethon = open(nombre_pipe,'w')
        pypethon.write(encrypt(mensaje))
        #pypethon.write(mensaje)
        pypethon.close()
        if mensaje == '': break
else:
    print("No se ha creado el FIFO")
