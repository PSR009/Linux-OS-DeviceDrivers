count_sem: count_sem.o thread1.o thread2.o thread3.o	
	gcc -o count_sem count_sem.o thread1.o thread2.o thread3.o -lpthread
count_sem.o: count_sem.c
	gcc -o count_sem.o -c count_sem.c
thread1.o: thread1.c
	gcc -o thread1.o -c thread1.c
thread2.o: thread2.c
	gcc -o thread2.o -c thread2.c
thread3.o: thread3.c
	gcc -o thread3.o -c thread3.c
clean:
	rm -rf *.o count_sem