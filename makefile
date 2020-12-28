CPP=g++
LINKER=ld
COMPILEFLAGS=-std=c++20 -O3 -fpermissive
ERRORFLAGS=-c -W -Wall -pedantic
LINKERFLAGS=-lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lGLEW
OUT_DIR=bin
BUILD_DIR=build

all: directories main

.PHONY: directories

directories: $(OUT_DIR) $(BUILD_DIR)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

main: main.o
	$(CPP) $(COMPILEFLAGS) -o bin/main build/main.o $(LINKERFLAGS)

main.o: src/main.cpp
	$(CPP) $(COMPILEFLAGS) -o build/main.o src/main.cpp $(ERRORFLAGS)

clean:
	rm -rf build/*.o *~ bin/main

init:
	mkdir ./build ./bin

run:
	./bin/main