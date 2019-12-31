import sys
import os
import subprocess
import time
import socket

start_time = time.time()

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('127.0.0.1', 9999)) 

A= sys.argv[1]
B= sys.argv[2]



dictOfLines = dict()

with open('numeros.txt') as fd:   
   for line in fd:
        if line in dictOfLines:
            dictOfLines[line] += 1
        else:
            dictOfLines[line] = 1

#print(dictOfLines)
       


 

sumAct1 = 0
sumAct3 = 0




#with open('numeros.txt') as fd:
#   for line in fd:

        #Guardar numeros distintos y las veces que se repiten

        #Act 1
        #proc = subprocess.Popen(['python3', 'fuente1.py',A,line], stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        #fuenteRes = proc.communicate()[0]      
        #fuenteRes = int(fuenteRes.decode())
        #sumAct1=sumAct1+fuenteRes

        #Act3
        #s.send(line.encode())
        #serverRes = int(s.recv(1024).decode())
        #sumAct3 = sumAct3 + serverRes
        

s.close() 
fd.close()


#Act2

x = 10000000 + int(sys.argv[2])*10000
y = 10000000 - int(sys.argv[2])*10000
r = 0

for j in range(500):   
    for i in range(200000):
        x = x * 5.6800001 / 5.68   
    for i in range(100000):       
        y = y * 5.6800001 / 5.68   
    
    r = r + x + y
            
print (r)
   

print('-------------------------------------------')
print('Actividad 1',sumAct1)
print("Tiempo 1 %s s" % (time.time() - start_time))
print('-------------------------------------------')

print('-------------------------------------------')
print('Actividad 3',sumAct3)
print("Tiempo 3 %s s" % (time.time() - start_time))
print('-------------------------------------------')



print('-------------------------------------------')
print('Actividad 2', r)
print("Tiempo 2 %s s" % (time.time() - start_time))
print('-------------------------------------------')




    
  


