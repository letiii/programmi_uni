from socket import *

serverPort=12000

serverSocket=socket(AF_INET,SOCK_STREAM)

#apertura del server per richieste di connessione
serverSocket.bind(('',serverPort))
#attesa di richieste di connessione da chiunque su serverPort

serverSocket.listen(1) #welcome socket
print("Server è pronto per ricevere connessioni: ")

while True:
    #accept() connection socket, indirizzo client
    connectionSocket, clientAddress=serverSocket.accept() #active open
    #connection socket != welcome socket

    print("Server connesso con: ",clientAddress)
    while True:
        messaggio=connectionSocket.recv(1024)
        messaggio=messaggio.decode('utf-8')
        if messaggio=='.':
            break
        messaggio=messaggio.upper()+ ' oid ocrop'
        connectionSocket.send(messaggio.encode('utf-8'))
    connectionSocket.close()

