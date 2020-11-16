from socket import *


serverName='localhost' #nome simbolico e numero porta server
serverPort=12000

clientSocket=socket(AF_INET,SOCK_DGRAM) #creo socket udp

message=input('inserisci lettere: ') #input da tastiera

clientSocket.sendto(message.encode('utf-8'), (serverName,serverPort))
#manda messaggio nel socket, con indicato nome e porta del server

modifiedMessage, serverAddress=clientSocket.recvfrom(2048)
#socket si pone in ascolto e poi mette il messaggio elaborato in una stringa

modifiedMessage=modifiedMessage.decode('utf-8')

print(modifiedMessage)

clientSocket.close() #chiusura socket dopo la stampa
