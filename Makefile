
default:
	g++ receiver.cpp uart.cpp main.cpp receiver.h uart.h -o flight.o
dummy:
	g++ uart.cpp uart.h uartTest.cpp -DDUMMY=1
uart:
	g++ uart.cpp uart.h uartTest.cpp -lwiringPi -Wall -o utest.o

clean:
	rm *.gch flight.o
