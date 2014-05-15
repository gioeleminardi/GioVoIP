#include "Server.h"

int Server::initSocket(){
	WSADATA wsaData;
	struct addrinfo *result = NULL, *ptr = NULL, hints;
	SOCKET listenSocket = INVALID_SOCKET;

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