me_sem: me_sem.o inc.o dec.o	
	gcc -o me_sem me_sem.o inc.o dec.o -lpthread
me_sem.o: me_sem.c
	gcc -o me_sem.o -c me_sem.c
inc.o: inc.c
	gcc -o inc.o -c inc.c
dec.o: dec.c
	gcc -o dec.o -c dec.c
clean:
	rm -rf *.o me_sem