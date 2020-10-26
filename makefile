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

procon: src/prodCons.c
	mkdir -p build
	$(CC) $(CFLAGS) src/prodCons.c -o build/procon $(CFLAGS)
	$(clean)

planta: src/plantacao.c 
	mkdir -p build
	$(CC) $(CFLAGS) src/plantacao.c  -o build/planta $(CFLAGS)
	$(clean)

dorminhoco: src/monitorDorminhoco.c 
	mkdir -p build
	$(CC) $(CFLAGS) src/monitorDorminhoco.c -o build/monitorDorminhoco $(CFLAGS)
	$(clean)

barbearia: src/barbearia.c 
	mkdir -p build
	$(CC) $(CFLAGS) src/barbearia.c -o build/barbearia.c $(CFLAGS)
	$(clean)

plantacao2: src/plantacao2.c 
	mkdir -p build
	$(CC) src/plantacao2.c  -o build/plantacao2 $(CFLAGS)
	$(clean)

clean:
	rm -f src/*.o
