CC = gcc
CFLAGS = -Wall `pkg-config --cflags gtk+-3.0`
LDFLAGS = `pkg-config --libs gtk+-3.0` -lcurl -lm -lcjson

all : Requeteur

Requeteur : Requeteur.o
	gcc $(CFLAGS) -o Requeteur Requeteur.o $(LDFLAGS)

Requeteur.o : Requeteur.c
	$(CC) $(CFLAGS) -c Requeteur.c


