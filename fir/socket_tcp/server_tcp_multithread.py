from socket import *
from threading import *

def handler(connectionSocket):
    while True:
        messaggio=connectionSocket.recv(1024)
        if messaggio.decode('utf-8')=='.':
            break
        messaggioMaiusc=messaggio.decode('utf-8').upper()
        connectionSocket.send(messaggioMaiusc)
    connectionSocket.close()


serverPort=12000
serverSocket=socket(AF_INET,SOCK_STREAM)
serverSocket.setsockopt(SOL_SOCKET,SO_REUSEADDR,1)

serverSocket.bind(('',serverPort))
serverSocket.listen(1)


while True:
    print("server pronto a ricevere")
    newSocket, addr =serverSocket.accept()

    thread=Thread(target=handler, args=(newSocket,  ))
    thread.start()

