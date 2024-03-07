/* openio.cpp - реализация методов класса RSocket для 
					 открытия и закрытия сокета ---------- */
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "rsocket.hpp"	
					 
	bool RSocket::openIO()
	{
		/* Открытие сокета и получение файлового дескриптора ввода-вывода */
		
		if(state == opened)
		{
			errstr = openio_error_state;
			return false;
		}
		
		if(m_sockType == undef)
			{
				errstr = openio_error_socktype;
				return false;		
			}
			
		if(m_ipprType == undef)
			{
				errstr = openio_error_ipprtype;
				return false;		
			}
			
		fd = socket(
						getFamily(m_ipprType), 
						getType(m_sockType), 
						getProtocol(m_sockType)
					  );
			
		if(fd < 0)
		{
			errstr = strerror(errno);
			return false;
		}
		
		state = opened;
		
		return true;
	}
	
	
	bool RSocket::closeIO()
	{
		if(close(fd))
		{
			errstr = strerror(errno);
			return false;			
		}
		
		state = closed;
		fd = -1;
		
		m_port = -1;
		
		for(int i = 0; i < addrlen; ++i)
			m_address[i] = '\0';
				
		return true;
	}
