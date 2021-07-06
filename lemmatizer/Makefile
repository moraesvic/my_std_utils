SRC=lemma.c lemma.h minofthree.o

make: $(SRC)
	gcc -O3 -o lemma $(SRC)

debug: $(SRC)
	gcc -O0 -g -o debug $(SRC)

minofthree.o: minofthree.asm
	nasm -f elf64 -o minofthree.o minofthree.asm