#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <conio.h>
#include <locale.h>
#include <time.h>

//struct dados do endere�o cliente
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

//struct datas da loca��o
struct data_retent{
    int dia;
    int mes;
    int ano;
};
typedef struct data_retent dr;

//struct dados da loca��o
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

//struct dados do pr�mio
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

//fun��o main abre os arquivos(arq do cliente, do ve�culo e da loca��o) e possui o menu para o usu�rio selecionar a op��o que deseja
int main(){
    FILE *arqCliente;//arquivo cliente
    FILE *arqVeiculo; //arquivo veiculo
    FILE *arqLocacao; //arquivo loca��o
    FILE *arqPremio; //arquivo pr�mio

    char op;
    setlocale(LC_ALL,"portuguese");
    srand(time(NULL));



    if (((arqVeiculo = fopen("veiculoDB.dat", "r+b"))==NULL) || ((arqCliente = fopen("clienteDB.dat", "r+b"))==NULL) || ((arqLocacao = fopen("locadoraDB.dat", "r+b"))==NULL) || ((arqPremio = fopen("premioDB.dat", "r+b"))==NULL)){ // arquivo existe
        printf("Arquivo n�o existia ... criando arquivo!");
        if( ((arqVeiculo = fopen("veiculoDB.dat", "w+b"))==NULL) || ((arqCliente = fopen("clienteDB.dat", "w+b"))==NULL) || ((arqLocacao = fopen("locadoraDB.dat", "w+b"))==NULL) || ((arqPremio = fopen("premioDB.dat", "w+b"))==NULL)){ //arq n�o existe
            printf("Erro na cria��o do arquivo!!");
            exit(1);
        }
        system("pause");
    }


    do{
        printf("\n----------------------------Menu Principal---------------------------\n");

        printf("Escolha uma op��o:\n\n");
        printf("(a) - Cadastrar cliente\n");
        printf("(b) - Alterar dados do cliente\n");
        printf("(c) - Listar clientes\n");
        printf("(d) - Cadastrar ve�culo\n");
        printf("(e) - Alterar dados ve�culo\n");
        printf("(f) - Listar ve�culos\n");
        printf("(g) - Aluguar veiculo\n");
        printf("(h) - Concluir locacao\n");
        printf("(i) - Listar loca��es\n");
        printf("(j) - Pesquisar loca��es espec�ficas de um cliente\n");
        printf("(k) - Pesquisar informa��es de um cliente\n");
        printf("(l) - Pesquisar informa��es de um ve�culo\n");
        printf("(m) - Pesquisar ganhadores kit LocaMais\n");
        printf("(n) - Loja de Pontos\n");
        printf("(o) - Resgatar Pr�mio\n");
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
            printf("\n-------------------------Cadastrando Ve�culo-------------------------\n");
            inclui_veiculo(arqVeiculo);
            break;
        case 'e':
            printf("\n---------------------------------------------------------------------\n");
            printf("\n---------------------Alterando dados do Ve�culo----------------------\n");
            altera_arquivo_veiculo(arqVeiculo);
            break;
        case 'f':
            printf("\n---------------------------------------------------------------------\n");
            printf("\n----------------------Listagem dos Ve�culos--------------------------\n");
            imprime_arquivo_veiculo(arqVeiculo);
            break;
        case 'g':
            printf("\n---------------------------------------------------------------------\n");
            printf("\n----------------------Preenchendo a Loca��o--------------------------\n");
            inclui_locacao(arqLocacao, arqVeiculo, arqCliente);
            break;
        case 'h':
            printf("\n---------------------------------------------------------------------\n");
            printf("\n----------------------Concluindo a Loca��o---------------------------\n");
            baixa_locacao(arqLocacao,arqVeiculo, arqCliente);
            break;
        case 'i':
            printf("\n---------------------------------------------------------------------\n");
            printf("\n--------------------------Listagem das Loca��es----------------------\n");
            imprime_arquivo_locacao(arqLocacao);
            break;
        case 'j':
            printf("\n---------------------------------------------------------------------\n");
            printf("\n-----------Pesquisando loca��es espec�ficas de um Cliente------------\n");
            pesquisa_locacoes_cliente(arqLocacao, arqCliente);
            break;
        case 'k':
            printf("\n---------------------------------------------------------------------\n");
            printf("\n-----------------Pesquisa Informa��es de um Cliente------------------\n");
            pesquisa_Informacao_Cliente(arqCliente);
            system("pause");
            break;
        case 'l':
            printf("\n---------------------------------------------------------------------\n");
            printf("\n-----------------Pesquisa Informa��es de um Ve�culo------------------\n");
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
            printf("\nOp��o inv�lida\n");
        }
    }
    while (op!='p');
    fclose(arqCliente);
    fclose(arqVeiculo);
    fclose(arqLocacao);
    fclose(arqPremio);
    return 0;
}



/*-----------------------------------------------------FUN��ES PARA O CLIENTE-------------------------------------------------------------------*/
//procedimento que cadastra/inclui um cliente no sistema
void inclui_cliente(FILE *arqCliente){
    fflush(stdin);
    cliente c;
    int posicao;

    printf("\n");
    c.codigoC=1;
    do{
        printf("\nDigite o c�digo com at� 3 d�gitos: ");
        fflush(stdin);
        scanf("%3d",&c.codigoC);
        if(c.codigoC<=1){
            printf("\nERRO!");
        }
    }while( c.codigoC<=1);
    posicao=localiza_cliente(arqCliente,c.codigoC);
    if (posicao==-1){ //n�o tinha codigo no arquivo
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
        printf("\nO c�digo %d j� existe no arquivo. Inclus�o n�o realizada!\n",c.codigoC);
    }
}


//procedimento que altera os dados do cliente
void altera_arquivo_cliente(FILE *arqCliente){
    fflush(stdin);
    int codigoC,posicao;
    cliente c;
    printf("\nPara alterar, digite o c�digo do cliente: ");
    scanf("%3d",&codigoC);
    posicao=localiza_cliente(arqCliente,codigoC);

    //localizou o cliente
    if (posicao!=-1){

        fseek(arqCliente,sizeof(c)*(posicao),SEEK_SET);
        fread(&c, sizeof(c),1, arqCliente);
        printf("\n*Dados atuais* \n");
        printf("-Cliente: %i \n-Nome: %s\n-Telefone: %s \n\n-Rua: %s\n-Bairro: %s\n-N�: %i\n-Cidade: %s\n-Estado: %s\n-Cep: %s ",c.codigoC,c.nome,c.telefone, c.endereco.rua, c.endereco.bairro, c.endereco.num,c.endereco.cidade, c.endereco.estado, c.endereco.cep);

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
        printf("\nC�digo do cliente n�o encontrado");
    }
}


//procedimento que localiza o cliente (comparando o c�digo digitado com os c�digos que existem no arquivo cliente)
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


//procedimento que pesquisa e mostra informa��es de um cliente
void pesquisa_Informacao_Cliente(FILE *arqCliente){
    fflush(stdin);
    cliente c;
    int posicao, codDigitado;
    printf("\nDigite o c�digo do cliente que deseja procurar: ");
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
                    printf("\tPARAB�NS!!! VOC� � ELEG�VEL PARA UM PR�MIO!!!");
                }
                printf("\nTelefone: %s\n",c.telefone);
                printf("\n*Endere�o* \n");
                printf("Rua:%s \nbairro: %s \nN� %i \nCep: %s \nCidade: %s\nEstado: %s",c.endereco.rua,c.endereco.bairro,c.endereco.num,c.endereco.cep, c.endereco.cidade, c.endereco.estado);
                printf("\n\n");
            }
            fread(&c, sizeof(c),1, arqCliente);
        }
    }
    else{
        printf("\nC�digo do cliente n�o encontrado\n");
    }
}


//procedimento que pesquisa e mostra informa��es de um cliente
void pesquisa_locacoes_cliente(FILE *arqLocacao, FILE *arqCliente){
    fflush(stdin);
    locacao l;
    int posicao, codDigitado;
    printf("\nDigite o c�digo do cliente para procurar suas loca��es: ");
    fflush(stdin);
    scanf("%3i",&codDigitado);
    posicao=localiza_cliente(arqCliente, codDigitado);

    if (posicao != -1){
        fseek(arqLocacao,0,SEEK_SET);
        fread(&l, sizeof(l),1,arqLocacao);

        while(!feof (arqLocacao) ){
            if(codDigitado == l.cod_cliente){
                printf("\nLoca��o c�digo:%llu \n",l.codigo);
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
        printf("\nC�digo do cliente n�o encontrado\n");
    }
}


//procedimento que imprime informa��es de todos os clientes
void imprime_arquivo_cliente(FILE *arqCliente){
    fflush(stdin);
    cliente c;
    fseek(arqCliente,0,SEEK_SET);
    fread(&c, sizeof(c),1, arqCliente);

    while (!feof(arqCliente)){
        printf("C�digo do Cliente: %d \n",c.codigoC);
        printf("Nome: %s \n",c.nome);
        printf("\nPontos Fidelidade: %i\n",c.ponto_Fidelidade);
        printf("\nTelefone: %s\n",c.telefone);
        printf("\n*Endere�o* \n");
        printf("Rua:%s \nbairro: %s \nN� %i \nCep: %s \nCidade: %s\nEstado: %s",c.endereco.rua,c.endereco.bairro,c.endereco.num,c.endereco.cep, c.endereco.cidade, c.endereco.estado);
        printf("\n*********************************************************************\n");

        fread(&c, sizeof(c),1, arqCliente);
    }
}




/*--------------------------------------------------FUN��ES APRA O VE�CULO-----------------------------------------------------------------------*/
//procedimento que cadastra/inclui um ve�culo no sistema
void inclui_veiculo(FILE *arqVeiculo){
    fflush(stdin);
    veiculo v;
    int posicao;
    printf("\n\n");
    v.codigoV=1;
    do{
        printf("Digite o c�digo do veiculo com at� tr�s digitos: ");
        fflush(stdin);
        scanf("%3d",&v.codigoV);
        if(v.codigoV<=1){
            printf("\nERRO!");
        }
    }while(v.codigoV<=1);

        posicao=localiza_veiculo(arqVeiculo,v.codigoV);

    if (posicao==-1){ //n�o tinha codigo no arquivo
        printf("Modelo do ve�culo: ");
        fflush(stdin);
        gets(v.modelo);
        printf("Descri��o do veiculo: ");
        fflush(stdin);
        gets(v.descricao);
        printf("Cor do ve�culo: ");
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
        //chama o procedimento do status do carro para o usu�rio selecionar a op��o
        status_veiculo(&v);

        printf("Pre�o da di�ria: ");
        fflush(stdin);
        scanf("%f",&v.valor_diaria);

        fseek(arqVeiculo,0,SEEK_END); // posicionado o arquivo no final
        fwrite(&v, sizeof(v),1,arqVeiculo); //gravando os dados
        fflush(arqVeiculo);
    }
     else{
        printf("C�digo %d j� existe no arquivo. Inclus�o n�o realizada!\n", v.codigoV);
    }
}


//procedimento que altera os dados do ve�culo
void altera_arquivo_veiculo(FILE *arqVeiculo){
    fflush(stdin);
    int codigoV,posicao;
    veiculo v;
    printf("\nPara alterar, digite o c�digo do ve�culo: ");
    scanf("%d",&codigoV);
    posicao=localiza_veiculo(arqVeiculo,codigoV);

    //localizou a veiculo
    if (posicao!=-1){
        fseek(arqVeiculo,sizeof(v)*(posicao),SEEK_SET);
        fread(&v, sizeof(v),1, arqVeiculo);
        printf("\n*Dados atuais* \n");
        printf("-Ve�culo: %i \n-Modelo: %s \n-Descri��o: %s\n-Cor: %s \n-Placa: %s\n-Qtde ocupantes: %i\n-Status: %s\n-Valor di�ria: %.2f",v.codigoV,v.modelo,v.descricao,v.cor,v.placa,v.qtd_ocupante,v.status,v.valor_diaria);

        printf("\n\n*Nova descri��o*");

        printf("Modelo do ve�culo: ");
        fflush(stdin);
        gets(v.modelo);
        printf("Descri��o do veiculo: ");
        fflush(stdin);
        gets(v.descricao);
        printf("Cor do ve�culo: ");
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

        //chama o procedimento do status do carro para o usu�rio selecionar a op��o
        status_veiculo(&v);

        printf("Pre�o da di�ria: ");
        fflush(stdin);
        scanf("%f",&v.valor_diaria);

        fseek(arqVeiculo,sizeof(v)*(posicao),SEEK_SET);
        fwrite(&v, sizeof(v),1, arqVeiculo);
        fflush(arqVeiculo);
    }
    else{
        printf("\nC�digo do ve�culo n�o encontrado");
    }
}


//procedimento que localiza o ve�culo (comparando o c�digo digitado com os c�digos que existem no arquivo do ve�culo)
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


//procedimento que pesquisa e mostra informa��es de um ve�culo
void pesquisa_Informacao_Veiculo(FILE *arqVeiculo){
    fflush(stdin);
    veiculo v;
    int posicao, codDigitado;
    printf("\nDigite o c�digo do veiculo que deseja procurar: ");
    fflush(stdin);
    scanf("%3i",&codDigitado);
    posicao=localiza_veiculo(arqVeiculo, codDigitado);

    if (posicao != -1){
        fseek(arqVeiculo,0,SEEK_SET);
        fread(&v, sizeof(v),1,arqVeiculo);

        while(!feof (arqVeiculo) ){
            if(codDigitado == v.codigoV){
                printf("Modelo: %s\n",v.modelo);
                printf("Descri��o: %s \n",v.descricao);
                printf("Cor: %s\n",v.cor);
                printf("Placa: %s\n",v.placa);
                printf("Qtd de ocupantes: %i\n",v.qtd_ocupante);
                printf("Status: %s\n",v.status);
                printf("Valor di�ria: %.2f\n",v.valor_diaria);
                printf("\n\n");
            }
            fread(&v, sizeof(v),1, arqVeiculo);
        }
    }
    else{
        printf("\nC�digo do ve�culo n�o encontrado\n");
    }
}

//procedimento que imprime todos os ve�culos
void imprime_arquivo_veiculo(FILE *arqVeiculo){
    fflush(stdin);
    veiculo v;
    fseek(arqVeiculo,0,SEEK_SET);
    fread(&v, sizeof(v),1, arqVeiculo);

    while (!feof(arqVeiculo)){
        printf("\nC�d ve�culo: %i \n",v.codigoV);
        printf("Modelo: %s\n",v.modelo);
        printf("Descri��o: %s \n",v.descricao);
        printf("Cor: %s\n",v.cor);
        printf("Placa: %s\n",v.placa);
        printf("Qtd de ocupantes: %i\n",v.qtd_ocupante);
        printf("Status: %s\n",v.status);
        printf("Valor di�ria: %.2f\n",v.valor_diaria);
        printf("\n*********************************************************************\n");
        fread(&v, sizeof(v),1, arqVeiculo);
    }
}

//procedimento que o usu�rio seleciona a op��o do status do ve�culo
void status_veiculo(veiculo *v){
    fflush(stdin);

    int opcao;

    do{
        printf("\nDigite o status do ve�culo: \n");
        printf("(1) - Alugado\n");
        printf("(2) - Dispon�vel\n");
        printf("(3) - Em manuten��o\n");

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
                v->status[8]= '�';
                v->status[9]= '�';
                v->status[9]= 'o';
                v->status[10]='\0';
            break;
            default:
                printf("\nOpcao invalida. Digite novamente o status: ");
        }
    }
    while((opcao!= 1) && (opcao !=2) && (opcao !=3));
}




/*----------------------------------------Fun��es para a Loca��o----------------------------------------------------------------*/
//procedimento que cadastra/inclui uma loca��o no sistema
void inclui_locacao(FILE *arqLocacao, FILE *arqVeiculo, FILE *arqCliente){
    fflush(stdin);
    locacao l;
    veiculo v;
    char status[20];
    int posicao,carro_lote=(rand()%9000)+1000,ocupantes,disp=0,cod_cliente;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    tm.tm_hour=tm.tm_hour-3; //Simulando nosso fuso-horario de acordo com horario do time_t (aprox 3 horas a mais que nosso hor�rio)
    if(tm.tm_hour<8||tm.tm_hour>18){ //restringe o hor�rio para fazer uma loca��o
        printf("\nPor favor, volte no hor�rio comercial.");
    }
    else{ //se estiver no hor�rio comercial, inicia o cadastro da loca��o

        printf("\nDigite o c�digo do cliente: ");
        fflush(stdin);
        scanf("%3d",&cod_cliente);
        posicao=localiza_cliente(arqCliente,cod_cliente);

        if(posicao!=-1){
            printf("\nDigite a quantia de ocupantes desejada: ");
            fflush(stdin);
            scanf("%d",&ocupantes);
            //chama o procedimento que lista os carros disponiveis de acordo com a qtd de ocupantes inserida pelo usu�rio
            disp=list_ocupantes(arqVeiculo,ocupantes);

            if(disp>0){ //caso haja carro dispon�vel, � listado todos e o usu�rio seleciona o carro que ele deseja
                printf("\nDigite o c�digo de um veiculo dispon�vel desejado: ");
                fflush(stdin);
                scanf("%3d",&l.cod_veiculo);

                posicao=localiza_veiculo(arqVeiculo,l.cod_veiculo);
                fseek(arqVeiculo,sizeof(v)*(posicao),SEEK_SET);
                fread(&v, sizeof(v),1, arqVeiculo);
                strcpy(status,v.status);

                //aqui come�a o cadastro da loca��o para o carro selecionado
                if ((posicao!=-1)&&(strcmp(status,"disponivel")==0)){
                    l.cod_cliente=cod_cliente;
                    l.codigo=(l.cod_cliente*(unsigned long long int)10000000)+(l.cod_veiculo*10000)+(carro_lote);
                    printf("Codigo locacao: %llu\n",l.codigo);
                    posicao=localiza_locacao(arqLocacao,l.codigo);
                    if (posicao==-1){  //n�o tinha codigo no arquivo

                        printf("Digite as datas da locacao: ");
                        fflush(stdin);
                        l.qnt_dias=get_days(&l.retirada,&l.entrega); //chama a fun��o de registrar as datas da loca��o
                        l.qnt_dias=l.qnt_dias+1;

                        //confere se o cliente quer um seguro ou n�o
                        do{
                            printf("Digite o seguro da locacao (sim ou nao): ");
                            fflush(stdin);
                            gets(l.seguro);
                        }
                        while(((strcmp(l.seguro,"nao")!=0)&&((strcmp(l.seguro,"sim")!=0))));

                        printf("Dias de loca��o: %d",l.qnt_dias);

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
                        printf("\nEsse c�digo j� existe");
                    }
                }
                else if(posicao==-1){
                    printf("\nC�digo de veiculo inv�lido");
                }
                else{
                    printf("\nVeiculo %s!\n",status);
                }
            }
            else{
                printf("\nPerd�o, n�o h� ve�culos dispon�veis no momento :(\n");
            }

        }
        else{
            printf("\nC�digo de cliente inv�lido\n");
        }

    }

}


/*procedimento que finaliza/baixa a loca��o no sistema quando o usuario entrega o ve�culo.
  Ela confere o total de dias alugados e realiza a cobran�a o pagamento.
  Se o total de dias for diferente do que foi acordado, h� a cobran�a de juros*/
void baixa_locacao(FILE *arqLocacao, FILE *arqVeiculo, FILE *arqCliente){
    fflush(stdin);
    unsigned long long int codigo,salva_codigo;
    int posicao1,posicao2,posicao3,dias_de_juros,qnt_dias,dia,mes,ano;
    float valor_final=0.0;
    locacao l;
    veiculo v;
    cliente c;
    printf("Digite o c�digo da loca��o: ");
    scanf("%10llu",&codigo);
    fflush(stdin);

    posicao1=localiza_locacao(arqLocacao,codigo); //posicao1 chama a fun��o para localizar as loca��es

    if (posicao1!=-1){ // localiza o c�digo da loca��o para finaliz�-la
        salva_codigo=codigo;
        codigo=((codigo%10000000)/10000);
        posicao2=localiza_veiculo(arqVeiculo,codigo); //posi��o2 chama a fun��o para localizar os ve�culos

        if(posicao2!=-1){
            fseek(arqLocacao,sizeof(l)*(posicao1),SEEK_SET);
            fread(&l, sizeof(l),1, arqLocacao);

            if(strcmp(l.baixa,"nao")==0){ //confere se a loca��o selecionada j� obteve baixa ou n�o
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

                 //calcula e da baixa na loca��o
                do{
                    valor_final=0.0;
                    printf("Data de Entrega: ");
                    fflush(stdin);
                    scanf("%d/%d/%d",&l.entrega.dia,&l.entrega.mes,&l.entrega.ano);
                    dias_de_juros=dias_juros(l.retirada,l.entrega);

                    //calcula o valor da loca��o sem juros
                    if (dias_de_juros<=0){
                        l.qnt_dias=l.qnt_dias+dias_de_juros;
                    }
                    valor_final=((v.valor_diaria)*(l.qnt_dias))/1.0;

                    //se o usu�rio solicitou seguro do carro, acrescenta o valor do seguro no total a ser pago
                    if(strcmp(l.seguro,"sim")==0){
                        valor_final=valor_final+50.0;
                    }

                    //se h� juros, acrescenta o valor do juros no total a ser pago
                    if(dias_de_juros>=1){
                        valor_final=valor_final+(valor_final*0.05)+(30*dias_de_juros);
                    }

                    //confere se o valor da loca��o est� correto a partir da data inserida
                    if(valor_final<=0){
                        printf("\nData inv�lida. Insira uma data v�lida\n");
                    }

                }while(valor_final<=0);

                printf("\nPre�o total da sua loca��o: %.2f",valor_final);

                printf("\nTotal de dias de loca��o: %d",l.qnt_dias);

                //printando o total de dias atrasados
                if(dias_de_juros>0){
                    printf("\nDias de atraso: %d",dias_de_juros);
                }

                codigo=salva_codigo;
                codigo=codigo/10000000;
                posicao3=localiza_cliente(arqCliente,codigo); //posi��o3 chama a fun��o para localizar o cliente
                fseek(arqCliente,sizeof(c)*posicao3,SEEK_SET);
                fread(&c, sizeof(c),1, arqCliente);
                fseek(arqCliente,sizeof(c)*posicao3,SEEK_SET);

                //calcula os pontos fidelidade do cliente
                int pt=c.ponto_Fidelidade;
                c.ponto_Fidelidade=(pt+(qnt_dias*10));
                printf("\nSeus pontos de fidelidade s�o: %d",c.ponto_Fidelidade);
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
                printf("Essa loca��o j� teve baixa");
            }
        }
        else{
            printf("Erro ao localizar veiculo da loca��o");
        }
    }
    else{
        printf("N�o h� loca��o com esse c�digo");
    }
}


//procedimento que localiza a loca��o (comparando o c�digo digitado com os c�digos que existem no arquivo da loca��o)
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


//procedimento que imprime o arquivo de todas as loca��es
void imprime_arquivo_locacao(FILE *arqLocacao){
    fflush(stdin);
    locacao l;
    fseek(arqLocacao,0,SEEK_SET);
    fread(&l, sizeof(l),1, arqLocacao);
    while (!feof(arqLocacao)){
        printf("C�digo: %llu \n",l.codigo);
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


//Fun��o que compara o total de ocupantes no ve�culo, e lista quais ve�culos est�o dispon�veis a partir da quantidade digitada*/
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
                printf("\nVe�culo: %d \n",v.codigoV);
                printf("Descri��o: %s \n",v.descricao);
                printf("Modelo: %s\n",v.modelo);
                printf("Cor: %s\n",v.cor);
                printf("Placa: %s\n",v.placa);
                printf("Valor di�ria: %.2f\n",v.valor_diaria);
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




/*----------------------------------------Fun��es para as Datas----------------------------------------------------------------*/
//fun��o que define e confere os dias de retirada e entrega, de acordo com regras v�lidas ou n�o
int get_days(dr *retirada, dr *entrega){
    fflush(stdin);
    int daytotal,save_month,save_day,save_year;

    int day_diff, mon_diff, year_diff,var=0; //vari�veis de diferen�a de dias, diferen�a de meses e diferen�a de anos

    printf("\nDigite a data de retirada - inserindo as barras - (DD/MM/YYYY): ");
    scanf("%d/%d/%d", &retirada->dia, &retirada->mes, &retirada->ano);

    printf("\nDigite a data de entrega - inserindo as barras - (DD/MM/YYYY): ");
    scanf("%d/%d/%d", &entrega->dia, &entrega->mes, &entrega->ano);

    save_day=entrega->dia;
    save_month=entrega->mes;
    save_year=entrega->ano;

    while((!valid_date(retirada->dia, retirada->mes, retirada->ano))||(!valid_date(entrega->dia, entrega->mes, entrega->ano))){
        if(!valid_date(retirada->dia, retirada->mes, retirada->ano)){ //isso valida se a data de retirada � v�lida (de acordo com as restri��es na fun��o de validar)
            printf("\nPrimeira data � inv�lida.\n");
    }
        if(!valid_date(entrega->dia, entrega->mes, entrega->ano)){//isso valida se a data de entregaa � v�lida (de acordo com as restri��es na fun��o de validar)
            printf("\nSegunda data � inv�lida");
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
            //verifica se o ano � bissexto
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

        //emprestar dias de janeiro ou mar�o ou maio ou julho ou agosto ou outubro ou dezembro (meses com 31 dias)
        else{
           entrega->dia += 31;
        }

        entrega->mes = entrega->mes - 1;
    }

    if (entrega->mes < retirada->mes){
        entrega->mes += 12;
        entrega->ano -= 1;
    }

    //calcula as diferen�as entre dias, meses e anos
    day_diff = entrega->dia - retirada->dia;
    mon_diff = entrega->mes - retirada->mes;
    year_diff = entrega->ano - retirada->ano;
    entrega->mes=save_month;
    entrega->dia=save_day;
    entrega->ano=save_year;

    //c�lculo do total de dias do carro alugado
    daytotal=day_diff+(30*mon_diff)+(365*year_diff)+var;

    return daytotal;
}


//Fun��o para checar se a data � valida
int valid_date(int day, int mon, int year){
    fflush(stdin);
    int is_valid = 1, is_leap = 0;

    if (year >= 2000 && year <= 2100){

        //verifica se o ano � bissexto
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)){
            is_leap = 1;
        }

        // Verifica se o m�s est� entre 1 e 12
        if(mon >= 1 && mon <= 12){
            //verifica os dias de fevereiro (28 dias ou 29 quando o ano � bissexto)
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


//Fun��o que calcula os dias de juros da loca��o
int dias_juros(dr retir, dr entr){
    fflush(stdin);
    int daytotal,save_month,save_day,save_year;

    int day_diff, mon_diff, year_diff,var=0;

    save_day=entr.dia;
    save_month=entr.mes;
    save_year=entr.ano;

    while((!valid_date(retir.dia, retir.mes, retir.ano))||(!valid_date(save_day, save_month, save_year))){
        if(!valid_date(retir.dia, retir.mes, retir.ano)){
            printf("\nPrimeira Data � inv�lida.\n");
    }
        if(!valid_date(save_day, save_month, save_year)){
            printf("\nSegunda Data � inv�lida\n");
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
            //verifica se o ano � bissexto
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

        //emprestar dias de janeiro ou mar�o ou maio ou julho ou agosto ou outubro ou dezembro (meses com 31 dias)
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




/*----------------------------------------Fun��es para a  Loja----------------------------------------------------------------*/

/*Procedimento que abre a loja de pontos e lista seus itens.
  A partir das escolhas do cliente, o sistema ir� gerar um c�digo para o cliente poder resgatar seus pr�mios posteriormente*/
void loja_de_pontos(FILE *arqCliente, FILE *arqPremio){
    fflush(stdin);
    cliente c;
    premio p;
    int cod_cliente,posicao,op;
    long int cod=0;
    //vari�veis para os itens (almofada lombar, almofada pesco�o, aroma, caneta, chaveiro, flanela e o kit locaMaias)
    p.q_alom=0;p.q_apes=0;p.q_aroma=0;p.q_can=0;p.q_chav=0;p.q_flan=0;p.q_kit=0;
    fflush(arqCliente);

    do{
        printf("Digite o c�digo do cliente para entrar na loja de pontos: \n");
        fflush(stdin);
        scanf("%3d",&cod_cliente);
        if(cod_cliente<=1){
            printf("\nERRO! C�digo inv�lido");
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
            printf("(5) - %s LocaMais: %d pts\n","Almofada de Pesco�o",200);
            printf("(6) - %s LocaMais: %d pts\n","Almofada Lombar",250);
            printf("(7) - %s LocaMais: %d pts\n","SUPER KIT",500);
            printf("O SUPER KIT contem todos os itens da loja de pontos por um desconto!\n\n");

            printf("Digite o que deseja comprar na loja, ou digite '8' para pegar seu c�digo e sair da loja: ");
            scanf("%d",&op);

            //switch para as op��es de compra e caso o cliente n�o possua pontos suficientes, a compra n�o � realizada
            switch(op){
                case 1:
                    if(c.ponto_Fidelidade>=15){
                        printf("\nComprando %s ...\n...\nCompra realizada com sucesso!\n ","Caneta");
                        c.ponto_Fidelidade=c.ponto_Fidelidade-15;
                        cod++;
                        p.q_can++;
                    }
                    else{
                        printf("\nComprando %s ...\n...\nOPS! Parece que voc� n�o tem pontos suficientes para comprar o produto ''%s'' :(\n","Caneta","Caneta");
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
                        printf("\nComprando %s ...\n...\nOPS! Parece que voc� n�o tem pontos suficientes para comprar o produto ''%s'' :(\n","Chaveiro","Chaveiro");
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
                        printf("\nComprando %s ...\n...\nOPS! Parece que voc� n�o tem pontos suficientes para comprar o produto ''%s'' :(\n","Aromatizador de carro","Aromatizador de carro");
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
                        printf("\nComprando %s ...\n...\nOPS! Parece que voc� n�o tem pontos suficientes para comprar o produto ''%s'' :(\n","Flanela","Flanela");
                    }
                    system("pause");
                break;
                case 5:
                    if(c.ponto_Fidelidade>=200){
                        printf("\nComprando %s ...\n...\nCompra realizada com sucesso!\n ","Almofada de Pesco�o");
                        c.ponto_Fidelidade=c.ponto_Fidelidade-200;
                        cod++;
                        p.q_apes++;
                    }
                    else{
                        printf("\nComprando %s ...\n...\nOPS! Parece que voc� n�o tem pontos suficientes para comprar o produto ''%s'' :(\n","Almofada de Pesco�o","Almofada de Pesco�o");
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
                        printf("\nComprando %s ...\n...\nOPS! Parece que voc� n�o tem pontos suficientes para comprar o produto ''%s'' :(\n","Almofada Lombar","Almofada Lombar");
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
                        printf("\nComprando %s ...\n...\nOPS! Parece que voc� n�o tem pontos suficientes para comprar o produto ''%s'' :(\n","SUPER KIT LOCAMAIS","SUPER KIT LOCAMAIS");
                    }
                    system("pause");
                break;
                case 8:
                    fwrite(&c, sizeof(c),1, arqCliente);
                    fflush(arqCliente);

                    //se a pessoa comprou algo (codigo ser� maior q 0)
                    if(cod>0){
                        cod=rand()%900000+100000;
                        posicao=localiza_premio(arqPremio,cod);

                        if(posicao==-1){
                            p.cod=cod;
                            printf("Seu c�digo de premios � %ld, apresente esse c�digo ao caixa para receber seus pr�mios!\n",cod);
                            p.resgatado[0]='n';p.resgatado[1]='a';p.resgatado[2]='o';p.resgatado[3]='\0';
                            fseek(arqPremio,sizeof(p)*(posicao),SEEK_SET);
                            fflush(arqPremio);
                            fwrite(&p,sizeof(p),1,arqPremio);
                        }
                    }
                    //se a pessoa n�o comprar nada
                    else{
                        printf("Obrigado por visitar a loja\n");
                    }

                break;
                default:
                    printf("ERRO! Comando inv�lido!!!\n");
                break;
            }
        }while(op!=8);
    }
    else{
        printf("C�digo de cliente n�o reconhecido.\n");
    }
}


//Fun��o que localiza os pr�mios
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

//Fun��o que imprime os dados do pr�mio e tamb�m resgata os pr�mios
void imprime_arquivo_premio(FILE *arqPremio){
    fflush(stdin);
    premio p;
    long int cod;
    int posicao;
    printf("Digite o c�digo do premio:");
    fflush(stdin);
    scanf("%ld",&cod);
    posicao=localiza_premio(arqPremio,cod);

    if(posicao!=-1){
        fseek(arqPremio,sizeof(p)*(posicao),SEEK_SET);
        fread(&p, sizeof(p),1, arqPremio);
        if(strcmp(p.resgatado,"nao")==0){
            printf("C�digo:%ld \n",p.cod);
            printf("Qntd %s: %d\n","Caneta",p.q_can);
            printf("Qntd %s: %d\n","Chaveiro",p.q_chav);
            printf("Qntd %s: %d\n","Aromatizador",p.q_aroma);
            printf("Qntd %s: %d\n","Flanela",p.q_flan);
            printf("Qntd %s: %d\n","Almofada de pesco�o",p.q_apes);
            printf("Qntd %s: %d\n","Almofada Lombar",p.q_alom);
            printf("Qntd %s: %d\n","Kit LocaMais",p.q_kit);
            printf("\n*********************************************************************\n");
            p.resgatado[0]='s';p.resgatado[1]='i';p.resgatado[2]='m';p.resgatado[3]='\0';
            fseek(arqPremio,sizeof(p)*(posicao),SEEK_SET);
            fwrite(&p,sizeof(p),1,arqPremio);
        }
        else{
            printf("\nO pr�mio j� foi resgatado\n");
        }
    }
    else{
        printf("\nCodigo inv�lido\n");
    }
}


//Procedimento que oferece o kit locaMais aos clientes com pontua��o a partir de 500pts
void kit_locaMais(FILE *arqCliente){
    fflush(stdin);
    cliente c;
    int cont=0;

    fseek(arqCliente,0,SEEK_SET);
    fread(&c, sizeof(c),1, arqCliente);

    printf("\nClientes com direito � um kit LocaMais:\n\n");

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
