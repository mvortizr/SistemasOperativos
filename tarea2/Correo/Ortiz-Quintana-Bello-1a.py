import os, sys,random,string,mmap,posix_ipc

mm_name = 'buffer.txt'
seed= sys.argv[1]
random.seed(seed)
iterations = 3 

def main():
    
    #Initialize semaphores
    full = posix_ipc.Semaphore('/full', posix_ipc.O_CREX,initial_value=0)
    mutex = posix_ipc.Semaphore('/mutex', posix_ipc.O_CREX,initial_value=1)
    empty = posix_ipc.Semaphore('/empty', posix_ipc.O_CREX,initial_value=1)


    #Shared Block with the library
    #memory = posix_ipc.SharedMemory(params["SHARED_MEMORY"], posix_ipc.O_CREX,size=params["SHM_SIZE"])
    #mapfile = mmap.mmap(memory.fd, memory.size)
    #memory.close_fd()

    #Our shared block
    fd = os.open(mm_name, os.O_CREAT | os.O_TRUNC | os.O_RDWR)
    assert os.write(fd, '0'.encode('ascii') * mmap.PAGESIZE) == mmap.PAGESIZE
    mm = mmap.mmap(fd, mmap.PAGESIZE, mmap.MAP_SHARED, mmap.PROT_WRITE)
    

    while True: 
        empty.acquire() 
        message = input('Enter your message:')
        encrypted = encrypt(message)
        mutex.acquire()
        mm.seek(0)
        mm.write(encrypted.encode('ascii'))
        mutex.release()
        full.release()
      
    #posix_ipc.unlink_semaphore('/mutex')
    #posix_ipc.unlink_semaphore('/empty')
    #posix_ipc.unlink_semaphore('/full')

    #mm.close()
    #os.close(fd)


def encrypt(message):   
    key = string.ascii_lowercase
    key = ''.join(random.choice(key) for i in range(len(message))) 
    encrypted = [ format((ord(a) ^ ord(b)),'b') for (a,b) in zip(message, key) ] 
    encrypted = " ".join(encrypted)
    encrypted = encrypted + '\n'
    return encrypted

main()
   
