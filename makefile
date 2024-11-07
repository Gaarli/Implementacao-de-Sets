all: main.o ArvB.o set.o 
	gcc main.o ArvB.o set.o  -o main -std=c99 -Wall

main.o:
	gcc -c main.c

ArvB.o:
	gcc -c ArvB.c

set.o:
	gcc -c set.c 

run:all
	./main
	
clean:
	rm -rf *.o main