#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <conio.h>
#include <locale.h>
#include <time.h>

//struct dados do endereço cliente
struct Tender{
    char rua[50], bairro[30], cidade[50], estado[50], cep[15];
    int num;
};
typedef struct Tender ender;

//struct dados pessoais do cliente
struct Tcliente{
    int codigoC, ponto_Fidelidade;
    char nome[30], telefone[18];
    ender endereco;

};
typedef struct Tcliente cliente;

//structs dados do veiculo
struct Tveiculo{
    int codigoV;
    char descricao[100];
    char modelo[50];
    char cor[10];
    char placa[8];
    float valor_diaria;
    int qtd_ocupante;
    char status[20];
};
typedef struct Tveiculo veiculo;

//struct datas da locação
struct data_retent{
    int dia;
    int mes;
    int ano;
};
typedef struct data_retent dr;

//struct dados da locação
struct Tlocacao{
    unsigned long long int codigo;
    int qnt_dias;
    dr retirada;
    dr entrega;
    char seguro[4];
    int cod_cliente;
    int cod_veiculo;
    char baixa[4];
};
typedef struct Tlocacao locacao;

//struct dados do prêmio
struct Tpremio{
    long int cod;
    int q_can,q_chav,q_aroma,q_flan,q_apes,q_alom,q_kit;
    char resgatado[4];
};
typedef struct Tpremio premio;


void inclui_cliente(FILE *);
void altera_arquivo_cliente(FILE *);
int localiza_cliente(FILE *, int);
void pesquisa_Informacao_Cliente(FILE *);
void pesquisa_Informacao_Veiculo(FILE *);
void pesquisa_locacoes_cliente(FILE *, FILE*);
void imprime_arquivo_cliente(FILE *);
void inclui_veiculo(FILE *);
void altera_arquivo_veiculo(FILE *);
int localiza_veiculo(FILE *, int);
void altera_arquivo_veiculo(FILE *);
int localiza_locacao(FILE *, unsigned long long int);
void inclui_locacao(FILE *, FILE *, FILE *);
void baixa_locacao(FILE *, FILE *, FILE *);
void imprime_arquivo_locacao(FILE *);
void imprime_arquivo_veiculo(FILE *);
int get_days(dr *, dr *);
int valid_date(int, int, int);
int dias_juros(dr, dr);
int list_ocupantes(FILE *, int);
void status_veiculo(veiculo *);
void kit_locaMais(FILE *);
void loja_de_pontos(FILE *,FILE *);
void imprime_arquivo_premio(FILE *);
int localiza_premio(FILE *,long int);

//função main abre os arquivos(arq do cliente, do veículo e da locação) e possui o menu para o usuário selecionar a opção que deseja
int main(){
    FILE *arqCliente;//arquivo cliente
    FILE *arqVeiculo; //arquivo veiculo
    FILE *arqLocacao; //arquivo locação
    FILE *arqPremio; //arquivo prêmio

    char op;
    setlocale(LC_ALL,"portuguese");
    srand(time(NULL));



    if (((arqVeiculo = fopen("veiculoDB.dat", "r+b"))==NULL) || ((arqCliente = fopen("clienteDB.dat", "r+b"))==NULL) || ((arqLocacao = fopen("locadoraDB.dat", "r+b"))==NULL) || ((arqPremio = fopen("premioDB.dat", "r+b"))==NULL)){ // arquivo existe
        printf("Arquivo não existia ... criando arquivo!");
        if( ((arqVeiculo = fopen("veiculoDB.dat", "w+b"))==NULL) || ((arqCliente = fopen("clienteDB.dat", "w+b"))==NULL) || ((arqLocacao = fopen("locadoraDB.dat", "w+b"))==NULL) || ((arqPremio = fopen("premioDB.dat", "w+b"))==NULL)){ //arq não existe
            printf("Erro na criação do arquivo!!");
            exit(1);
        }
        system("pause");
    }


    do{
        printf("\n----------------------------Menu Principal---------------------------\n");

        printf("Escolha uma opção:\n\n");
        printf("(a) - Cadastrar cliente\n");
        printf("(b) - Alterar dados do cliente\n");
        printf("(c) - Listar clientes\n");
        printf("(d) - Cadastrar veículo\n");
        printf("(e) - Alterar dados veículo\n");
        printf("(f) - Listar veículos\n");
        printf("(g) - Aluguar veiculo\n");
        printf("(h) - Concluir locacao\n");
        printf("(i) - Listar locações\n");
        printf("(j) - Pesquisar locações específicas de um cliente\n");
        printf("(k) - Pesquisar informações de um cliente\n");
        printf("(l) - Pesquisar informações de um veículo\n");
        printf("(m) - Pesquisar ganhadores kit LocaMais\n");
        printf("(n) - Loja de Pontos\n");
        printf("(o) - Resgatar Prêmio\n");
        printf("(p) - Sair do sistema\n");

        op=getch();

        switch (op){
        case 'a':
            printf("\n---------------------------------------------------------------------\n");
            printf("\n------------------------Cadastrando Cliente--------------------------\n");
            inclui_cliente(arqCliente);
            break;
        case 'b':
            printf("\n---------------------------------------------------------------------\n");
            printf("\n---------------------Alterando dados do Cliente----------------------\n");
            altera_arquivo_cliente(arqCliente);
            break;
        case 'c':
            printf("\n---------------------------------------------------------------------\n");
            printf("\n-----------------------Listagem Clientes-----------------------------\n");
            imprime_arquivo_cliente(arqCliente);
            break;
        case 'd':
            printf("\n---------------------------------------------------------------------\n");
            printf("\n-------------------------Cadastrando Veículo-------------------------\n");
            inclui_veiculo(arqVeiculo);
            break;
        case 'e':
            printf("\n---------------------------------------------------------------------\n");
            printf("\n---------------------Alterando dados do Veículo----------------------\n");
            altera_arquivo_veiculo(arqVeiculo);
            break;
        case 'f':
            printf("\n---------------------------------------------------------------------\n");
            printf("\n----------------------Listagem dos Veículos--------------------------\n");
            imprime_arquivo_veiculo(arqVeiculo);
            break;
        case 'g':
            printf("\n---------------------------------------------------------------------\n");
            printf("\n----------------------Preenchendo a Locação--------------------------\n");
            inclui_locacao(arqLocacao, arqVeiculo, arqCliente);
            break;
        case 'h':
            printf("\n---------------------------------------------------------------------\n");
            printf("\n----------------------Concluindo a Locação---------------------------\n");
            baixa_locacao(arqLocacao,arqVeiculo, arqCliente);
            break;
        case 'i':
            printf("\n---------------------------------------------------------------------\n");
            printf("\n--------------------------Listagem das Locações----------------------\n");
            imprime_arquivo_locacao(arqLocacao);
            break;
        case 'j':
            printf("\n---------------------------------------------------------------------\n");
            printf("\n-----------Pesquisando locações específicas de um Cliente------------\n");
            pesquisa_locacoes_cliente(arqLocacao, arqCliente);
            break;
        case 'k':
            printf("\n---------------------------------------------------------------------\n");
            printf("\n-----------------Pesquisa Informações de um Cliente------------------\n");
            pesquisa_Informacao_Cliente(arqCliente);
            system("pause");
            break;
        case 'l':
            printf("\n---------------------------------------------------------------------\n");
            printf("\n-----------------Pesquisa Informações de um Veículo------------------\n");
            pesquisa_Informacao_Veiculo(arqVeiculo);
            system("pause");
            break;
        case 'm':
            printf("\n---------------------------------------------------------------------\n");
            printf("\n-----------------Pesquisa Ponto Fidelidade---------------------------\n");
            kit_locaMais(arqCliente);
            system("pause");
            break;
        case 'n':
            loja_de_pontos(arqCliente,arqPremio);
            system("pause");
            break;
        case 'o':
            printf("\n---------------------------------------------------------------------\n");
            printf("\n------------------------Listando Premio------------------------------\n");
            imprime_arquivo_premio(arqPremio);
            system("pause");
            break;
        case 'p':
            printf("\n---------------------------------------------------------------------\n");
            printf("\n-------------------------Fim programa--------------------------------\n");
            system("pause");
            break;
        default:
            printf("\nOpção inválida\n");
        }
    }
    while (op!='p');
    fclose(arqCliente);
    fclose(arqVeiculo);
    fclose(arqLocacao);
    fclose(arqPremio);
    return 0;
}



/*-----------------------------------------------------FUNÇÕES PARA O CLIENTE-------------------------------------------------------------------*/
//procedimento que cadastra/inclui um cliente no sistema
void inclui_cliente(FILE *arqCliente){
    fflush(stdin);
    cliente c;
    int posicao;

    printf("\n");
    c.codigoC=1;
    do{
        printf("\nDigite o código com até 3 dígitos: ");
        fflush(stdin);
        scanf("%3d",&c.codigoC);
        if(c.codigoC<=1){
            printf("\nERRO!");
        }
    }while( c.codigoC<=1);
    posicao=localiza_cliente(arqCliente,c.codigoC);
    if (posicao==-1){ //não tinha codigo no arquivo
        printf("Nome: ");
        fflush(stdin);
        gets(c.nome);

        printf("Telefone: ");
        fflush(stdin);
        gets(c.telefone);

        printf("\n*Cadastrando o endereco*");
        printf("\nRua: ");
        fflush(stdin);
        gets(c.endereco.rua);
        printf("Bairro: ");
        fflush(stdin);
        gets(c.endereco.bairro);
        printf("Numero: ");
        scanf("%i", &c.endereco.num);
        printf("Cep: ");
        fflush(stdin);
        gets(c.endereco.cep);
        printf("Cidade: ");
        fflush(stdin);
        gets(c.endereco.cidade);
        printf("Estado: ");
        fflush(stdin);
        gets(c.endereco.estado);

        c.ponto_Fidelidade=0;

        fseek(arqCliente,0,SEEK_END); // posicionado o arquivo no final
        fwrite(&c, sizeof(c),1,arqCliente); //gravando os dados
        fflush(arqCliente);
    }
     else{
        printf("\nERRO!");
        printf("\nO código %d já existe no arquivo. Inclusão não realizada!\n",c.codigoC);
    }
}


//procedimento que altera os dados do cliente
void altera_arquivo_cliente(FILE *arqCliente){
    fflush(stdin);
    int codigoC,posicao;
    cliente c;
    printf("\nPara alterar, digite o código do cliente: ");
    scanf("%3d",&codigoC);
    posicao=localiza_cliente(arqCliente,codigoC);

    //localizou o cliente
    if (posicao!=-1){

        fseek(arqCliente,sizeof(c)*(posicao),SEEK_SET);
        fread(&c, sizeof(c),1, arqCliente);
        printf("\n*Dados atuais* \n");
        printf("-Cliente: %i \n-Nome: %s\n-Telefone: %s \n\n-Rua: %s\n-Bairro: %s\n-Nº: %i\n-Cidade: %s\n-Estado: %s\n-Cep: %s ",c.codigoC,c.nome,c.telefone, c.endereco.rua, c.endereco.bairro, c.endereco.num,c.endereco.cidade, c.endereco.estado, c.endereco.cep);

        printf("\n\n*Novos dados*");
        printf("\nNome: ");
        fflush(stdin);
        gets(c.nome);

        printf("Telefone: ");
        fflush(stdin);
        gets(c.telefone);

        printf("\n-Endereco-");
        printf("\nRua: ");
        fflush(stdin);
        gets(c.endereco.rua);
        printf("Bairro: ");
        fflush(stdin);
        gets(c.endereco.bairro);
        printf("Numero: ");
        scanf("%i", &c.endereco.num);
        printf("Cep: ");
        fflush(stdin);
        gets(c.endereco.cep);
        printf("Cidade: ");
        fflush(stdin);
        gets(c.endereco.cidade);
        printf("Estado: ");
        fflush(stdin);
        gets(c.endereco.estado);


        fseek(arqCliente,sizeof(c)*(posicao),SEEK_SET);
        fwrite(&c, sizeof(c),1, arqCliente);
        fflush(arqCliente);
    }
    else{
        printf("\nCódigo do cliente não encontrado");
    }
}


//procedimento que localiza o cliente (comparando o código digitado com os códigos que existem no arquivo cliente)
int localiza_cliente(FILE *arqCliente,int codigoC){
    fflush(stdin);
    int posicao=-1, achou=0;
    cliente c;
    fseek(arqCliente,0,SEEK_SET);
    fread(&c, sizeof(c), 1, arqCliente);

    while(!feof(arqCliente) && !achou){
         posicao++;
        if (c.codigoC==codigoC){
            achou=1;
        }
        fread(&c, sizeof(c),1, arqCliente);
    }

    if(achou){
        return posicao;
    }
     else{
        return -1;
    }
}


//procedimento que pesquisa e mostra informações de um cliente
void pesquisa_Informacao_Cliente(FILE *arqCliente){
    fflush(stdin);
    cliente c;
    int posicao, codDigitado;
    printf("\nDigite o código do cliente que deseja procurar: ");
    fflush(stdin);
    scanf("%3i",&codDigitado);
    posicao=localiza_cliente(arqCliente, codDigitado);

    if (posicao != -1){
        fseek(arqCliente,0,SEEK_SET);
        fread(&c, sizeof(c),1,arqCliente);

        while(!feof (arqCliente) ){
            if(codDigitado == c.codigoC){
                printf("\nNome: %s \n",c.nome);
                printf("\nPontos Fidelidade: %i\n",c.ponto_Fidelidade);
                if(c.ponto_Fidelidade>=500){
                    printf("\tPARABÉNS!!! VOCÊ É ELEGíVEL PARA UM PRÊMIO!!!");
                }
                printf("\nTelefone: %s\n",c.telefone);
                printf("\n*Endereço* \n");
                printf("Rua:%s \nbairro: %s \nNº %i \nCep: %s \nCidade: %s\nEstado: %s",c.endereco.rua,c.endereco.bairro,c.endereco.num,c.endereco.cep, c.endereco.cidade, c.endereco.estado);
                printf("\n\n");
            }
            fread(&c, sizeof(c),1, arqCliente);
        }
    }
    else{
        printf("\nCódigo do cliente não encontrado\n");
    }
}


//procedimento que pesquisa e mostra informações de um cliente
void pesquisa_locacoes_cliente(FILE *arqLocacao, FILE *arqCliente){
    fflush(stdin);
    locacao l;
    int posicao, codDigitado;
    printf("\nDigite o código do cliente para procurar suas locações: ");
    fflush(stdin);
    scanf("%3i",&codDigitado);
    posicao=localiza_cliente(arqCliente, codDigitado);

    if (posicao != -1){
        fseek(arqLocacao,0,SEEK_SET);
        fread(&l, sizeof(l),1,arqLocacao);

        while(!feof (arqLocacao) ){
            if(codDigitado == l.cod_cliente){
                printf("\nLocação código:%llu \n",l.codigo);
                printf("Dias de locacao:%d \n",l.qnt_dias);
                printf("Data Retirada:%d/%d/%d\n",l.retirada.dia,l.retirada.mes,l.retirada.ano);
                printf("Data Entrega:%d/%d/%d\n",l.entrega.dia,l.entrega.mes,l.entrega.ano);
                printf("Seguro? %s\n",l.seguro);
                printf("Cod Veiculo:%d\n",l.cod_veiculo);
                printf("Concluida?:%s\n",l.baixa);
                printf("\n\n");
            }
            fread(&l, sizeof(l),1, arqLocacao);
        }
    }
    else{
        printf("\nCódigo do cliente não encontrado\n");
    }
}


//procedimento que imprime informações de todos os clientes
void imprime_arquivo_cliente(FILE *arqCliente){
    fflush(stdin);
    cliente c;
    fseek(arqCliente,0,SEEK_SET);
    fread(&c, sizeof(c),1, arqCliente);

    while (!feof(arqCliente)){
        printf("Código do Cliente: %d \n",c.codigoC);
        printf("Nome: %s \n",c.nome);
        printf("\nPontos Fidelidade: %i\n",c.ponto_Fidelidade);
        printf("\nTelefone: %s\n",c.telefone);
        printf("\n*Endereço* \n");
        printf("Rua:%s \nbairro: %s \nNº %i \nCep: %s \nCidade: %s\nEstado: %s",c.endereco.rua,c.endereco.bairro,c.endereco.num,c.endereco.cep, c.endereco.cidade, c.endereco.estado);
        printf("\n*********************************************************************\n");

        fread(&c, sizeof(c),1, arqCliente);
    }
}




/*--------------------------------------------------FUNÇÕES APRA O VEÍCULO-----------------------------------------------------------------------*/
//procedimento que cadastra/inclui um veículo no sistema
void inclui_veiculo(FILE *arqVeiculo){
    fflush(stdin);
    veiculo v;
    int posicao;
    printf("\n\n");
    v.codigoV=1;
    do{
        printf("Digite o código do veiculo com até três digitos: ");
        fflush(stdin);
        scanf("%3d",&v.codigoV);
        if(v.codigoV<=1){
            printf("\nERRO!");
        }
    }while(v.codigoV<=1);

        posicao=localiza_veiculo(arqVeiculo,v.codigoV);

    if (posicao==-1){ //não tinha codigo no arquivo
        printf("Modelo do veículo: ");
        fflush(stdin);
        gets(v.modelo);
        printf("Descrição do veiculo: ");
        fflush(stdin);
        gets(v.descricao);
        printf("Cor do veículo: ");
        fflush(stdin);
        gets(v.cor);
        printf("Placa: ");
        fflush(stdin);
        gets(v.placa);
        v.qtd_ocupante=-1;
        do{
            printf("Quantidade de ocupantes: ");
            fflush(stdin);
            scanf("%i",&v.qtd_ocupante);
        }while((v.qtd_ocupante<=0)||(v.qtd_ocupante>=15));
        //chama o procedimento do status do carro para o usuário selecionar a opção
        status_veiculo(&v);

        printf("Preço da diária: ");
        fflush(stdin);
        scanf("%f",&v.valor_diaria);

        fseek(arqVeiculo,0,SEEK_END); // posicionado o arquivo no final
        fwrite(&v, sizeof(v),1,arqVeiculo); //gravando os dados
        fflush(arqVeiculo);
    }
     else{
        printf("Código %d já existe no arquivo. Inclusão não realizada!\n", v.codigoV);
    }
}


//procedimento que altera os dados do veículo
void altera_arquivo_veiculo(FILE *arqVeiculo){
    fflush(stdin);
    int codigoV,posicao;
    veiculo v;
    printf("\nPara alterar, digite o código do veículo: ");
    scanf("%d",&codigoV);
    posicao=localiza_veiculo(arqVeiculo,codigoV);

    //localizou a veiculo
    if (posicao!=-1){
        fseek(arqVeiculo,sizeof(v)*(posicao),SEEK_SET);
        fread(&v, sizeof(v),1, arqVeiculo);
        printf("\n*Dados atuais* \n");
        printf("-Veículo: %i \n-Modelo: %s \n-Descrição: %s\n-Cor: %s \n-Placa: %s\n-Qtde ocupantes: %i\n-Status: %s\n-Valor diária: %.2f",v.codigoV,v.modelo,v.descricao,v.cor,v.placa,v.qtd_ocupante,v.status,v.valor_diaria);

        printf("\n\n*Nova descrição*");

        printf("Modelo do veículo: ");
        fflush(stdin);
        gets(v.modelo);
        printf("Descrição do veiculo: ");
        fflush(stdin);
        gets(v.descricao);
        printf("Cor do veículo: ");
        fflush(stdin);
        gets(v.cor);
        printf("Placa: ");
        fflush(stdin);
        gets(v.placa);

        do{
            printf("Quantidade de ocupantes: ");
            fflush(stdin);
            scanf("%i",&v.qtd_ocupante);
        }while((v.qtd_ocupante<=0)||(v.qtd_ocupante>=15));

        //chama o procedimento do status do carro para o usuário selecionar a opção
        status_veiculo(&v);

        printf("Preço da diária: ");
        fflush(stdin);
        scanf("%f",&v.valor_diaria);

        fseek(arqVeiculo,sizeof(v)*(posicao),SEEK_SET);
        fwrite(&v, sizeof(v),1, arqVeiculo);
        fflush(arqVeiculo);
    }
    else{
        printf("\nCódigo do veículo não encontrado");
    }
}


//procedimento que localiza o veículo (comparando o código digitado com os códigos que existem no arquivo do veículo)
int localiza_veiculo(FILE *arqVeiculo,int codigoV){
    fflush(stdin);
    int posicao=-1,achou=0;
    veiculo v;
    fseek(arqVeiculo,0,SEEK_SET);
    fread(&v, sizeof(v), 1, arqVeiculo);

    while(!feof(arqVeiculo) && !achou){
         posicao++;
        if (v.codigoV==codigoV){
            achou=1;
        }
        fread(&v, sizeof(v),1, arqVeiculo);
    }

    if(achou){
        return posicao;
    }
     else{
        return -1;
    }
}


//procedimento que pesquisa e mostra informações de um veículo
void pesquisa_Informacao_Veiculo(FILE *arqVeiculo){
    fflush(stdin);
    veiculo v;
    int posicao, codDigitado;
    printf("\nDigite o código do veiculo que deseja procurar: ");
    fflush(stdin);
    scanf("%3i",&codDigitado);
    posicao=localiza_veiculo(arqVeiculo, codDigitado);

    if (posicao != -1){
        fseek(arqVeiculo,0,SEEK_SET);
        fread(&v, sizeof(v),1,arqVeiculo);

        while(!feof (arqVeiculo) ){
            if(codDigitado == v.codigoV){
                printf("Modelo: %s\n",v.modelo);
                printf("Descrição: %s \n",v.descricao);
                printf("Cor: %s\n",v.cor);
                printf("Placa: %s\n",v.placa);
                printf("Qtd de ocupantes: %i\n",v.qtd_ocupante);
                printf("Status: %s\n",v.status);
                printf("Valor diária: %.2f\n",v.valor_diaria);
                printf("\n\n");
            }
            fread(&v, sizeof(v),1, arqVeiculo);
        }
    }
    else{
        printf("\nCódigo do veículo não encontrado\n");
    }
}

//procedimento que imprime todos os veículos
void imprime_arquivo_veiculo(FILE *arqVeiculo){
    fflush(stdin);
    veiculo v;
    fseek(arqVeiculo,0,SEEK_SET);
    fread(&v, sizeof(v),1, arqVeiculo);

    while (!feof(arqVeiculo)){
        printf("\nCód veículo: %i \n",v.codigoV);
        printf("Modelo: %s\n",v.modelo);
        printf("Descrição: %s \n",v.descricao);
        printf("Cor: %s\n",v.cor);
        printf("Placa: %s\n",v.placa);
        printf("Qtd de ocupantes: %i\n",v.qtd_ocupante);
        printf("Status: %s\n",v.status);
        printf("Valor diária: %.2f\n",v.valor_diaria);
        printf("\n*********************************************************************\n");
        fread(&v, sizeof(v),1, arqVeiculo);
    }
}

//procedimento que o usuário seleciona a opção do status do veículo
void status_veiculo(veiculo *v){
    fflush(stdin);

    int opcao;

    do{
        printf("\nDigite o status do veículo: \n");
        printf("(1) - Alugado\n");
        printf("(2) - Disponível\n");
        printf("(3) - Em manutenção\n");

        fflush(stdin);
        scanf("%i", &opcao);

        switch (opcao){
            case 1:
                v->status[0] = 'a';
                v->status[1]= 'l';
                v->status[2]= 'u';
                v->status[3]= 'g';
                v->status[4]= 'a';
                v->status[5]= 'd';
                v->status[6]= 'o';
                v->status[7]='\0';

            break;
            case 2:
                v->status[0] = 'd';
                v->status[1]= 'i';
                v->status[2]= 's';
                v->status[3]= 'p';
                v->status[4]= 'o';
                v->status[5]= 'n';
                v->status[6]= 'i';
                v->status[7]= 'v';
                v->status[8]= 'e';
                v->status[9]= 'l';
                v->status[10]='\0';
            break;
            case 3:
                v->status[0] = 'e';
                v->status[1]= 'm';
                v->status[2]= ' ';
                v->status[3]= 'm';
                v->status[4]= 'a';
                v->status[5]= 't';
                v->status[6]= 'e';
                v->status[7]= 'n';
                v->status[8]= 'ç';
                v->status[9]= 'ã';
                v->status[9]= 'o';
                v->status[10]='\0';
            break;
            default:
                printf("\nOpcao invalida. Digite novamente o status: ");
        }
    }
    while((opcao!= 1) && (opcao !=2) && (opcao !=3));
}




/*----------------------------------------Funções para a Locação----------------------------------------------------------------*/
//procedimento que cadastra/inclui uma locação no sistema
void inclui_locacao(FILE *arqLocacao, FILE *arqVeiculo, FILE *arqCliente){
    fflush(stdin);
    locacao l;
    veiculo v;
    char status[20];
    int posicao,carro_lote=(rand()%9000)+1000,ocupantes,disp=0,cod_cliente;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    tm.tm_hour=tm.tm_hour-3; //Simulando nosso fuso-horario de acordo com horario do time_t (aprox 3 horas a mais que nosso horário)
    if(tm.tm_hour<8||tm.tm_hour>18){ //restringe o horário para fazer uma locação
        printf("\nPor favor, volte no horário comercial.");
    }
    else{ //se estiver no horário comercial, inicia o cadastro da locação

        printf("\nDigite o código do cliente: ");
        fflush(stdin);
        scanf("%3d",&cod_cliente);
        posicao=localiza_cliente(arqCliente,cod_cliente);

        if(posicao!=-1){
            printf("\nDigite a quantia de ocupantes desejada: ");
            fflush(stdin);
            scanf("%d",&ocupantes);
            //chama o procedimento que lista os carros disponiveis de acordo com a qtd de ocupantes inserida pelo usuário
            disp=list_ocupantes(arqVeiculo,ocupantes);

            if(disp>0){ //caso haja carro disponível, é listado todos e o usuário seleciona o carro que ele deseja
                printf("\nDigite o código de um veiculo disponível desejado: ");
                fflush(stdin);
                scanf("%3d",&l.cod_veiculo);

                posicao=localiza_veiculo(arqVeiculo,l.cod_veiculo);
                fseek(arqVeiculo,sizeof(v)*(posicao),SEEK_SET);
                fread(&v, sizeof(v),1, arqVeiculo);
                strcpy(status,v.status);

                //aqui começa o cadastro da locação para o carro selecionado
                if ((posicao!=-1)&&(strcmp(status,"disponivel")==0)){
                    l.cod_cliente=cod_cliente;
                    l.codigo=(l.cod_cliente*(unsigned long long int)10000000)+(l.cod_veiculo*10000)+(carro_lote);
                    printf("Codigo locacao: %llu\n",l.codigo);
                    posicao=localiza_locacao(arqLocacao,l.codigo);
                    if (posicao==-1){  //não tinha codigo no arquivo

                        printf("Digite as datas da locacao: ");
                        fflush(stdin);
                        l.qnt_dias=get_days(&l.retirada,&l.entrega); //chama a função de registrar as datas da locação
                        l.qnt_dias=l.qnt_dias+1;

                        //confere se o cliente quer um seguro ou não
                        do{
                            printf("Digite o seguro da locacao (sim ou nao): ");
                            fflush(stdin);
                            gets(l.seguro);
                        }
                        while(((strcmp(l.seguro,"nao")!=0)&&((strcmp(l.seguro,"sim")!=0))));

                        printf("Dias de locação: %d",l.qnt_dias);

                        l.baixa[0]='n';
                        l.baixa[1]='a';
                        l.baixa[2]='o';
                        l.baixa[3]='\0';
                        fseek(arqLocacao,0,SEEK_END); // posicionado o arquivo no final
                        fwrite(&l, sizeof(l),1,arqLocacao); //gravando os dados
                        fflush(arqLocacao);

                        v.status[0]='a';
                        v.status[1]='l';
                        v.status[2]='u';
                        v.status[3]='g';
                        v.status[4]='a';
                        v.status[5]='d';
                        v.status[6]='o';
                        v.status[7]='\0';
                        posicao=localiza_veiculo(arqVeiculo,l.cod_veiculo);
                        fseek(arqVeiculo,sizeof(v)*(posicao),SEEK_SET);
                        fwrite(&v, sizeof(v),1, arqVeiculo);
                        fflush(arqVeiculo);

                    }
                    else{
                        printf("\nEsse código já existe");
                    }
                }
                else if(posicao==-1){
                    printf("\nCódigo de veiculo inválido");
                }
                else{
                    printf("\nVeiculo %s!\n",status);
                }
            }
            else{
                printf("\nPerdão, não há veículos disponíveis no momento :(\n");
            }

        }
        else{
            printf("\nCódigo de cliente inválido\n");
        }

    }

}


/*procedimento que finaliza/baixa a locação no sistema quando o usuario entrega o veículo.
  Ela confere o total de dias alugados e realiza a cobrança o pagamento.
  Se o total de dias for diferente do que foi acordado, há a cobrança de juros*/
void baixa_locacao(FILE *arqLocacao, FILE *arqVeiculo, FILE *arqCliente){
    fflush(stdin);
    unsigned long long int codigo,salva_codigo;
    int posicao1,posicao2,posicao3,dias_de_juros,qnt_dias,dia,mes,ano;
    float valor_final=0.0;
    locacao l;
    veiculo v;
    cliente c;
    printf("Digite o código da locação: ");
    scanf("%10llu",&codigo);
    fflush(stdin);

    posicao1=localiza_locacao(arqLocacao,codigo); //posicao1 chama a função para localizar as locações

    if (posicao1!=-1){ // localiza o código da locação para finalizá-la
        salva_codigo=codigo;
        codigo=((codigo%10000000)/10000);
        posicao2=localiza_veiculo(arqVeiculo,codigo); //posição2 chama a função para localizar os veículos

        if(posicao2!=-1){
            fseek(arqLocacao,sizeof(l)*(posicao1),SEEK_SET);
            fread(&l, sizeof(l),1, arqLocacao);

            if(strcmp(l.baixa,"nao")==0){ //confere se a locação selecionada já obteve baixa ou não
                dia=l.retirada.dia;
                mes=l.retirada.mes;
                ano=l.retirada.ano;
                fseek(arqVeiculo,sizeof(v)*(posicao2),SEEK_SET);
                fread(&v, sizeof(v),1, arqVeiculo);
                l.retirada.dia=l.entrega.dia;
                l.retirada.mes=l.entrega.mes;
                l.retirada.ano=l.entrega.ano;
                fscanf(arqVeiculo,"%f",&v.valor_diaria);
                qnt_dias=l.qnt_dias;

                 //calcula e da baixa na locação
                do{
                    valor_final=0.0;
                    printf("Data de Entrega: ");
                    fflush(stdin);
                    scanf("%d/%d/%d",&l.entrega.dia,&l.entrega.mes,&l.entrega.ano);
                    dias_de_juros=dias_juros(l.retirada,l.entrega);

                    //calcula o valor da locação sem juros
                    if (dias_de_juros<=0){
                        l.qnt_dias=l.qnt_dias+dias_de_juros;
                    }
                    valor_final=((v.valor_diaria)*(l.qnt_dias))/1.0;

                    //se o usuário solicitou seguro do carro, acrescenta o valor do seguro no total a ser pago
                    if(strcmp(l.seguro,"sim")==0){
                        valor_final=valor_final+50.0;
                    }

                    //se há juros, acrescenta o valor do juros no total a ser pago
                    if(dias_de_juros>=1){
                        valor_final=valor_final+(valor_final*0.05)+(30*dias_de_juros);
                    }

                    //confere se o valor da locação está correto a partir da data inserida
                    if(valor_final<=0){
                        printf("\nData inválida. Insira uma data válida\n");
                    }

                }while(valor_final<=0);

                printf("\nPreço total da sua locação: %.2f",valor_final);

                printf("\nTotal de dias de locação: %d",l.qnt_dias);

                //printando o total de dias atrasados
                if(dias_de_juros>0){
                    printf("\nDias de atraso: %d",dias_de_juros);
                }

                codigo=salva_codigo;
                codigo=codigo/10000000;
                posicao3=localiza_cliente(arqCliente,codigo); //posição3 chama a função para localizar o cliente
                fseek(arqCliente,sizeof(c)*posicao3,SEEK_SET);
                fread(&c, sizeof(c),1, arqCliente);
                fseek(arqCliente,sizeof(c)*posicao3,SEEK_SET);

                //calcula os pontos fidelidade do cliente
                int pt=c.ponto_Fidelidade;
                c.ponto_Fidelidade=(pt+(qnt_dias*10));
                printf("\nSeus pontos de fidelidade são: %d",c.ponto_Fidelidade);
                fwrite(&c,sizeof(c),1,arqCliente);
                fflush(arqCliente);

                v.status[0]='d';v.status[1]='i';v.status[2]='s';v.status[3]='p';v.status[4]='o';v.status[5]='n';v.status[6]='i';v.status[7]='v';v.status[8]='e';v.status[9]='l';v.status[10]='\0';
                fseek(arqVeiculo,sizeof(v)*(posicao2),SEEK_SET);
                fwrite(&v, sizeof(v),1, arqVeiculo);
                fflush(arqVeiculo);

                l.baixa[0]='s';l.baixa[1]='i';l.baixa[2]='m';l.baixa[3]='\0';
                l.retirada.dia=dia;
                l.retirada.mes=mes;
                l.retirada.ano=ano;
                fseek(arqLocacao,sizeof(l)*(posicao1),SEEK_SET);
                fwrite(&l, sizeof(l),1, arqLocacao);
                fflush(arqLocacao);
            }
            else{
                printf("Essa locação já teve baixa");
            }
        }
        else{
            printf("Erro ao localizar veiculo da locação");
        }
    }
    else{
        printf("Não há locação com esse código");
    }
}


//procedimento que localiza a locação (comparando o código digitado com os códigos que existem no arquivo da locação)
int localiza_locacao(FILE *arqLocacao,unsigned long long int codigo){
    fflush(stdin);
    int posicao=-1,achou=0;
    locacao l;
    fseek(arqLocacao,0,SEEK_SET);
    fread(&l, sizeof(l),1, arqLocacao);
    while(!feof(arqLocacao) && !achou){
        posicao++;  // semelhante a  posicao = posicao +1;
        if (l.codigo==codigo){
            achou=1;
        }
        fread(&l, sizeof(l),1, arqLocacao);
    }
    if (achou){
        return posicao;
    }
    else{
        return -1;
    }
}


//procedimento que imprime o arquivo de todas as locações
void imprime_arquivo_locacao(FILE *arqLocacao){
    fflush(stdin);
    locacao l;
    fseek(arqLocacao,0,SEEK_SET);
    fread(&l, sizeof(l),1, arqLocacao);
    while (!feof(arqLocacao)){
        printf("Código: %llu \n",l.codigo);
        printf("Dias de locacao: %d \n",l.qnt_dias);
        printf("Data Retirada: %d/%d/%d\n",l.retirada.dia,l.retirada.mes,l.retirada.ano);
        printf("Data Entrega: %d/%d/%d\n",l.entrega.dia,l.entrega.mes,l.entrega.ano);
        printf("Seguro? %s\n",l.seguro);
        printf("Cod Cliente: %d\n",l.cod_cliente);
        printf("Cod Veiculo: %d\n",l.cod_veiculo);
        printf("Concluida?: %s\n",l.baixa);
        printf("\n*********************************************************************\n");
        fread(&l, sizeof(l),1, arqLocacao);
    }
}


//Função que compara o total de ocupantes no veículo, e lista quais veículos estão disponíveis a partir da quantidade digitada*/
int list_ocupantes(FILE *arqVeiculo, int ocupantes){
    fflush(stdin);
    int disp=0;
    veiculo v;
    fseek(arqVeiculo,0,SEEK_SET);
    fread(&v, sizeof(v),1, arqVeiculo);
    while (!feof(arqVeiculo)){
        if(ocupantes==v.qtd_ocupante){
            if(strcmp(v.status,"disponivel")==0){
                printf("\n\n----------------------------------------");
                printf("\nVeículo: %d \n",v.codigoV);
                printf("Descrição: %s \n",v.descricao);
                printf("Modelo: %s\n",v.modelo);
                printf("Cor: %s\n",v.cor);
                printf("Placa: %s\n",v.placa);
                printf("Valor diária: %.2f\n",v.valor_diaria);
                printf("Quantidade de ocupantes: %d\n",v.qtd_ocupante);
                printf("Status: %s\n",v.status);
                printf("----------------------------------------");
                disp++;
            }
        }
        fread(&v, sizeof(v),1, arqVeiculo);
    }
    return disp;
}




/*----------------------------------------Funções para as Datas----------------------------------------------------------------*/
//função que define e confere os dias de retirada e entrega, de acordo com regras válidas ou não
int get_days(dr *retirada, dr *entrega){
    fflush(stdin);
    int daytotal,save_month,save_day,save_year;

    int day_diff, mon_diff, year_diff,var=0; //variáveis de diferença de dias, diferença de meses e diferença de anos

    printf("\nDigite a data de retirada - inserindo as barras - (DD/MM/YYYY): ");
    scanf("%d/%d/%d", &retirada->dia, &retirada->mes, &retirada->ano);

    printf("\nDigite a data de entrega - inserindo as barras - (DD/MM/YYYY): ");
    scanf("%d/%d/%d", &entrega->dia, &entrega->mes, &entrega->ano);

    save_day=entrega->dia;
    save_month=entrega->mes;
    save_year=entrega->ano;

    while((!valid_date(retirada->dia, retirada->mes, retirada->ano))||(!valid_date(entrega->dia, entrega->mes, entrega->ano))){
        if(!valid_date(retirada->dia, retirada->mes, retirada->ano)){ //isso valida se a data de retirada é válida (de acordo com as restrições na função de validar)
            printf("\nPrimeira data é inválida.\n");
    }
        if(!valid_date(entrega->dia, entrega->mes, entrega->ano)){//isso valida se a data de entregaa é válida (de acordo com as restrições na função de validar)
            printf("\nSegunda data é inválida");
    }
        printf("\nDigite a data de retirada - inserindo as barras - (DD/MM/YYYY): ");
        scanf("%d/%d/%d", &retirada->dia, &retirada->mes, &retirada->ano);

        printf("\nDigite a data de entrega (DD/MM/YYYY): ");
        scanf("%d/%d/%d", &entrega->dia, &entrega->mes, &entrega->ano);

        save_day=entrega->dia;
        save_month=entrega->mes;
        save_year=entrega->ano;

    }

    if(entrega->dia < retirada->dia){
        //empresta dias de fevereiro
        if (entrega->mes == 3){
            //verifica se o ano é bissexto
            if ((entrega->ano % 4 == 0 && entrega->ano % 100 != 0) || (entrega->ano % 400 == 0)){
                entrega->dia += 29;
            }
            else{
                entrega->dia += 28;
            }
        }

        //empresta dias de abril ou junho ou setembro ou novembro (meses q possuemm 30 dias)
        else if (entrega->mes == 5 || entrega->mes == 7 || entrega->mes == 10 || entrega->mes == 12){
           entrega->dia += 30;
        }

        //emprestar dias de janeiro ou março ou maio ou julho ou agosto ou outubro ou dezembro (meses com 31 dias)
        else{
           entrega->dia += 31;
        }

        entrega->mes = entrega->mes - 1;
    }

    if (entrega->mes < retirada->mes){
        entrega->mes += 12;
        entrega->ano -= 1;
    }

    //calcula as diferenças entre dias, meses e anos
    day_diff = entrega->dia - retirada->dia;
    mon_diff = entrega->mes - retirada->mes;
    year_diff = entrega->ano - retirada->ano;
    entrega->mes=save_month;
    entrega->dia=save_day;
    entrega->ano=save_year;

    //cálculo do total de dias do carro alugado
    daytotal=day_diff+(30*mon_diff)+(365*year_diff)+var;

    return daytotal;
}


//Função para checar se a data é valida
int valid_date(int day, int mon, int year){
    fflush(stdin);
    int is_valid = 1, is_leap = 0;

    if (year >= 2000 && year <= 2100){

        //verifica se o ano é bissexto
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)){
            is_leap = 1;
        }

        // Verifica se o mês está entre 1 e 12
        if(mon >= 1 && mon <= 12){
            //verifica os dias de fevereiro (28 dias ou 29 quando o ano é bissexto)
            if (mon == 2){
                if (is_leap && day == 29){
                    is_valid = 1;
                }
                else if(day > 28){
                    is_valid = 0;
                }
            }

            //verifica os dias de abril, junho, setembro e novembro (meses com 30 dias)
            else if (mon == 4 || mon == 6 || mon == 9 || mon == 11){
                if (day > 30){
                    is_valid = 0;
                }
            }

            // verifica os dias dos outros meses do ano que possuem 31 dias
            else if(day > 31){
                is_valid = 0;
            }
        }
        else{
            is_valid = 0;
        }

    }
    else{
        is_valid = 0;
    }

    return is_valid;
}


//Função que calcula os dias de juros da locação
int dias_juros(dr retir, dr entr){
    fflush(stdin);
    int daytotal,save_month,save_day,save_year;

    int day_diff, mon_diff, year_diff,var=0;

    save_day=entr.dia;
    save_month=entr.mes;
    save_year=entr.ano;

    while((!valid_date(retir.dia, retir.mes, retir.ano))||(!valid_date(save_day, save_month, save_year))){
        if(!valid_date(retir.dia, retir.mes, retir.ano)){
            printf("\nPrimeira Data é inválida.\n");
    }
        if(!valid_date(save_day, save_month, save_year)){
            printf("\nSegunda Data é inválida\n");
    }

        printf("\nDigite a data de entrega - inserindo as barras - (DD/MM/YYYY): ");
        scanf("%d/%d/%d", &entr.dia, &entr.mes, &entr.ano);

        save_day=entr.dia;
        save_month=entr.mes;
        save_year=entr.ano;

    }

    if(entr.dia < retir.dia){
        //empresta dias de fevereiro
        if (entr.mes == 3){
            //verifica se o ano é bissexto
            if ((entr.ano % 4 == 0 && entr.ano % 100 != 0) || (entr.ano % 400 == 0)){
                entr.dia += 29;
            }
            else{
                entr.dia += 28;
            }
        }

        //empresta dias de abril ou junho ou setembro ou novembro (meses q possuemm 30 dias)
        else if (entr.mes == 5 || entr.mes == 7 || entr.mes == 10 || entr.mes == 12){
           entr.dia += 30;
        }

        //emprestar dias de janeiro ou março ou maio ou julho ou agosto ou outubro ou dezembro (meses com 31 dias)
        else{
           entr.dia += 31;
        }

        entr.mes = entr.mes - 1;
    }

    if (entr.mes < retir.mes){
        entr.mes += 12;
        entr.ano -= 1;
    }

    day_diff = entr.dia - retir.dia;
    mon_diff = entr.mes - retir.mes;
    year_diff = entr.ano - retir.ano;
    entr.mes=save_month;
    entr.dia=save_day;
    entr.ano=save_year;
    daytotal=day_diff+(30*mon_diff)+(365*year_diff)+var;

    return daytotal;
}




/*----------------------------------------Funções para a  Loja----------------------------------------------------------------*/

/*Procedimento que abre a loja de pontos e lista seus itens.
  A partir das escolhas do cliente, o sistema irá gerar um código para o cliente poder resgatar seus prêmios posteriormente*/
void loja_de_pontos(FILE *arqCliente, FILE *arqPremio){
    fflush(stdin);
    cliente c;
    premio p;
    int cod_cliente,posicao,op;
    long int cod=0;
    //variáveis para os itens (almofada lombar, almofada pescoço, aroma, caneta, chaveiro, flanela e o kit locaMaias)
    p.q_alom=0;p.q_apes=0;p.q_aroma=0;p.q_can=0;p.q_chav=0;p.q_flan=0;p.q_kit=0;
    fflush(arqCliente);

    do{
        printf("Digite o código do cliente para entrar na loja de pontos: \n");
        fflush(stdin);
        scanf("%3d",&cod_cliente);
        if(cod_cliente<=1){
            printf("\nERRO! Código inválido");
        }
    }while(cod_cliente<=1);

    posicao=localiza_cliente(arqCliente,cod_cliente);

    if(posicao!=-1){
        fseek(arqCliente,sizeof(c)*(posicao),SEEK_SET);
        fread(&c, sizeof(c),1, arqCliente);
        fseek(arqCliente,sizeof(c)*(posicao),SEEK_SET);

        //menu da loja de pontos
        do{
            printf("\n---------------------------------------------------------------------\n");
            printf("\n---------------------Bem vindo a Loja de pontos!!--------------------\n");
            printf("\nSeu saldo de Pontos de Fidelidade: %d\n",c.ponto_Fidelidade);
            printf("\n----------------------------Itens------------------------------------\n");
            printf("(1) - %s LocaMais: %d pts\n","Caneta",15);
            printf("(2) - %s LocaMais: %d pts\n","Chaveiro",30);
            printf("(3) - %s LocaMais: %d pts\n","Aromatizador para carros",50);
            printf("(4) - %s LocaMais: %d pts\n","Flanela",100);
            printf("(5) - %s LocaMais: %d pts\n","Almofada de Pescoço",200);
            printf("(6) - %s LocaMais: %d pts\n","Almofada Lombar",250);
            printf("(7) - %s LocaMais: %d pts\n","SUPER KIT",500);
            printf("O SUPER KIT contem todos os itens da loja de pontos por um desconto!\n\n");

            printf("Digite o que deseja comprar na loja, ou digite '8' para pegar seu código e sair da loja: ");
            scanf("%d",&op);

            //switch para as opções de compra e caso o cliente não possua pontos suficientes, a compra não é realizada
            switch(op){
                case 1:
                    if(c.ponto_Fidelidade>=15){
                        printf("\nComprando %s ...\n...\nCompra realizada com sucesso!\n ","Caneta");
                        c.ponto_Fidelidade=c.ponto_Fidelidade-15;
                        cod++;
                        p.q_can++;
                    }
                    else{
                        printf("\nComprando %s ...\n...\nOPS! Parece que você não tem pontos suficientes para comprar o produto ''%s'' :(\n","Caneta","Caneta");
                    }
                    system("pause");
                break;
                case 2:
                    if(c.ponto_Fidelidade>=30){
                        printf("\nComprando %s ...\n...\nCompra realizada com sucesso!\n ","Chaveiro");
                        c.ponto_Fidelidade=c.ponto_Fidelidade-30;
                        cod++;
                        p.q_chav++;
                    }
                    else{
                        printf("\nComprando %s ...\n...\nOPS! Parece que você não tem pontos suficientes para comprar o produto ''%s'' :(\n","Chaveiro","Chaveiro");
                    }
                    system("pause");
                break;
                case 3:
                    if(c.ponto_Fidelidade>=50){
                        printf("\nComprando %s ...\n...\nCompra realizada com sucesso!\n ","Aromatizador de carro");
                        c.ponto_Fidelidade=c.ponto_Fidelidade-50;
                        cod++;
                        p.q_aroma++;
                    }
                    else{
                        printf("\nComprando %s ...\n...\nOPS! Parece que você não tem pontos suficientes para comprar o produto ''%s'' :(\n","Aromatizador de carro","Aromatizador de carro");
                    }
                    system("pause");
                break;
                case 4:
                    if(c.ponto_Fidelidade>=100){
                        printf("\nComprando %s ...\n...\nCompra realizada com sucesso!\n ","Flanela");
                        c.ponto_Fidelidade=c.ponto_Fidelidade-100;
                        cod++;
                        p.q_flan++;
                    }
                    else{
                        printf("\nComprando %s ...\n...\nOPS! Parece que você não tem pontos suficientes para comprar o produto ''%s'' :(\n","Flanela","Flanela");
                    }
                    system("pause");
                break;
                case 5:
                    if(c.ponto_Fidelidade>=200){
                        printf("\nComprando %s ...\n...\nCompra realizada com sucesso!\n ","Almofada de Pescoço");
                        c.ponto_Fidelidade=c.ponto_Fidelidade-200;
                        cod++;
                        p.q_apes++;
                    }
                    else{
                        printf("\nComprando %s ...\n...\nOPS! Parece que você não tem pontos suficientes para comprar o produto ''%s'' :(\n","Almofada de Pescoço","Almofada de Pescoço");
                    }
                    system("pause");
                break;
                case 6:
                    if(c.ponto_Fidelidade>=250){
                        printf("\nComprando %s ...\n...\nCompra realizada com sucesso!\n ","Almofada Lombar");
                        c.ponto_Fidelidade=c.ponto_Fidelidade-250;
                        cod++;
                        p.q_alom++;
                    }
                    else{
                        printf("\nComprando %s ...\n...\nOPS! Parece que você não tem pontos suficientes para comprar o produto ''%s'' :(\n","Almofada Lombar","Almofada Lombar");
                    }
                    system("pause");
                break;
                case 7:
                    if(c.ponto_Fidelidade>=500){
                        printf("\nComprando %s ...\n...\nCompra realizada com sucesso!\n ","SUPER KIT LOCAMAIS");
                        c.ponto_Fidelidade=c.ponto_Fidelidade-500;
                        cod++;
                        p.q_kit++;
                    }
                    else{
                        printf("\nComprando %s ...\n...\nOPS! Parece que você não tem pontos suficientes para comprar o produto ''%s'' :(\n","SUPER KIT LOCAMAIS","SUPER KIT LOCAMAIS");
                    }
                    system("pause");
                break;
                case 8:
                    fwrite(&c, sizeof(c),1, arqCliente);
                    fflush(arqCliente);

                    //se a pessoa comprou algo (codigo será maior q 0)
                    if(cod>0){
                        cod=rand()%900000+100000;
                        posicao=localiza_premio(arqPremio,cod);

                        if(posicao==-1){
                            p.cod=cod;
                            printf("Seu código de premios é %ld, apresente esse código ao caixa para receber seus prêmios!\n",cod);
                            p.resgatado[0]='n';p.resgatado[1]='a';p.resgatado[2]='o';p.resgatado[3]='\0';
                            fseek(arqPremio,sizeof(p)*(posicao),SEEK_SET);
                            fflush(arqPremio);
                            fwrite(&p,sizeof(p),1,arqPremio);
                        }
                    }
                    //se a pessoa não comprar nada
                    else{
                        printf("Obrigado por visitar a loja\n");
                    }

                break;
                default:
                    printf("ERRO! Comando inválido!!!\n");
                break;
            }
        }while(op!=8);
    }
    else{
        printf("Código de cliente não reconhecido.\n");
    }
}


//Função que localiza os prêmios
int localiza_premio(FILE *arqPremio,long int codigoP){
    fflush(stdin);
    int posicao=-1, achou=0;
    premio p;
    fseek(arqPremio,0,SEEK_SET);
    fread(&p, sizeof(p), 1, arqPremio);
    while(!feof(arqPremio) && !achou){
         posicao++;
        if (p.cod==codigoP){
            achou=1;
        }
        fread(&p, sizeof(p),1, arqPremio);
    }

    if(achou){
        return posicao;
    }
     else{
        return -1;
    }
}

//Função que imprime os dados do prêmio e também resgata os prêmios
void imprime_arquivo_premio(FILE *arqPremio){
    fflush(stdin);
    premio p;
    long int cod;
    int posicao;
    printf("Digite o código do premio:");
    fflush(stdin);
    scanf("%ld",&cod);
    posicao=localiza_premio(arqPremio,cod);

    if(posicao!=-1){
        fseek(arqPremio,sizeof(p)*(posicao),SEEK_SET);
        fread(&p, sizeof(p),1, arqPremio);
        if(strcmp(p.resgatado,"nao")==0){
            printf("Código:%ld \n",p.cod);
            printf("Qntd %s: %d\n","Caneta",p.q_can);
            printf("Qntd %s: %d\n","Chaveiro",p.q_chav);
            printf("Qntd %s: %d\n","Aromatizador",p.q_aroma);
            printf("Qntd %s: %d\n","Flanela",p.q_flan);
            printf("Qntd %s: %d\n","Almofada de pescoço",p.q_apes);
            printf("Qntd %s: %d\n","Almofada Lombar",p.q_alom);
            printf("Qntd %s: %d\n","Kit LocaMais",p.q_kit);
            printf("\n*********************************************************************\n");
            p.resgatado[0]='s';p.resgatado[1]='i';p.resgatado[2]='m';p.resgatado[3]='\0';
            fseek(arqPremio,sizeof(p)*(posicao),SEEK_SET);
            fwrite(&p,sizeof(p),1,arqPremio);
        }
        else{
            printf("\nO prêmio já foi resgatado\n");
        }
    }
    else{
        printf("\nCodigo inválido\n");
    }
}


//Procedimento que oferece o kit locaMais aos clientes com pontuação a partir de 500pts
void kit_locaMais(FILE *arqCliente){
    fflush(stdin);
    cliente c;
    int cont=0;

    fseek(arqCliente,0,SEEK_SET);
    fread(&c, sizeof(c),1, arqCliente);

    printf("\nClientes com direito à um kit LocaMais:\n\n");

    while (!feof(arqCliente)){
        if(c.ponto_Fidelidade>=500){
            printf("Cliente: %d \n",c.codigoC);
            printf("Nome: %s \n",c.nome);
            printf("\nPontos Fidelidade: %i\n",c.ponto_Fidelidade);
            printf("\nTelefone: %s\n",c.telefone);
            printf("\n*********************************************************************\n");
            cont++;
        }
        fread(&c, sizeof(c),1, arqCliente);
    }
    if(cont==0){
        printf("OPS! Parece que nenhum cliente tem pontos de fidelidade suficiente!\n");
    }
}
