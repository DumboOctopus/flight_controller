
default:
	g++ receiver.cpp uart.cpp main.cpp receiver.h uart.h -o flight.o

clean:
	rm *.gch flight.o