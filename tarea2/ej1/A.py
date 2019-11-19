import os, sys,random,string,mmap

mm_name = 'buffer.txt'
seed= sys.argv[1]
random.seed(seed) 

def main():
    fd = os.open(mm_name, os.O_CREAT | os.O_TRUNC | os.O_RDWR)
    assert os.write(fd, '0'.encode('ascii') * mmap.PAGESIZE) == mmap.PAGESIZE
    mm = mmap.mmap(fd, mmap.PAGESIZE, mmap.MAP_SHARED, mmap.PROT_WRITE)
    message = input('Enter your message:')
    encrypted = encrypt(message)
    mm.write(encrypted.encode('ascii'))
    os.close(fd)


def encrypt(message):
    key = string.ascii_lowercase
    key = ''.join(random.choice(key) for i in range(len(message))) 
    encrypted = [ format((ord(a) ^ ord(b)),'b') for (a,b) in zip(message, key) ] 
    encrypted = " ".join(encrypted)
    encrypted = encrypted + '\n'
    return encrypted

main()
   
