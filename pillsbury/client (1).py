

#imports 
import os
import sys
import socket
from Crypto.Cipher import AES
from Crypto.Hash import SHA1

#network config
HOST = '0.0.0.0'  # this should likley be a env variable for docker deployment/kubernetees secrets
PORT = 65432        # Port to listen on (non-privileged ports are > 1023)


serverNonce =b''
clientNonce =b''


#prints a byte as 2 hex digits with a trailing space
#(pythons built in hex formating didnt do specifically what i wanted)
def printByte(inByte):
    byteint = int(inByte)
    if(byteint<16):
        print(0,end='')
    print('%x' % byteint,end=' ')

#prints 
def printByteArray(inByteArray):
    for i in range(0,len(inByteArray)):
        printByte(inByteArray[i])

#prints section of byte array
def printByteArrayRange(inByteArray,start,end):
    for i in range(start,end):
        printByte(inByteArray[i])

        
#AES encrypts a 16 byte text with key
def EncryptBlock(key,text):
    mode = AES.MODE_ECB #simplest "block" mode
    encryptor = AES.new(key,mode)
    return bytearray(encryptor.encrypt(text))

#runs the cipher
def cipher_encrypt(key,iv,text):
    text = iv + text 
    for index in range(0,len(text)-16):
        block = text[index:index+16]
        encryptedBlock = EncryptBlock(key,block)
        xorResult = text[index+16] ^ encryptedBlock[0]
        newText = text
        newText[index+16] = xorResult
        text = newText
    return text[16:len(text)]


#decrypts given the text, key, and iv
def cipher_decrypt(key,iv,text):
    newtext = text
    text = iv + text 
    for index in range(0,len(text)-16):
        block = text[index:index+16]
        encryptedBlock = EncryptBlock(key,block)
        xorResult = text[index+16] ^ encryptedBlock[0]  #this is the unencryptd byte
        newtext[index] = xorResult
    return newtext


#socket globals
Socket = None
connectedAddress = None

#open a socket
def createSocket():
    global Socket
    global connectedAddress
    #handle socket connections 
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as Socket:
        Socket.bind((HOST, PORT))
        Socket.listen()
        print("listening on port " + str(PORT))
        #Socket, connectedAddress = Socket.accept()

#connect to a socket
def connectSocket():
    global Socket
    #handle socket connections 
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as Socket:
        Socket.connect((HOST, PORT))
        print("listening on port " + str(PORT))

#function that handles the protocols 
def handleCommand(message):
    global serverNonce
    global clientNonce
    command = int.from_bytes(message[0:2],byteorder='big', signed=False)
    body = message[2:len(message)]
    if(command ==0):
        print("Disconected from server")
        exit()
    #print command, pass the rest of the message to stdout if a client 
    if(command == 2):
        print(str(body,encoding="utf-8"))
    #request username command
    if(command == 3):
        getAndSendUserName()
    #server accepted username
    if(command == 5):
        sendNonceCommand()
    #nonce command
    if(command == 6):
        print()
        serverNonce = body
        getAndSendPassword()



#function that sends all bytes over the socket
def sendBytesOverSocket(sendBytes):
    global Socket
    Socket.sendall(sendBytes)

def sendDisconect():
    global Socket
    try:
        sendBytesOverSocket(b'\0\0')
    except Exception as e:
        pass
    Socket.close()
    print("conection closed")



#sends a random 16 byte int for use as a nonce
def sendNonceCommand():
    global serverNonce
    global clientNonce
    #creates the nonce
    nonce = os.urandom(16)
    msg = bytearray(b'\0\6') + nonce
    #save the  nonce 
    clientNonce = nonce
    sendBytesOverSocket(msg)
    None

def getAndSendUserName():
    username = input("UserName:")
    username = bytearray(username,encoding='utf-8', errors='strict')
    username = bytearray(b'\0\4') + username
    sendBytesOverSocket(username)


#client sends password
def getAndSendPassword():
    print("server is requesting password")
    password = input("Password:")
    password = bytearray(password,encoding='utf-8', errors='strict')
    key = KDF(password)
    iv = bytearray(b'\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0')

    authToken = cipher_encrypt(key,iv,clientNonce)

    msg = b'\0\7' + authToken

    sendBytesOverSocket(msg)
    
    None

#------------------------------------------------------------------
#This function is server only code, do not distribute to clients!             
#               -SUPER SECURE server TM dev 
#------------------------------------------------------------------


#def validatePassword(auth):
#    password = getUserPassword()
#    password = bytearray(password,encoding='utf-8', errors='strict')
#    key = KDF(password)
#    iv = bytearray(b'\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0')
#    decryptResult = cipher_decrypt(key,iv,auth)
#    print()
#    if(decryptResult == clientNonce):
#        print("right password!")
#        printTextClientCommand("Here is the super secret code\n")
#        printTextClientCommand(secret)
#        sendDisconect()
#    else:
#        print("wrong password!")
#        sendDisconect()

#makes a 16 byte key from the server nonce and the password
def KDF(password):
    global serverNonce
    hasher = SHA1.new()
    hasher.update(password)
    hasher.update(serverNonce)
    key = hasher.digest()
    key = bytearray(key[0:16])
    print()
    return key




def clientBehaviour():
    global Socket
    print("please enter server address")
    HOST = input()
    print("please enter server port")
    PORT = int(input())
    #connectSocket()
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as Socket:
        Socket.connect((HOST, PORT))
        print("listening on port " + str(PORT))  
        #the client just waits for instructions from server forever
        while True:
            data = Socket.recv(100)
            handleCommand(data)
    None


def main():
    print("Running app")
    args = sys.argv
    print(args)
    print("running as client")
    clientBehaviour()
    None
main()