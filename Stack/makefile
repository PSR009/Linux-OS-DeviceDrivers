final: main.o push.o pop.o TOS.o disp.o	
	gcc -o final main.o push.o pop.o TOS.o disp.o
main.o: main.c
	gcc -o main.o -c main.c
push.o: push.c
	gcc -o push.o -c push.c
pop.o: pop.c
	gcc -o pop.o -c pop.c
TOS.o: TOS.c
	gcc -o TOS.o -c TOS.c
disp.o: disp.c
	gcc -o disp.o -c disp.c
clean:
	rm -rf *.o final