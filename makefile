CC=gcc
CFLAGS = -lpthread -std=c99 -Wall

define clean
    rm -f src/*.o
endef

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

barbearia: src/Barbearia/barbearia.c 
	mkdir -p build
	$(CC) $(CFLAGS) src/Barbearia/barbearia.c -o build/barbearia $(CFLAGS)
	$(clean)

plantacao2: src/Outros/plantacao2.c 
	mkdir -p build
	$(CC) src/Outros/plantacao2.c  -o build/plantacao2 $(CFLAGS)
	$(clean)

prodConBuf: src/Outros/prodConBuf.c
	mkdir -p build
	$(CC) src/Outros/prodConBuf.c -o build/prodConBuf $(CFLAGS)

clean:
	rm -f src/*.o
