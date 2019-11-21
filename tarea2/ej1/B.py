import os, sys,random,string,mmap,posix_ipc
mm_name = 'buffer.txt'
seed= sys.argv[1]
random.seed(seed)
iterations=3


def main():

    #Busy waiting until A initializes semaphores and creates shared memory 
    while True:
        if os.path.exists(mm_name): 

            empty = posix_ipc.Semaphore('/empty')
            full = posix_ipc.Semaphore('/full')
            mutex = posix_ipc.Semaphore('/mutex') 

            fd = os.open(mm_name, os.O_RDONLY)
            mm = mmap.mmap(fd, mmap.PAGESIZE, mmap.MAP_SHARED, mmap.PROT_READ)
            
            #Repeats the reading process infinitely when A gives turn
            while True:
                full.acquire()
                #Critical region
                mm.seek(0)
                mutex.acquire()
                encrypted = mm.readline().decode('ascii')
                mutex.release()           

                print('\nEncrypted in B', encrypted, end='\n')
                message = decrypt(encrypted)
                print('\nDecrypted in B:', message, end='\n')

                empty.release() 

            #mm.close()
            #os.close(fd)
            #break()
            

def decrypt(encrypted):
    key = string.ascii_lowercase
    encrypted = encrypted.split()
    key = ''.join(random.choice(key) for i in range(len(encrypted)))
    decrypted = [ chr(int(a, 2) ^ ord(b)) for (a,b) in zip(encrypted, key) ]
    decrypted = "".join(decrypted)
    return decrypted

main()   
