sig_sem: sig_sem.o in_thread.o proc_thread.o	
	gcc -o sig_sem sig_sem.o in_thread.o proc_thread.o -lpthread
sig_sem.o: sig_sem.c
	gcc -o sig_sem.o -c sig_sem.c
in_thread.o: in_thread.c
	gcc -o in_thread.o -c in_thread.c
proc_thread.o: proc_thread.c
	gcc -o proc_thread.o -c proc_thread.c
clean:
	rm -rf *.o sig_sem