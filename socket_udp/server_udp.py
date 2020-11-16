from socket import *

serverPort =12000
serverSocket=socket(AF_INET,SOCK_DGRAM)
serverSocket.bind(('',serverPort))

print("yayyy il server è pronto a ricevere \n")

while True:
    message, clientAddress=serverSocket.recvfrom(2048)
    print ("Datagramma (udp) da: ",clientAddress)
    message=message.decode('utf-8')
    modifiedMessage=message.upper()+'  hehehehe'
    serverSocket.sendto(modifiedMessage.encode('utf-8'),clientAddress)
