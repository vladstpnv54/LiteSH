CC = gcc
CFLAGS = -Wall -Werror
CLIENT = LiteSH
SERVER = LiteSHserver
SERVICE = LiteSH.service

all: bin/$(CLIENT) bin/$(SERVER) build/libhelp.so

bin/$(CLIENT): build/client.o build/erproc.o build/commands.o
	$(CC) $(CFLAGS) $^ -o $@ -ldl

bin/$(SERVER): build/server.o build/erproc.o build/commands.o
	$(CC) $(CFLAGS) $^ -o $@
	
build/client.o: src/client.c
	$(CC) $(CFLAGS) -c $< -o $@

build/server.o: src/server.c
	$(CC) $(CFLAGS) -c $< -o $@
	
build/erproc.o: src/libs/erproc.c
	$(CC) $(CFLAGS) -c $< -o $@
	
build/commands.o: src/libs/commands.c
	$(CC) $(CFLAGS) -c $< -o $@

build/help.o: src/libs/help.c
	$(CC) $(CFLAGS) -c -fPIC $< -o $@
	
build/libhelp.so: build/help.o
	$(CC) $(CFLAGS) -g -shared -o $@ $<
	
.PHONY: clean install unistall

clean: 
	rm -rf build/*.o
	rm -rf build/*.so
	rm -rf bin/*
	
install: bin/$(CLIENT) bin/$(SERVER)
	mkdir -p $(DESTDIR)/usr/bin
	cp -f bin/$(CLIENT) $(DESTDIR)/usr/bin
	chmod 755 $(DESTDIR)/usr/bin/LiteSH
	cp -f bin/$(SERVER) $(DESTDIR)/usr/bin
	chmod 755 $(DESTDIR)/usr/bin/LiteSHserver
	
	
	mkdir -p $(DESTDIR)/usr/lib
	cp -f build/libhelp.so $(DESTDIR)/usr/lib
	chmod 644 $(DESTDIR)/usr/lib/libhelp.so
	
	mkdir -p $(DESTDIR)/etc/systemd/system
	cp -f $(SERVICE) $(DESTDIR)/etc/systemd/system
	chmod 755 $(DESTDIR)/etc/systemd/system/LiteSH.service
	
unistall:
	rm -f $(DESTDIR)/usr/bin/LiteSH
	rm -f $(DESTDIR)/usr/bin/LiteSHserver
	rm -f $(DESTDIR)/usr/lib/libhelp.so
	rm -f $(DESTDIR)/etc/systemd/system/LiteSH.service
	
