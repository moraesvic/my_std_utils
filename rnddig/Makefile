FLAGS_DEV=-Wall -g -pg
FLAGS_PROD=-Wall -O2
LIBS=../libs

make: my_random.o main.c
	gcc $(FLAGS_PROD) my_random.o main.c -o rnddig

my_random.o: $(LIBS)/my_random.c $(LIBS)/my_random.h
	gcc $(FLAGS_PROD) -c $(LIBS)/my_random.c -o my_random.o

install: rnddig
	echo "Installing rnddig for all users. Please make sure you're running as sudo"
	sudo mv rnddig /usr/local/bin/

clean:
	rm my_random.o