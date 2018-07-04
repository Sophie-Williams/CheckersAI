output: main.o Checkers.o Graphics.o
		g++ main.o Checkers.o Graphics.o -o output

main.o: main.cpp
		g++ -c main.cpp

Checkers.o: Checkers.cpp Checkers.h
		g++ -c Checkers.cpp

Graphics.o: Graphics.cpp Graphics.h
		g++ -c Graphics.cpp

clean:
		rm *.o output
