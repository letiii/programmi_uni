from socket import *

serverName='localhost'
serverPort=12000

#socket del client del tipo tcp
clientSocket=socket(AF_INET,SOCK_STREAM)

clientSocket.connect((serverName,serverPort)) #questo si occupa di aprire la connessione, syn-> synack<- ack->, poi comunica al SO la riuscita

while True: #modifico per chiudere connessione dopo aver ricevuto "."

    messaggio=input("Inserisci frase: (inserisci. per terminare la connessione) ")
    messaggio=messaggio.encode('utf-8')

    clientSocket.send(messaggio.encode('utf-8')) #non ci serve sendto come udp
    if messaggio.decode('utf-8')=='.': #si può anche fare '.'.encode('utf-8')
        break
    messaggioModificato=clientSocket.recv(1024) #diverso da udp
    print("Dal server: ",messaggioModificato.decode('utf-8'))

clientSocket.close()

#nc -t -l n.porta per testare i socket client senza scrivere un server
#e si possono fare catture con wireshark

