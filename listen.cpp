/* listen.cpp - реализация метода класса RSocket для настройки
                прослушивания сокета ------------------------- */

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "rsocket.hpp"

	bool RSocket::listenSock(int maxconn)
	{
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
