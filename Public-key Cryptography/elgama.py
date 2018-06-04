import Crypto.Util.number

cryptolength = 128

def ext_euclid(a, b):
     if b == 0:
         return 1, 0, a
     else:
         x, y, q = ext_euclid(b, a % b) # q = gcd(a, b) = gcd(b, a%b)
         x, y = y, (x - (a // b) * y)
         return x, y, q

def ModReverse(a,n):
    #ax=1(mod n)
    x,y,q = ext_euclid(a,n)
    return x

class Elgama:
    p = Crypto.Util.number.getPrime(cryptolength)
    g = Crypto.Util.number.getRandomNBitInteger(cryptolength//2)
    x = Crypto.Util.number.getRandomNBitInteger(cryptolength//2)
    y = pow(g,x,p)
    c1 = 0
    c2 = 0

    def __init__(self):
        p = Crypto.Util.number.getPrime(cryptolength)
        g = Crypto.Util.number.getRandomNBitInteger(cryptolength//2)
        x = Crypto.Util.number.getRandomNBitInteger(cryptolength//2)
        y = pow(g,x,p)
        c1 = 0
        c2 = 0

    def encode(self,x):
        ret = []
        k = Crypto.Util.number.getRandomNBitInteger(cryptolength//2)
        c1 = pow(self.g,k,self.p)
        c2 = pow(self.y,k,self.p)
        ret.append(c1)
        ret.append((c2*x)%self.p)
        return ret

    def decode(self,x):
        ret = (x[1]*ModReverse(pow(x[0],self.x,self.p),self.p))%self.p
        return ret

test = Elgama()
print(test.decode(test.encode(333)))
