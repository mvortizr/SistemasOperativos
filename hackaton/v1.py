import sys
import os
import subprocess
#import time
#import socket
import multiprocessing as mp
import concurrent.futures

#start_time = time.time()


A= sys.argv[1]
B= sys.argv[2]


def getDataFromTxt():
    dictOfLines = dict()

    with open('numeros.txt') as fd:   
        for line in fd:
            if line in dictOfLines:
                dictOfLines[line] += 1
            else:
                dictOfLines[line] = 1
    
    return dictOfLines

def callFuente1(numtxt):
    #NOTA: sustituir 1 por A
    proc = subprocess.Popen(['python3', 'fuente1.py','1',numtxt], stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    fuenteRes = proc.communicate()[0]      
    fuenteRes = int(fuenteRes.decode())
    return (fuenteRes,numtxt)



 
def Act1(txtInfo):
    #queue = mp.Queue()
    #Crear una Pool de llamadas a fuente A, numtxt y sumarlas
    with concurrent.futures.ProcessPoolExecutor() as executor:
        results = executor.map(callFuente1,txtInfo)

    resAct1 = 0
    for item in results:
        resAct1 = resAct1 + item[0]*txtInfo[item[1]] 
        
    print('Actividad 1:', resAct1)





    
def Act1andAct3():
    txtInfo = getDataFromTxt()

    act1Process = mp.Process(target=Act1,args=[txtInfo])
    #act2Process = Process(target=Act2)
    act1Process.start()
    #act2.Process.start()

    act1Process.join()
    #act2Process.join()




#def Act2():
#   pass



p1 = mp.Process(target=Act1andAct3)
p1.start()

#p2 = Process(target=Act2)
p1.join()
#p2.join()









    
  


