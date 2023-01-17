tomorrows: tomorrows.o
	g++ -o tomorrows.exe tomorrows.o
	rm -f tomorrows.o
	./tomorrows.exe

tomorrows.o: tomorrows.cpp
	g++ -c tomorrows.cpp

all: tomorrows.exe ;

clean:
	rm -f tomorrows.exe tomorrows.o
