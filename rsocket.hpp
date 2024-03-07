// rsocket.hpp - описание класса RSocket для работы с сокетами

#include "iodevice.hpp"

#ifndef R_SOCKET_HPP
#define R_SOCKET_HPP

#define openio_error_state    "RSocket::openio:  Socket it was open!"
#define openio_error_socktype "RSocket::openio:  Socket type is undef!"
#define openio_error_ipprtype "RSocket::openio:  IP protocol is undef!"
#define connect_error_state   "RSocket::connect: Socket is not opened!"
#define bind_error_state      "RSocket::bind:    Socket is not opened!"
#define listen_error_state    "RSocket::listen:  Socket is not opened!"
#define accept_error_state    "RSocket::accept:  Socket is not listened!"
#define accpet_error_socket   "RSocket::accept:  Socket is not clear!"


	class RSocket : public IODevice
	{
		public:
		
			enum 
			{ 				
				undef = 0,   // Неопределенное состояние
				addrlen = 14 // Максимальная длина IP-адреса
			};
			
			enum /* Целочисленные идентификаторы типа сокета */
			{ 			
				Tcp = 1, 
				Udp = 2 
			};
			
			enum /* Целочисленные идентификаторы версий протокола IP */
			{	
				ipv4 = 1, 
				ipv6 = 2 
			};
			
			enum /* Целочисленные идентификаторы состояния сокета */
			{	
				closed = 1, 
				opened = 2, 
				connected = 3,
				listened = 4
			};
			
		private:
		
			int state; // Текущее состояние сокета
			
			int m_sockType; // Тип сокета
			int m_ipprType; // Тип ip-протоокола
			
			int m_port;              // Порт сокета
			char m_address[addrlen]; // Адресс сокета
			
		public:
		
			/* Конcтрукторы и деструкторы класса */
		
				RSocket();
				RSocket(int sockType, int ipprType);
				virtual ~RSocket() {}
				
			/* Селекторы класса */
			
				int getState()    const { return state;      }
				int getSockType() const { return m_sockType; }
				int getSockIppr() const { return m_ipprType; }
				
				int getPort() const { return m_port; }
				const char *getAddress() const { return m_address; }
				
			/* Модификаторы класса */
			
				bool setSockType(int sockType);
				bool setSockIppr(int sockIppr);
	
				bool setPort(int port);
				bool setAddress(const char *address);
			
			/* Методы для открытия и закрытия файлов */
			
				bool openIO();
				bool closeIO();
			
			/* Методы чтения и записи в файл */
			
				int rddata(char *buf, int size);				
				int wrdata(const char *buf, int size);
				
			/* Другие методы класса */
			
				void reset();
				
				int getFamily(int sockIppr) const;
				int getType(int sockType) const;
				int getProtocol(int sockIppr) const;
				
				bool listenSock(int maxconn);
				bool acceptSock(RSocket & rsocket);
				bool bindSock(const char *ipaddr, int port);
				bool connectToHost(const char *ipaddr, int port);
				
			
	}; // class RSocket

#endif // R_SOCKET_HPP
