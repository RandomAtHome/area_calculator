.PHONY: clean main.o 
TARGET = main
OBJ = functions.o main.o
METHOD ?= 1

all: $(TARGET)

binary: $(TARGET)

chords: METHOD = 2
chords: $(TARGET)
	
clean:
	rm -f $(TARGET) *.o

functions.o: functions.asm
	nasm -f elf32 functions.asm -o functions.o

main.o: main.c
	gcc -Wall -D METHOD=$(METHOD) -o main.o -c main.c -m32

$(TARGET): $(OBJ)
	gcc -Wall -o $(TARGET) $(OBJ) -m32
