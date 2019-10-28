import socketserver
from numpy import base_repr
import sys


class Converter:
    def __init__(self, filename):
        self.ip_list = open(filename, 'r').read()
        self.ip_list = self.ip_list.split("\n")

    def present(self, id):
        return self.ip_list[id]
    
    def present_all(self):
        string = ''
        for i in self.ip_list:
            string += str(i) + '\n'
        return string

    def convert(self, ip):
        ip = ip.split(".")

        binary = f"{base_repr(int(ip[0]), 2)}.{base_repr(int(ip[1]), 2)}" \
                 f".{base_repr(int(ip[2]), 2)}.{base_repr(int(ip[3]), 2)}"

        hexadem = f"{base_repr(int(ip[0]), 16)}.{base_repr(int(ip[1]), 16)}" \
                 f".{base_repr(int(ip[2]), 16)}.{base_repr(int(ip[3]), 16)}"

        return {"bin": binary,
                "hex": hexadem}


host = '0.0.0.0'
port = 8800
addr = (host, port)
ip_converter = Converter("ip.list")

class MyTCPHandler(socketserver.StreamRequestHandler):
    def handle(self):
        self.data = self.request.recv(512)
        print('client send: ' + str(self.data))
        if (bytes.decode(self.data) == 'file'):
            print("AAAAAA")
            message = ip_converter.present_all().encode("ascii")
            
            self.request.sendall(message)
        else:
            ip = ip_converter.present(int(self.data))
            resp = ip_converter.convert(ip)
            message = f"{resp['bin']}\n{resp['hex']}".encode("ascii")
            self.request.sendall(message)


if __name__ == "__main__":
    server = socketserver.TCPServer(addr, MyTCPHandler)

    print('Starting server...')
    server.serve_forever()
