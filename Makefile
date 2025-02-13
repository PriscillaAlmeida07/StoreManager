CFLAGS = -std=c99 -Wall -Werror -Wvla -g 
LDFLAGS = -lm -lmysqlclient

.PHONY: all clean

all: main

main: main.o config_db.o
	gcc $(CFLAGS) main.o config_db.o -o main $(LDFLAGS)

main.o: main.c config_db.h
	gcc $(CFLAGS) -c main.c

config_db.o: config_db.c config_db.h
	gcc $(CFLAGS) -c config_db.c

clean:
	rm -f main *.o
