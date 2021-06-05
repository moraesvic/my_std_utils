FLAGS_DEV=-Wall -g -pg
FLAGS_PROD=-Wall -O2
LIBS=../libs

heapsort: heapsort.c my_random.o my_string.o
	gcc $(FLAGS_DEV) heapsort.c my_random.o my_string.o -o heapsort

my_random.o: $(LIBS)/my_random.c $(LIBS)/my_random.h
	gcc $(FLAGS_PROD) -c $(LIBS)/my_random.c -o my_random.o

my_string.o: $(LIBS)/my_string.c $(LIBS)/my_string.h
	gcc $(FLAGS_PROD) -c $(LIBS)/my_string.c -o my_string.o

clean:
	rm my_random.o my_string.o gmon.out