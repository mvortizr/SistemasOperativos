import os, sys,random,string,mmap

mm_name = 'buffer.txt'
seed= sys.argv[1]
random.seed(seed) 

def main():
    fd = os.open(mm_name, os.O_RDONLY)
    mm = mmap.mmap(fd, mmap.PAGESIZE, mmap.MAP_SHARED, mmap.PROT_READ)
    encrypted = mm.readline().decode('ascii')
    print('\nEncrypted in B', encrypted, end='\n')
    message = decrypt(encrypted)
    print('\nDecrypted in B: ', message, end='\n') 
    os.close(fd)
    os.remove(mm_name)

def decrypt(encrypted):
    key = string.ascii_lowercase
    encrypted = encrypted.split()
    key = ''.join(random.choice(key) for i in range(len(encrypted)))
    decrypted = [ chr(int(a, 2) ^ ord(b)) for (a,b) in zip(encrypted, key) ]
    decrypted = "".join(decrypted)
    return decrypted

main()   
