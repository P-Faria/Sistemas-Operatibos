CC=gcc
DEPS= src/globals.h

all: server client

server: bin/sdstored

client: bin/sdstore

bin/sdstored: obj/sdstored.o obj/sdstored_aux.o
	$(CC) obj/sdstored.o obj/sdstored_aux.o -o bin/sdstored

obj/sdstored.o: src/server.c $(DEPS)
	$(CC) -Wall -c src/server.c -o obj/sdstored.o

obj/sdstored_aux.o: src/server_aux.c $(DEPS)
	$(CC) -Wall -c src/server_aux.c -o obj/sdstored_aux.o

bin/sdstore: obj/sdstore.o obj/sdstore_aux.o
	$(CC)  obj/sdstore.o obj/sdstore_aux.o -o bin/sdstore

obj/sdstore.o: src/client.c $(DEPS)
	$(CC) -Wall -c src/client.c -o obj/sdstore.o

obj/sdstore_aux.o: src/client_aux.c $(DEPS)
	$(CC) -Wall -c src/client_aux.c -o obj/sdstore_aux.o

clean:
	rm obj/* tmp/* bin/{sdstore,sdstored}