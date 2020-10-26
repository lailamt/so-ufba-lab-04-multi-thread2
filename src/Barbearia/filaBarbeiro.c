
#define barbeiroMAX 50

int filaBarbeiro[barbeiroMAX];
int tamAtualFilaBarbeiro = - 1;
int inicioBarbeiro = - 1;

void inserirBarbeiro(int item){

	if(tamAtualFilaBarbeiro == barbeiroMAX - 1)
		printf("Estouro da fila");
	else{
		if(inicioBarbeiro== - 1)
			inicioBarbeiro = 0;
		tamAtualFilaBarbeiro = tamAtualFilaBarbeiro + 1;
		filaBarbeiro[tamAtualFilaBarbeiro] = item;
	}
}
void deletarBarbeiro(){
	if(inicioBarbeiro == - 1 || inicioBarbeiro > tamAtualFilaBarbeiro){
		printf("Estouro negativo da fila");
		return;
	}
	else{
		inicioBarbeiro = inicioBarbeiro + 1;
	}
}