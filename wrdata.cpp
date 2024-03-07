// wrdata.cpp - реализация методов записи в файл класса RFile

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "rsocket.hpp"

	int RSocket::wrdata(const char *buf, int size)
	{
		if(state != opened) return -1;
		if(buf == nullptr)  return -1;
		int ret = write(fd, buf, size);
		if(ret < 0) errstr = strerror(errno);
		return ret;
	}
