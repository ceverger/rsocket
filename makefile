all:
	g++ -g -fpic -c accept.cpp    -o ../build/accept.o    -I .
	g++ -g -fpic -c bind.cpp      -o ../build/bind.o      -I .
	g++ -g -fpic -c connect.cpp   -o ../build/connect.o   -I .
	g++ -g -fpic -c listen.cpp    -o ../build/listen.o    -I .
	g++ -g -fpic -c openio.cpp    -o ../build/openio.o    -I .
	g++ -g -fpic -c rddata.cpp    -o ../build/rddata.o    -I .
	g++ -g -fpic -c rsocket.cpp   -o ../build/rsocket.o   -I .
	g++ -g -fpic -c wrdata.cpp    -o ../build/wrdata.o    -I .
	g++ -shared ../build/*.o   -o ../build/librsocket.so.0
