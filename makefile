CC=gcc
CFLAGS = -std=c99 -Wall -lm -lpthread -pthread

define clean
    rm -f src/*.o
endef

procon: src/prodCons.c
	mkdir -p build
	$(CC) $(CFLAGS) src/prodCons.c -o build/procon
	$(clean)

planta: sarc/plantacao.c 
	mkdir -p build
	$(CC) $(CFLAGS) src/plantacao.c  -o build/planta
	$(clean)

dorminhoco: src/monitorDorminhoco.c 
	mkdir -p build
	$(CC) $(CFLAGS) src/monitorDorminhoco.c -o build/monitorDorminhoco
	$(clean)

barbearia: src/barbearia.c 
	mkdir -p build
	$(CC) $(CFLAGS) src/barbearia.c -o build/barbearia.c
	$(clean)

clean:
	rm -f src/*.o
