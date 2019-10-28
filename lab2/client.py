import socket
import sys

host = 'localhost'
port = 8800
addr = (host, port)

tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
tcp_socket.connect(addr)

data = input('Write to server: ')
if data == '':
    data = str.encode("file")
    tcp_socket.send(data)
    data = bytes.decode(data)
else:
    # encode - recodes the entered data in bytes,
    # decode - back
    data = str.encode(data)
    tcp_socket.send(data)
    data = bytes.decode(data)

data = tcp_socket.recv(1024)
data = data.decode("ascii")

print(data)

tcp_socket.close()
