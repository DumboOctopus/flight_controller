
default:
	g++ receiver.cpp uart.cpp main.cpp receiver.h uart.h -o flight

clean:
	rm *.gch flight