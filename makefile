CPP=g++
LINKER=ld
COMPILEFLAGS=-std=c++20 -O3 -fpermissive
ERRORFLAGS=-c -W -Wall -pedantic
LINKERFLAGS=-lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lGLEW
OUT_DIR=bin
BUILD_DIR=build

MKDIR_P = mkdir -p

all: directories main

.PHONY: directories

directories: $(OUT_DIR) $(BUILD_DIR)

$(OUT_DIR):
	$(MKDIR_P) $(OUT_DIR)

$(BUILD_DIR):
	$(MKDIR_P) $(BUILD_DIR)

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