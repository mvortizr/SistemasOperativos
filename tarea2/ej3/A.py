import os,sys,random,string

pipe_name = 'buffer'
seed= sys.argv[1]
random.seed(seed)   


def main():
    os.mkfifo(pipe_name)   
    pipeout = open(pipe_name, 'w')
    message = input('Enter your message: ') 
    encrypted = encrypt(message)
    pipeout.write(encrypted)
    pipeout.close()  


def encrypt(message):
    key = string.ascii_lowercase
    key = ''.join(random.choice(key) for i in range(len(message))) 
    encrypted = [ format((ord(a) ^ ord(b)),'b') for (a,b) in zip(message, key) ] 
    encrypted = " ".join(encrypted)
    return encrypted


main()



