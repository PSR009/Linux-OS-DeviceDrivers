comp = gcc
main: main.o add.o sub.o
	$(comp) -o main main.o add.o sub.o
main.o: main.c
	$(comp) -o main.o -c main.c
add.o: add.c
	$(comp) -o add.o -c add.c
sub.o: sub.c
	$(comp) -o sub.o -c sub.c
clean:
	rm -rf *.o main