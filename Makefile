CC = gcc
CFLAGS = -Wall `pkg-config --cflags gtk+-3.0`
LDFLAGS = `pkg-config --libs gtk+-3.0` -lcurl -lm -lcjson

all : GTK

GTK : GTK.o
	gcc $(CFLAGS) -o GTK GTK.o $(LDFLAGS)

GTK.o : GTK.c
	$(CC) $(CFLAGS) -c GTK.c


