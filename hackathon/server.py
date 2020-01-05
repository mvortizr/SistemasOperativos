# install_twisted_rector must be called before importing and using the reactor
#from kivy.support import install_twisted_reactor

#install_twisted_reactor()

from twisted.internet.protocol import Protocol, Factory
from twisted.internet import reactor
import random
import string
import csv
import random
import time
from pprint import pprint

PORT = 9999


class Server(Protocol):
    label = None
    valid_chars_ascii = string.ascii_letters + string.digits + ' .,;:+-*/_!()=@'
    
    def clear_number(self, msg):
        ret = ''
        for x in msg:
            if x in string.digits:
                ret = ret + x
        return ret
    
    def clear_text(self, msg):
        ret = ''
        for x in msg:
            if x in self.valid_chars_ascii:
                ret = ret + x
        return ret


    def randomString(self, str_size):
    #chars = string.ascii_letters + string.digits
        return ''.join(random.choice(self.valid_chars_ascii) for x in range(str_size))

    def dataReceived(self, msg):
        msg = msg.decode('utf-8')
        print ("received:  {}\n".format(msg))
        msg = self.clear_number(msg)
        random.seed(int(msg))
        time.sleep(0.08)
        ret_msg = str(random.randint(0,100))+'\n'
        print ('Responded: ' + ret_msg + '\n')
        self.transport.write(ret_msg.encode('utf-8'))        
        
def main():
    f = Factory()
    f.protocol = Server
    reactor.listenTCP(PORT, f)
    reactor.run()

if __name__ == '__main__':
    main()
    
