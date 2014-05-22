#include "Server.h"

int Server::initSocket(){
	WSADATA wsaData;
	struct addrinfo *result = NULL, *ptr = NULL, hints;
	SOCKET listenSocket = INVALID_SOCKET;
	SOCKADDR_STORAGE from;
	int bytecount, fromlen, retval;
	char buffer[1024],     
	servstr[NI_MAXSERV],
    hoststr[NI_MAXHOST];

	int iResult = WSAStartup(MAKEWORD(3,2), &wsaData);
	if(iResult != 0){
		printf("WSAStartup fallito: %d\n", iResult);
		return -1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
	hints.ai_flags = AI_PASSIVE;

	iResult = getaddrinfo(NULL, PORTA, &hints, &result);
	if(iResult != 0){
		printf("getaddrinfo fallito: %d\n", iResult);
		return -1;
		WSACleanup();
	}

	listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if(listenSocket == INVALID_SOCKET){
		printf("Errore socket(): %s\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return -1;
	}

	iResult = bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);
	if(iResult == SOCKET_ERROR){
		printf("Fallito il bind del socket: %s\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(listenSocket);
		WSACleanup();
		return -1;
	}
	freeaddrinfo(result);
	for(;;){
		fromlen = sizeof(from);
		bytecount = recvfrom(listenSocket, buffer, sizeof(buffer), 0, (SOCKADDR *)&from, &fromlen);
		if (bytecount == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAECONNRESET) {
				fprintf(stderr, "recvfrom failed; %d\n", WSAGetLastError());
				freeaddrinfo(result);
				closesocket(listenSocket);
				WSACleanup();
			} else {
				continue;
			}
		}
		retval = getnameinfo(
                                (SOCKADDR *)&from,
                                fromlen,
                                hoststr,
                                NI_MAXHOST,
                                servstr,
                                NI_MAXSERV,
                                NI_NUMERICHOST | NI_NUMERICSERV
                                );
		if (retval != 0){
			fprintf(stderr, "getnameinfo failed: %d\n", retval);
			freeaddrinfo(result);
			closesocket(listenSocket);
			WSACleanup();
        }
		printf("read %d bytes from host %s and port %s\n", bytecount, hoststr, servstr);
	}

	return 0;
}

Server::Server(void){
	if(initSocket() == 0){
		printf("Socket inizializzato\n");
		printf("Socket bindato\n");
	}
}


Server::~Server(void)
{

}