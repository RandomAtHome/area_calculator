.PHONY: all clean
TARGET = main
OBJ = main.o f1.o f2.o f3.o

all: $(TARGET)

	
clean:
	rm -r $(TARGET) *.o

f1.o: f1.asm
	nasm -f elf32 f1.asm -o f1.o

f2.o: f2.asm
	nasm -f elf32 f2.asm -o f2.o

f3.o: f3.asm
	nasm -f elf32 f3.asm -o f3.o

main.o: main.c
	gcc -Wall -o main.o -c main.c -m32

$(TARGET): $(OBJ)
	gcc -Wall -o $(TARGET) $(OBJ) -m32
