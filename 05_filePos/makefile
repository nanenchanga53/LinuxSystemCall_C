CC=gcc

dbinsert: dbinsert.c
	$(CC) -o $@ $<

dbquery: dbquery.c
	$(CC) -o $@ $<

dbupdate: dbupdate.c
	$(CC) -o $@ $<

clean:
	rm *.o dbinsert dbquery dbupdate

all : dbinsert dbquery dbupdate
