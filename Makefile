CFLAGS = -std=c99 -Wall -Werror -Wvla -g 
LDFLAGS = -lm -lmysqlclient -lcurl

.PHONY: all clean

all: main

main: main.o config_db.o send_message.o
	gcc $(CFLAGS) main.o config_db.o send_message.o -o main $(LDFLAGS)

main.o: main.c config_db.h send_message.h
	gcc $(CFLAGS) -c main.c

config_db.o: config_db.c config_db.h
	gcc $(CFLAGS) -c config_db.c

send_message.o: send_message.c send_message.h
	gcc $(CFLAGS) -c send_message.c

clean:
	rm -f main *.o
