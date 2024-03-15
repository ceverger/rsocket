/* listen.cpp - реализация метода класса RSocket
                bool listenSock(int maxconn) --- */

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "rsocket.hpp"

	bool RSocket::listenSock(int maxconn)
	{
		/* Метод превращает открытый сокет в прослушивающий */
		
		if(state != opened)
		{
			errstr = listen_error_state;
			return false;
		}
		
		if(listen(fd, maxconn) < 0)
		{
			errstr = strerror(errno);
			return false;
		}
		
		state = listened;
		
		return true;
	}
