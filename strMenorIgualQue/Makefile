FLAGS_DEV=-Wall -g -pg
FLAGS_PROD=-Wall -O2
LIBS=../libs

main: my_string.o main.c
	gcc $(FLAGS_DEV) my_string.o main.c -o main

my_string.o: $(LIBS)/my_string.c $(LIBS)/my_string.h
	gcc $(FLAGS_PROD) -c $(LIBS)/my_string.c -o my_string.o

clean:
	rm my_string.o gmon.out
