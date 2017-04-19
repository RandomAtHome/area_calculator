.PHONY: all clean
TARGET = main
OBJ = f1.o f2.o f3.o main.o
METHOD ?= 1

all: $(TARGET)

binary: clean $(TARGET)

chords: METHOD = 2
chords: clean $(TARGET)
	
clean:
	rm -f $(TARGET) *.o

f1.o: f1.asm
	nasm -f elf32 f1.asm -o f1.o

f2.o: f2.asm
	nasm -f elf32 f2.asm -o f2.o

f3.o: f3.asm
	nasm -f elf32 f3.asm -o f3.o

main.o: main.c
	gcc -Wall -D METHOD=$(METHOD) -o main.o -c main.c -m32

$(TARGET): $(OBJ)
	gcc -Wall -o $(TARGET) $(OBJ) -m32
