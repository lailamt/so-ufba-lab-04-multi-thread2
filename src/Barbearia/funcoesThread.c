
#define qtdMaxBarbeiros 3
#define qtdMaxClientes 50
#define capacidadeMaxima 20


sem_t capacidadeDeClientes;           // para a capacidade de clientes
sem_t clientes;                       // para a espera dos clientes
sem_t barbeiros;                      // para a espera dos barbeiros
sem_t cliente[qtdMaxClientes];        // para todos os clientes
sem_t barbeiro[qtdMaxBarbeiros];      // para todos os barbeiros
sem_t pagamento;                      // para o quando o clinente for pagar o dinheiro ao barbeiro
sem_t entregarDinheiro;               // para o barbeiro colocar o dinheiro no caixa
sem_t corteDoCabelo;                  // para o corte em si
sem_t saidaDoCliente;                 // para quando o cliente estiver saindo


pthread_mutex_t filaDoCliente;
pthread_mutex_t filaDoBarbeiro;


//funcao para gerar as threads dos clientes
void *Cliente(void *args) {

    long idCliente=(long) args;
    
    chegandoAoSalao(idCliente);

    //a espera de quando a capacidade de clientes atinja o limite
    sem_wait(&capacidadeDeClientes);

    //inserindo cliente na fila
    pthread_mutex_lock(&filaDoCliente);
    inserirCliente(idCliente);

    sem_post(&clientes);
    pthread_mutex_unlock(&filaDoCliente);
    sem_wait(&cliente[idCliente]);
    
    sem_wait(&corteDoCabelo);
    sem_post(&pagamento);
    pagandoOdinheiro(idCliente);
    sem_post(&capacidadeDeClientes);

    //cliente indo embora apos efetuar o pagamento
    sem_wait(&saidaDoCliente);
    clienteIndoEmbora(idCliente);
}

//funcao para gerar as threads dos barbeiros
void *Barbeiro(void* args){

    long idBarbeiro=(long)args;
    int primeiroCliente;

    while(1){

        //barbeiro comeca a dormir 
        barbeiroDormindo(idBarbeiro);

        // esperando a vinda dos clientes
        sem_wait(&clientes);

        // pegando o cliente da fila e depois deletando
        pthread_mutex_lock(&filaDoCliente);
        primeiroCliente = filaCliente[inicioCliente];
        deletarCliente();

        pthread_mutex_unlock(&filaDoCliente);

        // chama o cliente q esta a mais tempo esperando
        sem_post(&cliente[primeiroCliente]);
        
        // acontecendo de fato o corteDoCabelo
        
        corteDeCabelo(idBarbeiro,primeiroCliente);

        sleep(5);// tempo para finalizar o corte
        sem_post(&corteDoCabelo);

        //esperando pelo cliente efetuar o pagamento
        sem_wait(&pagamento);

        recebendoDinheiro(idBarbeiro,primeiroCliente);

        sem_post(&saidaDoCliente);

        //adicionando um barbeiro a fila
        pthread_mutex_lock(&filaDoBarbeiro);

        inserirBarbeiro(idBarbeiro);
        sem_post(&barbeiros);
        pthread_mutex_unlock(&filaDoBarbeiro);

        sem_wait(&barbeiro[idBarbeiro]);
        sem_post(&entregarDinheiro);
        deixandoDinheiroNoCaixa(idBarbeiro);

    }
}

//funcao para gerar as threads do caixa
void *CaixaRegistradora(void *args){

    int primeiroBarbeiro;

    while(1){

        //a espera dos barbeiros
        sem_wait(&barbeiros);
        //retirando um barbeiro da fila
        pthread_mutex_lock(&filaDoBarbeiro);
        primeiroBarbeiro= filaBarbeiro[inicioBarbeiro];

        deletarBarbeiro();
        pthread_mutex_unlock(&filaDoBarbeiro);

        sem_post(&barbeiro[primeiroBarbeiro]);

        // a espera do barbeiro para deixar o dinheiro no caixa
        sem_wait(&entregarDinheiro);
    }
}