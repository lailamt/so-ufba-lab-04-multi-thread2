
#define clienteMAX 50

int filaCliente[clienteMAX];
int tamAtualFilaCliente = - 1;
int inicioCliente = - 1;

void inserirCliente(int item){

	if(tamAtualFilaCliente == clienteMAX - 1)
		printf("Estouro da fila");
	else{
		if(inicioCliente== - 1)
			inicioCliente = 0;
		tamAtualFilaCliente = tamAtualFilaCliente + 1;
		filaCliente[tamAtualFilaCliente] = item;
	}
}
void deletarCliente(){
	if(inicioCliente == - 1 || inicioCliente > tamAtualFilaCliente){
		printf("Estouro negativo da fila");
		return;
	}
	else{
		inicioCliente = inicioCliente + 1;
	}
}