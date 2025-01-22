import multiprocessing as mp
import socket as sk

def parsecommand(line):
    (req, num) = line.decode().rstrip("\n").split(" ")
    return (req, int(num))

class Server(mp.Process):
    def __init__(self, socket, lock, pricelist, is_sold):
        super().__init__()
        self.socket = socket
        self.lock = lock
        self.pricelist = pricelist
        self.is_sold = is_sold

    def run(self):
        msg = self.socket.recv(1024)

        while msg != "":
            (req, num) = parsecommand(msg)
            if num < 0 or num >= len(self.pricelist):
                self.socket.send("ERROR\n".encode())

            if req == "PRICE":
                self.price(num)
            elif req == "BUY":
                self.buy(num)
            else:
                self.socket.send("INVALID COMMAND\n".encode())
            
            msg = self.socket.recv(1024)

    def price(self, i):
        self.socket.send((str(self.pricelist[i]) + "\n").encode())

    def buy(self, i):
        with self.lock:
            if self.is_sold[i] == 1:
                self.socket.send("SOLD\n".encode())
            else:
                self.socket.send("OK\n".encode())
                self.is_sold[i] = 1

def startserver(host, port, pricelist):
    s = sk.socket(sk.AF_INET, sk.SOCK_STREAM)
    s.bind((host, port))
    s.listen(1)

    lock = mp.Lock()
    length = len(pricelist)
    is_sold = mp.Array("b", length)
    for i in range(length):
        is_sold[i] = 0

    while True:
        ns, addr = s.accept()
        p = Server(ns, lock, pricelist, is_sold)
        p.start()

if __name__ == "__main__":
    startserver("0.0.0.0", 8000, [10.0, 6.0, 9.0, 3.0])
