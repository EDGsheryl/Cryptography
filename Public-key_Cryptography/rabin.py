import Crypto.Util.number

cryptolength = 1024

class Rabin:
    p = Crypto.Util.number.getPrime(cryptolength)
    while (p%4!=3):
        p = Crypto.Util.number.getPrime(cryptolength)
    q = Crypto.Util.number.getPrime(cryptolength)
    while (q%4!=3):
        q = Crypto.Util.number.getPrime(cryptolength)
    n = p*q
    
    def __init__(self):
        p = Crypto.Util.number.getPrime(cryptolength)
        while (p%4!=3):
            p = Crypto.Util.number.getPrime(cryptolength)
        q = Crypto.Util.number.getPrime(cryptolength)
        while (q%4!=3):
            q = Crypto.Util.number.getPrime(cryptolength)
        n = p*q
    def encode(self,x):
        return pow(x,2,self.n)
    def decode(self,x):
        ret = []
        ret.append(pow(x,(self.p+1)//4,self.p))
        ret.append(pow(x,(self.q+1)//4,self.q))
        ret.append((self.p-pow(x,(self.p+1)//4,self.p))%self.p)
        ret.append((self.q-pow(x,(self.q+1)//4,self.q))%self.q)
        return ret

test = Rabin()
print(test.decode(test.encode(333)))
