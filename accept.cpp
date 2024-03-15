/* accept.cpp - реализация метода класса RSocket
                acceptSock(RSocket & rsocket) -- */

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "rsocket.hpp"
					  
	bool RSocket::acceptSock(RSocket & rsocket)
	{
		if(state != listened)
		{
			errstr = accept_error_state;
			return false;
		}

		if(rsocket.state != undef &&  rsocket.state != closed)
		{
			errstr = accpet_error_socket;
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
				addr4.sin_port = htons(m_port);
				p_ipaddr = (void *) &addr4.sin_addr;
				break;

			case AF_INET6: 
				addr_size = sizeof(addr6);
				p_addr = (struct sockaddr *) &addr6; 
				addr6.sin6_family = family;
				addr6.sin6_port = htons(m_port);
				p_ipaddr = (void *) &addr6.sin6_addr;
				break;
				
		} // switch(family)

		rsocket.m_sockType = m_sockType;
		rsocket.m_ipprType = m_ipprType;
		
		rsocket.fd = accept(fd, p_addr, &addr_size);
		
		if(rsocket.fd < 0)
		{
			errstr = strerror(errno);
			return false;			
		}
		
		switch(family)
		{ 
			case AF_INET: 
				rsocket.m_port = ntohs(addr4.sin_port); break;

			case AF_INET6: 
				rsocket.m_port = ntohs(addr6.sin6_port); break;
				
		} // switch(family)
		
		if(inet_ntop(family, p_ipaddr, rsocket.m_address, addrlen) < 0)
		{
			errstr = strerror(errno);
			return false;
		}
		
		rsocket.state = connected;
		
		return true;
	}
 					   
