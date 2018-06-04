import Crypto.Util.number

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

class RSA:
    p = Crypto.Util.number.getPrime(1024)
    q = Crypto.Util.number.getPrime(1024)
    n = p*q
    phi = (p-1)*(q-1)
    e = 65537
    d = (ModReverse(e,phi)%phi)
    def __init__(self):
        p = Crypto.Util.number.getPrime(1024)
        q = Crypto.Util.number.getPrime(1024)
        n = p*q
        phi = (p-1)*(q-1)
        e = 65537
        d = (ModReverse(e,phi)%phi)
    def encode(self,x):
        return pow(x,self.e,self.n)
    def decode(self,x):
        return pow(x,self.d,self.n)

test = RSA()
print(test.decode(test.encode(333)))
