// rddata.cpp - реализация методов чтения файла класса RFile

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "rsocket.hpp"

        int RSocket::rddata(char *buf, int size)
        {
                if(state != connected)
                {  errstr = rddata_error_state;
                        return -1;
                }

                if(buf == nullptr)
                {
                        errstr = rddata_error_buffer;
                        return -1;
                }

                int ret = read(fd, buf, size);
                if(ret < 0) errstr = strerror(errno);
                return ret;
        }
