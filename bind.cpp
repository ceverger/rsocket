/* bind.cpp - реализация метода класса RSocket для связывания сокета
              с ip-адресом и портом -------------------------------- */
				  
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "rsocket.hpp"

	bool RSocket::bindSock(const char *ipaddr, int port)
	{
		if(state != opened)
		{
			errstr = bind_error_state;
			return false;
		}
		
		socklen_t addr_size = 0;
		void *p_ipaddr = nullptr;
		struct sockaddr *p_addr;
		struct sockaddr_in addr4;
		struct sockaddr_in6 addr6;
		
		int family = getFamily(m_sockType);
		
		bzero(&addr4, sizeof(addr4));
		bzero(&addr6, sizeof(addr6));

		switch(family)
		{ 
			case AF_INET: 
				addr_size = sizeof(addr4);
				p_addr = (struct sockaddr *) &addr4;
				addr4.sin_family = family;
				addr4.sin_port = htons(port);
				p_ipaddr = (void *) &addr4.sin_addr;
				break;

			case AF_INET6: 
				addr_size = sizeof(addr6);
				p_addr = (struct sockaddr *) &addr6; 
				addr6.sin6_family = family;
				addr6.sin6_port = htons(port);
				p_ipaddr = (void *) &addr6.sin6_addr;
				break;
				
		} // switch(family)
		
		if(inet_pton(family, ipaddr, p_ipaddr) < 0)
		{
			errstr = strerror(errno);
			return false;
		}		

		if(bind(fd, p_addr, addr_size) < 0)
		{
			errstr = strerror(errno);
			return false;
		}
		
		m_port = port;
		
		for(int i = 0; i < strlen(ipaddr); ++i)
			m_address[i] = ipaddr[i];
		
		return true;
	}
