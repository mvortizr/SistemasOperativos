import os,sys,random,string
pipe_name = 'buffer'
seed= sys.argv[1] 
random.seed(seed) 


def main():    
    pipein = open(pipe_name, 'r')
    encrypted = pipein.readline()
    print('\nEncrypted in B', encrypted, end='\n')
    message = decrypt(encrypted)
    print('\nDecrypted in B: ', message, end='\n') 
    os.remove(pipe_name)

def decrypt(encrypted):
    key = string.ascii_lowercase
    encrypted = encrypted.split()
    key = ''.join(random.choice(key) for i in range(len(encrypted)))
    decrypted = [ chr(int(a, 2) ^ ord(b)) for (a,b) in zip(encrypted, key) ]
    decrypted = "".join(decrypted)
    return decrypted
   

main()