rec_mutex: rec_mutex.o inc.o dec.o	
	gcc -o rec_mutex rec_mutex.o inc.o dec.o -lpthread
rec_mutex.o: rec_mutex.c
	gcc -o rec_mutex.o -c rec_mutex.c
inc.o: inc.c
	gcc -o inc.o -c inc.c
dec.o: dec.c
	gcc -o dec.o -c dec.c
clean:
	rm -rf *.o rec_mutex