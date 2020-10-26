pthread_mutex_t pararFila; 


void corteDeCabelo(long idBarbeiro, int idCliente){
    pthread_mutex_lock(&pararFila);

    //imprimindo aqui o idDoBarbeiro para o printf quando o cliente acordar o barbeiro,
    //ou seja, continuacao da funcao chegandoAoSalao 
    printf("%lu.\n", idBarbeiro+1);
    
    printf("O Barbeiro %lu comeca a cortar o cabelo do Cliente %d.\n", idBarbeiro+1,idCliente+1);
    pthread_mutex_unlock(&pararFila);
}

void chegandoAoSalao(long idCliente){
    pthread_mutex_lock(&pararFila);
    printf("\nCliente %lu acaba de chegar no salao e acorda o Barbeiro ",idCliente+1);
    pthread_mutex_unlock(&pararFila);
}

void recebendoDinheiro(long idBarbeiro, int idCliente){
    pthread_mutex_lock(&pararFila);
    printf("O Barbeiro %lu acaba de receber o dinheiro do Cliente %d.\n", idBarbeiro+1,idCliente+1);
    pthread_mutex_unlock(&pararFila);
}

void barbeiroDormindo(int idBarbeiro){
    pthread_mutex_lock(&pararFila);
    printf("O Barbeiro %d esta dormindo.\n",idBarbeiro+1);
    pthread_mutex_unlock(&pararFila);
}

void clienteIndoEmbora(int idCliente){

    pthread_mutex_lock(&pararFila);
    printf("O Cliente %d deixa o salao.\n",idCliente+1);
    pthread_mutex_unlock(&pararFila);
}

void pagandoOdinheiro(int idCliente){

    pthread_mutex_lock(&pararFila);
    printf("\nO Cliente %d efetua o pagamento do seu corte de cabelo.\n",idCliente+1);
    pthread_mutex_unlock(&pararFila);
}

void deixandoDinheiroNoCaixa(int idBarbeiro){

    pthread_mutex_lock(&pararFila);
    printf("O Barbeiro %d deixa o dinheiro no caixa.\n",idBarbeiro+1);
    pthread_mutex_unlock(&pararFila);
}
