/* rsocket.cpp - реализация конструкторов, деструкторов и некоторых
                 других методов и класса RSocket ------------------ */
					  
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "rsocket.hpp"	
	
	RSocket::RSocket() : IODevice()
	{
		/* Конструктор класса по умолчанию */
		
		typeID = SocketType;		
		state = undef;		
		m_sockType = undef;
		m_ipprType = undef;
		
		m_port = -1;
		
		for(int i = 0; i < addrlen; ++i)
			m_address[i] = '\0';
	}
	
	RSocket::RSocket(int sockType, int ipprType) : IODevice()
	{
		/* Пользовательский конструктор класса */
		
		typeID = SocketType;		
		state = undef;
		
		switch(sockType)
		{
			case Tcp: m_sockType = Tcp; break;
			case Udp: m_sockType = Udp; break;
			default: m_sockType = Tcp;
	   }
		
		switch(ipprType)
		{
			case ipv4: m_ipprType = ipv4; break;
			case ipv6: m_ipprType = ipv6; break;
			default: m_ipprType = ipv4;
		}
		
		m_port = -1;
		
		for(int i = 0; i < addrlen; ++i)
			m_address[i] = '\0';
	}
	
	void RSocket::reset()
	{
		/* Сброс всех данных о сокете */
		
		if(state != closed && state != undef) return;
		
		state = undef;
		
		m_sockType = undef;
		m_ipprType = undef;
		
		m_port = -1;
		
		for(int i = 0; i < addrlen; ++i)
			m_address[i] = '\0';		
	}
	
	int RSocket::getFamily(int sockIppr) const
	{
		switch(sockIppr)
		{
			case ipv4: return AF_INET;
			case ipv6: return AF_INET6;
			default:   return -1;
		}
	}
	
	int RSocket::getType(int sockType) const
	{
		switch(sockType)
		{
			case Tcp: return SOCK_STREAM;
			case Udp: return SOCK_DGRAM;
			default:  return -1;
		}
	}
	
	int RSocket::getProtocol(int sockType) const
	{
		switch(sockType)
		{
			case Tcp: return IPPROTO_TCP;
			case Udp: return IPPROTO_UDP;
			default:  return -1;
		}		
	}
