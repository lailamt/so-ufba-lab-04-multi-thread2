CC=gcc
CFLAGS = -lpthread -std=c99 -Wall

define clean
    rm -f src/*.o
endef

monitorDorminhoco: src/monitorDorminhoco.c
	mkdir -p build
	$(CC) src/monitorDorminhoco.c -o build/monitorDorminhoco $(CFLAGS)
	$(clean)

prodConBuf: src/prodConBuf.c
	mkdir -p build
	$(CC) src/prodConBuf.c -o build/prodConBuf $(CFLAGS)
	$(clean)

clean:
	rm -f src/*.o
