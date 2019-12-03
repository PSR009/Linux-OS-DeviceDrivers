mutex: mutex.o inc.o dec.o	
	gcc -o mutex mutex.o inc.o dec.o -lpthread
mutex.o: mutex.c
	gcc -o mutex.o -c mutex.c
inc.o: inc.c
	gcc -o inc.o -c inc.c
dec.o: dec.c
	gcc -o dec.o -c dec.c
clean:
	rm -rf *.o mutex