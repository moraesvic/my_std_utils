SRC=lemma.c lemma.h minofthree.o sort.o rand.o alphabet.o

make: $(SRC)
	gcc -O3 -o lemma $(SRC)

debug: $(SRC)
	gcc -O0 -g -D DEBUG_FLAG -o debug $(SRC)

minofthree.o: minofthree.asm
	nasm -f elf64 -o minofthree.o minofthree.asm

sort.o: sort.c sort.h
	gcc -c -O3 -o sort.o sort.c

rand.o: rand.c rand.h
	gcc -c -O3 -o rand.o rand.c

alphabet.o: alphabet.c alphabet.h
	gcc -c -O3 -o alphabet.o alphabet.c