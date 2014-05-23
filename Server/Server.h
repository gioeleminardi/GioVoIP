#include "globals.h"

#pragma once
class Server
{
private:
	SOCKET initSocket();
	void startUDPlisten(SOCKET s);
public:
	Server(void);
	~Server(void);
};

