CC=gcc

mydb:main.o dbproc.o
	gcc -o mydb main.o dbproc.o
main.o: main.c dbproc.h
	gcc -c main.c
dbproc.o: dbproc.c 		
	gcc -c dbproc.c

clean:
	rm *.o mydb
