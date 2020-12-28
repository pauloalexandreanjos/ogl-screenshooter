CPP=g++
LINKER=ld
COMPILEFLAGS=-std=c++20 -O3 -fpermissive
ERRORFLAGS=-c -W -Wall -pedantic
LINKERFLAGS=-lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lGLEW

all: main

main: main.o
	$(CPP) $(COMPILEFLAGS) -o bin/main build/main.o $(LINKERFLAGS)

main.o: src/main.cpp
	$(CPP) $(COMPILEFLAGS) -o build/main.o src/main.cpp $(ERRORFLAGS)

clean:
	rm -rf build/*.o *~ bin/main

run:
	./bin/main