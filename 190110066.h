#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

#define TAM_MAX_CPF 12
#define TAM_MAX_CNPJ 15
#define TAM_MAX_NOME 100
#define TAM_MAX_DATA 8

//STRUCT PARA GUARDAR AS INFORMACOES PASSADAS PELO USUARIO
typedef struct{
    char cnpj_us[TAM_MAX_CNPJ];
    char nome_us[TAM_MAX_NOME];
    char data_us[TAM_MAX_DATA];
    float pot_est;
}CADASTRAR_USINA;

typedef struct{
    char iden_con[TAM_MAX_CNPJ];
    char nome_con[TAM_MAX_NOME];
}CADASTRAR_CONSUMIDOR;

typedef struct{
    char cnpj_con_us[TAM_MAX_CNPJ];
    char iden_contr_consu[TAM_MAX_CNPJ];
    char data_con[TAM_MAX_DATA];
    float pot_cont;
}CADASTRAR_CONTRATO;

int verifica_cpf (char *cpf){//VERIFICAR O CPF 

    int int_cpf[TAM_MAX_CPF];
    int i,sum,rest_1,digit_1,rest_2,digit_2;
    sum = 0;
    FILE* arquivo;
    char iden_consumidor[TAM_MAX_CPF];
    
    //RETORNAR COMO INVALIDO CPF COM TODOS OS DIGITOS IGUAIS
    if (strcmp(cpf,"00000000000") == 0 || strcmp(cpf,"11111111111") == 0 || strcmp(cpf,"22222222222") == 0 || strcmp(cpf,"33333333333") == 0 || strcmp(cpf,"44444444444") == 0 || strcmp(cpf,"55555555555") == 0 || strcmp(cpf,"66666666666") == 0 || strcmp(cpf,"77777777777") == 0 || strcmp(cpf,"88888888888") == 0 || strcmp(cpf,"99999999999") == 0 )
    {
        return 0;
    }else{
        //CONVERTER UMA STRING PARA INTEIROS
        for ( i = 0; i <= 10; i++)
        {
            int_cpf[i] = cpf[i] - 48;
        }
        //VERIFICAR O PRIMEIRO DIGITO VERIFICADOR
        for ( i = 0; i < 9; i++)
        {
            sum = sum + (int_cpf[i]*(10-i)); //SUM = SOMA DA MULTIPLICACAO DE 10 - i POR CADA DIGITO DO CPF
        }
        rest_1 = sum % 11;
        //SE O RESTO FOR 0 OU 1, O PRIMEIRO DIGITO VERIFICADOR SERA 0, CASO CONTRARIO, O DIGITO SERA 11 - RESTO DA DIVISAO 
        if (rest_1 == 0 || rest_1 == 1)
        {
            digit_1 = 0; 
        }else{
            digit_1 = 11 - rest_1;
        }
        sum = 0; //ZERAR A SOMA
        //VERIFICAR O SEGUNDO DIGITO VERIFICADOR
        for ( i = 0; i < 10 ; i++)
        {
            sum = sum + (int_cpf[i]*(11-i));
        }
        rest_2 = sum % 11;
        //SE O RESTO FOR 0 OU 1, O SEGUNDO DIGITO VERIFICADOR SERA 0, CASO CONTRARIO, O DIGITO SERA 11 - RESTO DA DIVISAO
        if (rest_2 == 0 || rest_2 == 1)
        {
            digit_2 = 0;
        }else{
            digit_2 = 11 - rest_2;
        }
        //SE O digit_1 FOR IGUAL AO DIGITO 10 DO CPF E O digit_2 FOR IGUAL AO DIGITO 11 DO CPF, ENTAO O CPF SERA VALIDO, CASO CONTRARIO, SERA INVALIDO
        //RETURN 1 PARA VALIDO E 0 PARA INVALIDO
        if ((digit_1 == int_cpf[9]) && (digit_2 == int_cpf[10]))
        {
            return 1;
        }else{
            return 0;
        }
    }
}
int verifica_data (char *data){
    int int_data[TAM_MAX_DATA];
    int a,m,d,i;
    //TARNSFORMAR STRING EM INTEIRO
    for ( i = 0; i < 8; i++)
    {
        int_data[i] = data[i] - 48;
    }
    //TRANSFORMAR DOIS INTEIROS SEPARADOS EM INTEIROS JUNTOS TIPO 2,3 VAI VIRAR 23
    d = int_data[0]*10 + int_data[1];
    m = int_data[2]*10 + int_data[3];
    a = int_data[4]*1000 + int_data[5]*100 + int_data[6]*10 + int_data[7];

    if(a>=0) //ANO TEM QUE SER MAIOR QUE 0
    {
        if (m>=1 && m<=12) //MES TEM QUE ESTAR ENTRE 1 E 12
        {
            //QUANTIDADE DE DIAS QUE CADA MES TEM, TIRANDO O MES DOIS QUE PODE TER 28 OU 29 DIAS (DEPENDENDO SE O ANO É BISSEXTO)
            if((m==1 && (d<=31 && d>0)) || (m==3 && (d<=31 && d>0)) || (m==4 && (d<=30 && d>0)) || (m==5 && (d<=31 && d>0)) || (m==6 && (d<=30 && d>0)) || (m==7 && (d<=31 && d>0)) || (m==8 && (d<=31 && d>0)) || (m==9 && (d<=30 && d>0)) || (m==10 && (d<=31 && d>0)) || (m==11 && (d<=30 && d>0)) || (m==12 && (d<=31 && d>0))){
                return 1;
            }else if((m == 2) && (d <= 28 && d > 0))//MES 2 TEM 28 DIAS EM QUALQUER ANO
            {
                return 1;
            }else if (d == 29 && m == 2 && (a % 400 == 0 || (a % 4 ==0 && a % 100 != 0)))//MES 2 TEM 29 DIAS SOMENTE SE O ANO FOR BISSEXTO, PARA SER BISSEXTO, O ANO TEM QUE TER RESTO 0 QUANDO DIVIDIDO POR 400 OU RESTO ENTRE ANO E 4 SER 0 E RESTO ENTRE ANO E 100 SER DIFERENTE DE 0
            {
                return 1;
            }else{
                return 0;
            }
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}
int verifica_cnpj (char *cnpj){//VERIFICA O CNPJ 
    int int_cnpj[TAM_MAX_CNPJ];
    int i,sum,digit_1,digit_2,rest_1,rest_2;
    sum = 0;

    char cnpj_us[TAM_MAX_CNPJ];

    //RETORNAR COMO INVALIDO CNPJ COM TODOS OS DIGITOS IGUAIS
    if (strcmp(cnpj,"00000000000000") == 0 || strcmp(cnpj,"11111111111111") == 0 || strcmp(cnpj,"22222222222222") == 0 || strcmp(cnpj,"33333333333333") == 0 || strcmp(cnpj,"44444444444444") == 0 || strcmp(cnpj,"55555555555555") == 0 || strcmp(cnpj,"66666666666666") == 0 || strcmp(cnpj,"77777777777777") == 0 || strcmp(cnpj,"88888888888888") == 0 || strcmp(cnpj,"99999999999999") == 0 )
    {
        return 0;
    }else{
        //CONVERTER UMA STRING PARA INTEIROS
        for (i = 0; i < 14; i++)
        {
            int_cnpj[i] = cnpj[i] - 48;
        }
        //VERIFICAR O PRIMEIRO DIGITO VERIFICADOR 
        for ( i = 0; i < 4; i++)
        {
            sum = sum + (int_cnpj[i]*(5-i));//SOMA DA MULTIPLICACAOO DE 5-i VEZES OS 4 PRIMEIROS DIGITOS DO CNPJ (i == POSICAO DE CADA DIGITO NO VETOR)
        }
        for ( i = 4; i < 12; i++)
        {
            sum = sum + (int_cnpj[i]*(13-i));//SOMA DA MULTIPLICACAO DE 13 - i VEZES OS DIGITOS 5,6,7,8,9,10,11,12 (i == POSICAO DE CADA DIGITO NO VETOR)
        }
        rest_1 = sum % 11; //CALCULO PARA ACHAR O PRIMEIRO DIGITO VERIFICADOR (DIGITO 13)
        //SE O RESTO DESSA DIVISAO FOR MENOR QUE 2, O DIGITO 13 DO CNPJ TEM QUE SER 0, CASO CONTRARIO, O DIGITO 13 SERA 11 MENOS ESSE RESTO
        if (rest_1 < 2)
        {
            digit_1 = 0;
        }else{
            digit_1 = 11 - rest_1;
        }
        sum = 0; //ZERAR A SOMA
        //VERIFICAR O SEGUNDO DIGITO VERIFICADOR
        for ( i = 0; i < 5; i++)
        {
            sum = sum + (int_cnpj[i]*(6-i));//SOMA DA MULTIPLICACAOO DE 6-i VEZES OS 5 PRIMEIROS DIGITOS DO CNPJ (i == POSICAO DE CADA DIGITO NO VETOR)
        }
        for ( i = 5; i < 13; i++)
        {
            sum = sum + (int_cnpj[i]*(14-i));//SOMA DA MULTIPLICACAO DE 14 - i VEZES OS DIGITOS 6,7,8,9,10,11,12,13 (i == POSICAO DE CADA DIGITO NO VETOR)
        }
        rest_2 = sum % 11;
        //SE O RESTO FOR MENOR QUE 2, O SEGUNDO DIGITO VERIFICADOR SERA 0, CASO NAO SEJA 0, O SEGUNDO DIGITO VERIFICADOR SERA 11 - RESTO
        if (rest_2 < 2)
        {
            digit_2 = 0;
        }else{
            digit_2 = 11 - rest_2;
        }
        //SE OS DIGITOS CALCULADOS FOREM IGAUIS AOS DIGITOS DIGITADOS, O CNPJ E VALIDO, CASO CONTRARIO E INVALIDO
        //RETURN 1 PARA VALIDO E 0 PARA INVALIDO
        if (digit_1 == int_cnpj[12] && digit_2 == int_cnpj[13])
        {
            return 1;
        }else{
            return 0;
        }
        
    }
}

void limpa_tela ()//LIMPAR TELA
{
    #if defined(linux) || defined(unix) || defined(APPLE)
        system ("clear");
    #endif
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}
void menu_opcoes (){
    printf("1 - Cadastrar Usina\n");
    printf("2 - Cadastrar Consumidor\n");
    printf("3 - Cadastrar Contrator entre Consumidor e Usina\n");
    printf("4 - Consultar Usina Cadastrada\n");
    printf("5 - Consultar Consumidor Cadastrado\n");
    printf("6 - Excluir Usina\n");
    printf("7 - Excluir Consumidor\n");
    printf("8 - Encerrar programa\n");
}
void cabecalho (){
    limpa_tela();
    printf("===========================================================\n");
    printf("----------------------USINAS SOLARES-----------------------\n");
    printf("===========================================================\n\n");
}

float potencia_restante (char *cnpj){//RETORNA A POTENCIA RESTANTE DE UMA USINA
    FILE *arquivo_usina;
    FILE *arquivo_contrato;
    CADASTRAR_USINA usina;
    CADASTRAR_CONTRATO contrato;
    float pot_gerada,pot_cont,pot_rest;
    pot_cont = 0;
    pot_gerada = 0;
    
    

    arquivo_usina = fopen("usinas.txt","rb");
    arquivo_contrato = fopen("contrato.txt","rb");

    if(arquivo_usina != NULL){
        fflush(stdin);
        while(fread(&usina,sizeof(CADASTRAR_USINA),1,arquivo_usina) == 1){
            if(strcmp(cnpj,usina.cnpj_us) == 0 ){
                pot_gerada = usina.pot_est; 
            }
        }
    }
    
    if(arquivo_contrato != NULL){
        fflush(stdin);
        while(fread(&contrato,sizeof(CADASTRAR_CONTRATO),1,arquivo_contrato) == 1){
            if(strcmp(cnpj,contrato.cnpj_con_us) == 0){
                pot_cont = pot_cont + contrato.pot_cont;
            }
        }
    }

    //POTENCIA GERADA MENOS A SOMA DAS POTENCIAS DOS CONTRATOS VINCULADOS A ESSA USINA
    pot_rest = pot_gerada - pot_cont;

    fclose(arquivo_contrato);
    fclose(arquivo_usina);
    return pot_rest;

}
float porcentagem_potencia(char *cnpj){//RETORNA A PORCENTAGEM DE POTENCIA RESTANTE DA USINA
    FILE *arquivo_usina;
    CADASTRAR_USINA usina;
    float pot_gerada,pot_rest,pot_porcentagem;

    arquivo_usina = fopen("usinas.txt","rb");
    if(arquivo_usina != NULL){
        fflush(stdin);
        while(fread(&usina,sizeof(CADASTRAR_USINA),1,arquivo_usina) == 1){
            if(strcmp(cnpj,usina.cnpj_us) == 0 ){
                pot_gerada = usina.pot_est;
            }
        }
    }
    pot_rest = potencia_restante(cnpj);
    pot_porcentagem = (pot_rest/pot_gerada)*100;
    fclose(arquivo_usina);
    return pot_porcentagem;
}

void cadastrar_usina(){
    int aux,aux_data,aux2;
    CADASTRAR_USINA usina;
    FILE *arquivo;

    arquivo = fopen("usinas.txt","ab");//abrir o arquivo txt e poder editar ele
    

    //SE NAO FOR POSSIVEL ABRIR O ARQUIVO,ELE DA O PRINTF
    if(arquivo == NULL){
        printf("Problemas na abertura do arquivo !\n");
    }else{
        do//LOPPINGA PARA SE A PESSOA QUISER CADASTRAR MAIS DE UMA USINA SEM TER QUE VOLTAR AO MENU, ELA CONSEGUE
        {
            cabecalho();
            fflush(stdin);//LIMPAR A MEMORIA DO TECLADO

            rewind(arquivo);//COLOCA O PONTEIRO DO ARQUIVO NA PRIMEIRA LINHA
            
            fflush(stdin);
            printf("Digite o CNPJ da usina (formato : XXXXXXXXXXXXXX):\n");
            scanf("%s",&usina.cnpj_us);
            //fflush(stdin);
            //LOPPING PARA VERIFICAR CNPJ

            aux2 = arquivo_cnpj(usina.cnpj_us);
            aux = arquivo_iden_cnpj(usina.cnpj_us);

            if( aux == 0 || strlen(usina.cnpj_us) != 14 || aux2 == 0 ) //SE ALGUM DOS VERIFICADORES FOREM INVALIDOS ELE ENTRA NESSA CONDICAO
            {
                while ( aux == 0 || strlen(usina.cnpj_us) != 14 || aux2 == 0 )//VAI LER ENQUANTO O CNPJ FOR INVALIDO, ATE UM VALIDO SER DIGITADO
                {
                    printf("CNPJ invalido! Digite um CNPJ valido (formato : XXXXXXXXXXXXXX):\n");
                    scanf("%s",&usina.cnpj_us);

                    aux2 = arquivo_cnpj(usina.cnpj_us);
                    aux = arquivo_iden_cnpj(usina.cnpj_us);
                    
                }
            }
            getchar();
            printf("Digite o nome da usina :\n");
            scanf("%[^\n]s", usina.nome_us);

            //RECEBER O NOME DA USINA
            getchar();
            fflush(stdin);

            //RECEBER A DATA DA USINA
            printf("Digite a data de inicio da operacao (Formato : XXXXXXXX) :\n");
            scanf("%s",usina.data_us);
            aux_data = verifica_data(usina.data_us);
            //LOPPING PARA VERIFICAR DATA
            if(aux_data == 0 || strlen(usina.data_us) != 8){//VERIFICACAO POR MEIO DA FUNCAO E POR MEIO DO TAMANHO DO VETOR, SE FOR DIFERENTE DE 8 JA E CONSIDERADO INVALIDO
                while (aux_data == 0 || strlen(usina.data_us) != 8)//VAI LER A DATA ENQUANTO ELA FOR INVALIDA, SO VAI GUARDAR NO ARQUIVO QUANDO FOR VALIDA
                {
                printf("Data invalida! Digite uma data valida (Formato : XXXXXXXX) :\n");
                scanf("%s", &usina.data_us);
                aux_data = verifica_data(usina.data_us);
                }
            }
            fflush(stdin);
            //RECEBER A POTENCIA
            printf("Digite a potencia estimada da usina (MW):\n");
            scanf("%f",&usina.pot_est);
            if(usina.pot_est <= 0)//SE A POTENCIA FOR MENOR QUE 0, CONSIDERAR COMO INVALIDA
            {
                while(usina.pot_est <= 0)//LER ENQUANTO FOR DIGITADA UMA POTENCIA INVALIDA, SO VAI SAIR DO LOOPING QUANDO FOR DIGITADO UMA POTENCIA VALIDA
                {
                    printf("Potencia estimada invalida! Digite uma potencia valida :\n");
                    scanf("%f",&usina.pot_est);
                }
            }

            //fwrite(&usina,sizeof(CADASTRAR_USINA),1, arquivo);//APOS TODAS AS VERIFICACOES, VAI GUARDAR NO ARQUIVO TXT
            fwrite(&usina,sizeof(CADASTRAR_USINA),1,arquivo);//FAZ UMA QUEBRA DE LINHA DENTRO DO ARQUIVO
            printf("Usina cadastrada com sucesso !\n");
            printf("Deseja cadastrar novamente ? (S/N)\n");

        }while(getche() == 's' || getche() == 'S');
        fclose(arquivo);//FECHAR O ARQUIVO QUE ESTAVA ABERTO
        
    }
    fclose(arquivo);//FECHAR O ARQUIVO QUE ESTAVA ABERTO

}
void cadastrar_consumidor (){

    CADASTRAR_CONSUMIDOR consumidor;
    FILE* arquivo;
    int aux,aux1,aux2;
    arquivo = fopen("consumidor.txt","ab");
    
    if(arquivo == NULL ){
        printf("Problemas na abertura do arquivo !\n");
    }else{
        do{
            
            cabecalho();
           
            rewind(arquivo);//COLOCA O PONTEIRO DO ARQUIVO PARA O INICIO
            fflush(stdin);//LIMPA A MEMORIA DO TECLADO
            printf("Digite a sua identificacao (CPF // CNPJ) (digitar somente os numeros):\n");
            scanf("%s",&consumidor.iden_con);
            
           if(strlen(consumidor.iden_con) == 11){
                aux = arquivo_cpf_consumidor(consumidor.iden_con);
            }else{
                if(strlen(consumidor.iden_con) == 14){
                    aux1 = arquivo_cnpj(consumidor.iden_con);
                    aux2 = arquivo_iden_cnpj(consumidor.iden_con);
                }else{
                    aux = arquivo_cpf_consumidor(consumidor.iden_con);
                    aux1 = arquivo_cnpj(consumidor.iden_con);
                    aux2 = arquivo_iden_cnpj(consumidor.iden_con);
                }
            }
          
            while (aux == 0 || aux1 == 0 || aux2 == 0)//ENQUANTO OS VERIFICADORES RETORNAREM 0,VAI LER UMA NOVA IDENTIFICACAO E TESTA-LAS NOVAMENTE, DA MESMA MANEIRA QUE FOI FEITO ANTERIORMENTE
            {   

                printf("CNPJ/CPF invalido! Digite o CNPJ/CPF novamente (formato sem hifens,pontos ou barras):\n");
                scanf("%s",&consumidor.iden_con);

                    if(strlen(consumidor.iden_con) == 11)
                {
                       aux = arquivo_cpf_consumidor(consumidor.iden_con);
                }else{
                    if (strlen(consumidor.iden_con)==14)
                    {
                        aux1 = arquivo_cnpj(consumidor.iden_con);
                        aux2 = arquivo_iden_cnpj(consumidor.iden_con);
                    }else{
                        aux = 0;
                        aux1 = 0;
                        aux2 = 0;
                    }
                }
                if(aux == 1){
                    aux1 = 1;
                    aux2 = 1;
                }
                if(aux1 == 1 && aux2 == 1){
                    aux = 1;
                }
            }

            getchar();
            
            //LER O NOME
            printf("Digite o seu nome :\n");
            gets(&consumidor.nome_con);
            //GUARDA OS DADOS DO CONSUMIDOR
            fwrite(&consumidor,sizeof(CADASTRAR_CONSUMIDOR),1, arquivo);
            
            printf("Deseja cadastrar novamente ? (S/N)\n");

        }while(getche() == 's' || getche() == 'S');
        fclose(arquivo);
    }
    fclose(arquivo);
}
void cadastrar_contrato(){
    CADASTRAR_CONTRATO contrato;
    FILE *arquivo;
    int aux_data,aux_data2,aux,aux1;
    
    arquivo = fopen("contrato.txt","ab");
    if(arquivo == NULL){
        printf("Problemas na abertura dos arquvivo !\n");
    }else{
        do{
          
            cabecalho();
            rewind(arquivo);//COLOCAR O PONTEIRO DO ARQUIVO NO INICIO
            fflush(stdin);//LIMPAR A MEMORIA DO TECLADO
            //LER O CNPJ DA USINA
            printf("Digite o CNPJ da usina (formato sem hifens,pontos ou barras):\n");
            scanf("%s",&contrato.cnpj_con_us);

            verifica_cnpj(contrato.cnpj_con_us);
            arquivo_cnpj_usina_contrato(contrato.cnpj_con_us);
            //VERIFICAR O CNPJ DA USINA
            if( verifica_cnpj(contrato.cnpj_con_us) == 0 || strlen(contrato.cnpj_con_us) != 14 || arquivo_cnpj_usina_contrato(contrato.cnpj_con_us) == 1) 
            {
                while ( verifica_cnpj(contrato.cnpj_con_us) == 0 || strlen(contrato.cnpj_con_us) != 14 || arquivo_cnpj_usina_contrato(contrato.cnpj_con_us) == 1)
                {
                    printf("CNPJ invalido! Digite um CNPJ valido (formato sem hifens,pontos ou barras):\n");
                    scanf("%s",&contrato.cnpj_con_us);
                    verifica_cnpj(contrato.cnpj_con_us);
                    arquivo_cnpj_usina_contrato(contrato.cnpj_con_us);
                }
            }
            fflush(stdin);
            
            //LER O IDENTIFICADOR DO CONSUMIDOR
            printf("Digite o CPF/CNPJ do consumidor (formato sem hifens,pontos ou barras):\n");
            scanf("%s",&contrato.iden_contr_consu);
            //VERIFICA O IDENTIFICADOR
            if(strlen(contrato.iden_contr_consu) == 11){
                aux = arquivo_cpf_contrato(contrato.iden_contr_consu);
            }else{
                if(strlen(contrato.iden_contr_consu) == 14){
                    aux1 = arquivo_cnpj_contrato(contrato.iden_contr_consu);
                }else{
                    aux = arquivo_cpf_contrato(contrato.iden_contr_consu);
                    aux1 = arquivo_cnpj_contrato(contrato.iden_contr_consu);
                }
            }
            while (aux == 0 || aux1 == 0 )//ENQUANTO OS VERIFICADORES RETORNAREM 0,VAI LER UMA NOVA IDENTIFICACAO E TESTA-LAS NOVAMENTE, DA MESMA MANEIRA QUE FOI FEITO ANTERIORMENTE
            {   
                printf("CNPJ/CPF invalido! Digite o CNPJ/CPF novamente (formato sem hifens,pontos ou barras):\n");
                scanf("%s",&contrato.iden_contr_consu);

                    if(strlen(contrato.iden_contr_consu) == 11)
                {
                       aux = arquivo_cpf_contrato(contrato.iden_contr_consu);
                }else{
                    if (strlen(contrato.iden_contr_consu)==14)
                    {
                        aux1 = arquivo_cnpj_contrato(contrato.iden_contr_consu);
                    }else{
                        aux = 0;
                        aux1 = 0;
                    }
                }
                if(aux == 1){
                    aux1 = 1;
                }
                if(aux1 == 1){
                    aux = 1;
                }
            }
            

            //LER A DATA DE INICIO DO CONTRATO
            printf("Digite a data de inicio do contrato (formato sem barras):\n");
            scanf("%s",&contrato.data_con);
            aux_data = verifica_data(contrato.data_con);
            aux_data2 = contrato_data(contrato.data_con,contrato.cnpj_con_us);
            //LOPPING PARA VERIFICAR DATA
            if(aux_data == 0 || strlen(contrato.data_con) != 8 || aux_data2 == 0){//VERIFICACAO POR MEIO DA FUNCAO E POR MEIO DO TAMANHO DO VETOR, SE FOR DIFERENTE DE 8 JA E CONSIDERADO INVALIDO
                while (aux_data == 0 || strlen(contrato.data_con) != 8 || aux_data2 == 0)//VAI LER A DATA ENQUANTO ELA FOR INVALIDA, SO VAI GUARDAR NO ARQUIVO QUANDO FOR VALIDA
                {
                if(aux_data2 == 0){
                    printf("Essa usina ainda nao esta em operacao !\n");
                }
                printf("Data invalida! Digite uma data valida (formato sem barras):\n");
                scanf("%s", &contrato.data_con);
                aux_data = verifica_data(contrato.data_con);
                aux_data2 = contrato_data(contrato.data_con,contrato.cnpj_con_us);
                }
            }
            //LER A POTENCIA CONTRATADA
            printf("Digite a potencia contratada (MW):\n");
            scanf("%f",&contrato.pot_cont);

            if(contrato.pot_cont <= 0 || contrato.pot_cont > potencia_restante(contrato.cnpj_con_us))//SE A POTENCIA FOR MENOR QUE 0, CONSIDERAR COMO INVALIDA
            {
                while(contrato.pot_cont <= 0 || contrato.pot_cont > potencia_restante(contrato.cnpj_con_us))//LER ENQUANTO FOR DIGITADA UMA POTENCIA INVALIDA, SO VAI SAIR DO LOOPING QUANDO FOR DIGITADO UMA POTENCIA VALIDA
                {
                    if(contrato.pot_cont > potencia_restante(contrato.cnpj_con_us)){
                        printf("Potencia indisponivel no momento !\nPotencia restante na usina : %.2f MW\n",potencia_restante(contrato.cnpj_con_us));
                    }
                    printf("Potencia estimada invalida! Digite uma potencia valida (MW):\n");
                    scanf("%f",&contrato.pot_cont);
                }
            }
            //ESCREVER NO ARQUIVO OS DADOS DO STRUCT DO CONTRATO
            fwrite(&contrato,sizeof(CADASTRAR_CONTRATO),1,arquivo);

            printf("Deseja cadastrar mais contratros ? (S/N) \n");
        }while(getche() == 's' || getche() == 'S');      
        fclose(arquivo);//FECHAR O ARQUIVO
    }
    fclose(arquivo);
}
void consultar_usina(){
    char cnpj[TAM_MAX_CNPJ];
    
    printf("Digite o CNPJ da usina que deseja consultar (formato sem hifens,pontos ou barras):\n");
    scanf("%s", cnpj);
    cabecalho();
    //VERIFICA SE O CNPJ DIGITADO ESTA NO ARQUIVO DE USINAS
    if(arquivo_cnpj(cnpj) == 1){
        //VAI LER NOVAMENTE ATE QUE SEJA DIGITADO UM CNPJ QUE TENHA NO ARQUIVO DE USINAS
        while(arquivo_cnpj(cnpj) == 1){
            printf("Essa usina nao esta cadastrada !\n");
            printf("Digite o CNPJ novamente :\n");
            scanf("%s",cnpj);
            arquivo_cnpj(cnpj);
        }
    }
    cabecalho();
    consultar_usina_arquivo(cnpj);
    
}
void consultar_consumidor(){
    char iden[TAM_MAX_CNPJ];
    int aux1,aux;

    printf("Digite o CPF/CNPJ do consumidor (formato sem hifens,pontos ou barras):\n");
    scanf("%s", iden);
    cabecalho();
    //VERIFICAR SE O IDENTIFICADOR DO CONSUMIDOR ESTA NO ARQUIVO DE CONSUMIDORES
    if(strlen(iden) == 11){
                aux = arquivo_cpf_contrato(iden);//VERFIFICA SE O CPF DIGITADO ESTA NO ARQUIVO DE CONSUMIDORES
            }else{
                if(strlen(iden) == 14){//VERFIFICA SE CNPJ DIGITADO ESTA NO ARQUIVO DE CONSUMIDORES
                    aux1 = arquivo_cnpj_contrato(iden);
                }else{
                    aux = arquivo_cpf_contrato(iden);
                    aux1 = arquivo_cnpj_contrato(iden);
                }
            }
            while (aux == 0 || aux1 == 0 )//ENQUANTO OS VERIFICADORES RETORNAREM 0,VAI LER UMA NOVA IDENTIFICACAO E TESTA-LAS NOVAMENTE, DA MESMA MANEIRA QUE FOI FEITO ANTERIORMENTE
            {   
                printf("CNPJ/CPF invalido! Digite o CNPJ/CPF novamente (formato sem hifens,pontos ou barras):\n");
                scanf("%s",&iden);

                    if(strlen(iden) == 11)
                {
                       aux = arquivo_cpf_contrato(iden);
                }else{
                    if (strlen(iden)==14)
                    {
                        aux1 = arquivo_cnpj_contrato(iden);
                    }else{
                        aux = 0;
                        aux1 = 0;
                    }
                }
                if(aux == 1){
                    aux1 = 1;
                }
                if(aux1 == 1){
                    aux = 1;
                }
            }
    cabecalho();
    consultar_consumidor_arquivo(iden);
}
void excluir_usina(){
    char cnpj[TAM_MAX_CNPJ];
    do{
        printf("Digite o CNPJ da usina que deseja excluir (formato sem hifens,pontos ou barras) :\n");
        scanf("%s", cnpj);
        cabecalho();
        //VERIFICA SE O CNPJ DIGITADO ESTA NO ARQUIVO DE USINAS
        if(arquivo_cnpj_usina_contrato(cnpj) == 1){
            //VAI LER NOVAMENTE ATE QUE SEJA DIGITADO UM CNPJ QUE TENHA NO ARQUIVO DE USINAS
            while(arquivo_cnpj_usina_contrato(cnpj) == 1){
                printf("Essa usina nao esta cadastrada !\n");
                printf("Digite o CNPJ novamente (formato sem hifens,pontos ou barras) :\n");
                scanf("%s",cnpj);
                arquivo_cnpj_usina_contrato(cnpj);
            }
        }
        apagar_usina(cnpj);

        printf("Deseja excluir mais usinas ? (S/N) \n");
    } while (getche() == 's' || getche() == 'S');
}
void excluir_consumidor(){
    char iden[TAM_MAX_CNPJ];
    int aux1,aux;

    do{
        printf("Digite o CPF/CNPJ do consumidor (formato sem hifens,pontos ou barras):\n");
        scanf("%s", iden);
        cabecalho();
        //VERIFICAR SE O IDENTIFICADOR DO CONSUMIDOR ESTA NO ARQUIVO DE CONSUMIDORES
        if(strlen(iden) == 11){
                    aux = arquivo_cpf_contrato(iden);//VERFIFICA SE O CPF DIGITADO ESTA NO ARQUIVO DE CONSUMIDORES
                }else{
                    if(strlen(iden) == 14){//VERFIFICA SE CNPJ DIGITADO ESTA NO ARQUIVO DE CONSUMIDORES
                        aux1 = arquivo_cnpj_contrato(iden);
                    }else{
                        aux = arquivo_cpf_contrato(iden);
                        aux1 = arquivo_cnpj_contrato(iden);
                    }
                }
                while (aux == 0 || aux1 == 0 )//ENQUANTO OS VERIFICADORES RETORNAREM 0,VAI LER UMA NOVA IDENTIFICACAO E TESTA-LAS NOVAMENTE, DA MESMA MANEIRA QUE FOI FEITO ANTERIORMENTE
                {   
                    printf("Digite o CNPJ/CPF novamente (formato sem hifens,pontos ou barras):\n");
                    scanf("%s",&iden);

                        if(strlen(iden) == 11)
                    {
                        aux = arquivo_cpf_contrato(iden);
                    }else{
                        if (strlen(iden)==14)
                        {
                            aux1 = arquivo_cnpj_contrato(iden);
                        }else{
                            aux = 0;
                            aux1 = 0;
                        }
                    }
                    if(aux == 1){
                        aux1 = 1;
                    }
                    if(aux1 == 1){
                        aux = 1;
                    }
                }
                apagar_consumidor(iden);
        printf("Deseja excluir mais usinas ? (S/N) \n");
    } while (getche() == 's' || getche() == 'S');
    
}

void consultar_consumidor_arquivo(char *iden){//PEGA O IDENTIFICADOR DIGITADO, VERIFICA SE TEM NO ARQUIVO, SE TIVER, RETORNA OS DADOS DO CONSUMIDOR E OS DADOS DAS USINAS NAS QUAIS ESSE CONSUMIDOR TEM CONTRATO
    FILE *arquivo;
    FILE *arquivo_contrato;
    CADASTRAR_CONSUMIDOR consumidor;
    CADASTRAR_CONTRATO contrato;
    char cnpj_us[TAM_MAX_CNPJ];
    
    //IMPRIME OS DADOS DO CONSUMIDOR QUE FOI FEITA A BUSCA
    arquivo = fopen("consumidor.txt","rb");
    if(arquivo != NULL){
        while (!feof(arquivo))
        {
            fread(&consumidor,sizeof(CADASTRAR_CONSUMIDOR),1,arquivo);
            if(strcmp(iden,consumidor.iden_con) == 0){
                printf("CPF/CNPJ : %s\nNome : %s\n",consumidor.iden_con,consumidor.nome_con);
                printf("-----------------------------------------------------------\n");
                printf("Usinas :\n\n");
                fclose(arquivo);
                break;
            }
        }
        
    }
    //PEGA O IDENTIFICADOR DO CONSUMIDOR, VERFICA NOS CONTRATOS, PEGA OS CNPJS DAS USINAS NAS QUAIS TEM CONTRATO E IMPRIME OS DADOS DELAS
    arquivo_contrato = fopen("contrato.txt","rb");
    if(arquivo_contrato != NULL){
        while(fread(&contrato,sizeof(CADASTRAR_CONTRATO),1,arquivo_contrato) == 1){
            if(strcmp(iden,contrato.iden_contr_consu) == 0){
                strcpy(cnpj_us,contrato.cnpj_con_us);
                consultar_consumidor_usina(cnpj_us);//IMPRIME OS DADOS DAS USINAS ATRAVES DO CNPJ DELAS
            }
        }
        fclose(arquivo_contrato);
    }
    system("pause");
    fclose(arquivo_contrato);
}
void consultar_consumidor_usina(char *cnpj){//IMPRIME OS DADOS DE UMA USINA A PARTIR DO CNPJ DELAS
    FILE * arquivo;
    CADASTRAR_USINA usina;

    arquivo = fopen("usinas.txt","rb");
    
    if(arquivo != NULL){
        while(fread(&usina,sizeof(CADASTRAR_USINA),1,arquivo) == 1 ){
            if(strcmp(cnpj,usina.cnpj_us) == 0 ){
                printf("CNPJ: %s\nNome: %s\nData de inicio das operacoes: %s\nPotencia estimada: %.2f MW\n",usina.cnpj_us,usina.nome_us,usina.data_us,usina.pot_est);
                printf("-----------------------------------------------------------\n");
            }
        }
        fclose(arquivo);
    }
    
}
int contrato_data(char *data, char *cnpj){//VERIFICA SE A DATA DO CONTRATO E ANTES DA DATA DE INICIO DA USINA, SE FOR, RETORNA 0
    FILE *arquivo;
    CADASTRAR_USINA usina;
    int int_data[TAM_MAX_DATA];
    int int_data_us[TAM_MAX_DATA];
    int A_arq,A,M_arq,M,D_arq,D,i;
    char data_usina[TAM_MAX_DATA];

    for ( i = 0; i < 8; i++)
    {
        int_data[i] = data[i] - 48;
    }
    //TRANSFORMAR DOIS INTEIROS SEPARADOS EM INTEIROS JUNTOS TIPO 2,3 VAI VIRAR 23
    D = int_data[0]*10 + int_data[1];
    M = int_data[2]*10 + int_data[3];
    A = int_data[4]*1000 + int_data[5]*100 + int_data[6]*10 + int_data[7];
    
    arquivo = fopen("usinas.txt","rb");
    
    if(arquivo != NULL){
        while(fread(&usina,sizeof(CADASTRAR_USINA),1,arquivo) == 1){//PERCORRE O ARQUIVO ATE O FINAL
            if(strcmp(cnpj,usina.cnpj_us) == 0 ){//SE O CNPJ DIGITADO FOR IGUAL AO DO ARQUIVO RETORNA 0
            strcpy(data_usina,usina.data_us);
            fclose(arquivo);
            break;
        }
    }
    for ( i = 0; i < 8; i++)
    {
        int_data_us[i] = data_usina[i] - 48;
    }
    D_arq = int_data_us[0]*10 + int_data_us[1];
    M_arq = int_data_us[2]*10 + int_data_us[3];
    A_arq = int_data_us[4]*1000 + int_data_us[5]*100 + int_data_us[6]*10 + int_data_us[7];

    if(A < A_arq){
        return 0;
    }else{
        if(A == A_arq && M < M_arq){
            return 0;
        }else{
            if(A == A_arq && M == M_arq && D < D_arq){
                return 0;
            }else{
                return 1;
            }
        }
    }
  }
}
int arquivo_cnpj(char *cnpj){//VERIFICA SE O CNPJ DA USINA JA ESTA CADASTRADO SE TIVER RETORNA 0
    FILE *arquivo;
    CADASTRAR_USINA usina;

    char cnpj_us[TAM_MAX_CNPJ];
  

    arquivo = fopen("usinas.txt","rb");
    
    if(arquivo != NULL){
        while(fread(&usina,sizeof(CADASTRAR_USINA),1,arquivo) == 1){//PERCORRE O ARQUIVO ATE O FINAL
            if(strcmp(cnpj,usina.cnpj_us) == 0 ){//SE O CNPJ DIGITADO FOR IGUAL AO DO ARQUIVO RETORNA 0
                printf("Ja existe uma usina cadastrada com esse CNPJ !\n");
                fclose(arquivo);
                return 0;
                break;
            }
        }
    }
    fclose(arquivo);
    return 1;
}
int arquivo_cnpj_usina_contrato(char *cnpj){//VERIFICA SE O CNPJ DA USINA JA ESTA CADASTRADO SE TIVER RETORNA 0
    FILE *arquivo;
    CADASTRAR_USINA usina;

    char cnpj_us[TAM_MAX_CNPJ];
  

    arquivo = fopen("usinas.txt","rb");
    
    if(arquivo != NULL){
        while(fread(&usina,sizeof(CADASTRAR_USINA),1,arquivo) == 1){//PERCORRE O ARQUIVO ATE O FINAL
            if(strcmp(cnpj,usina.cnpj_us) == 0 ){//SE O CNPJ DIGITADO FOR IGUAL AO DO ARQUIVO RETORNA 0
                fclose(arquivo);
                return 0;
                break;
            }
        }
    }
    printf("Essa usina nao esta cadastrada !\n");
    fclose(arquivo);
    return 1;
}
int arquivo_cpf_consumidor(char *cpf){//VERIFICA SE O CPF JA ESTA CADASTRADO NO ARQUIVO, SE TIVER, RETORNA 0
    FILE *arquivo;
    CADASTRAR_CONSUMIDOR consumidor;
  if(verifica_cpf(cpf) == 0){//VERIFICA SE O CPF E VALIDO
        printf("CPF invalido !\n");
        return 0;
    }else{
    arquivo = fopen("consumidor.txt","rb");
    //ABRE O ARQUIVO E VE SE JA TEM UM CPF IGUAL CADASTRADO
    if(arquivo != NULL){
        while(!feof(arquivo)){
            fread(&consumidor,sizeof(CADASTRAR_CONSUMIDOR),1,arquivo);
            if(strcmp(cpf,consumidor.iden_con) == 0 ){

                fclose(arquivo);
                printf("CPF ja esta no banco de dados !\n");
                return 0;
                break;
            }
        }
    }
    fclose(arquivo);
    return 1;
    }
}
int arquivo_iden_cnpj(char *cnpj){//VERIFICA SE JA EXISTE UM CNPJ DE CONSUMIDOR CADASTRADO, SE TIVER, RETORNA 0
    FILE *arquivo;
    CADASTRAR_CONSUMIDOR consumidor;
    if(verifica_cnpj(cnpj) == 0){//VERIFICA SE O CNPJ E VALIDO
        printf("CNPJ invalido !\n");
        return 0;
    }else{
        arquivo = fopen("consumidor.txt","rb");
        //OLHA NO ARQUIVO SE JA EXISTE UM MESMO CNPJ DENTRO DO ARQUIVO
        if(arquivo != NULL){
        while(!feof(arquivo)){
            fread(&consumidor,sizeof(CADASTRAR_CONSUMIDOR),1,arquivo);
            if(strcmp(cnpj,consumidor.iden_con) == 0 ){
                printf("Ja existe um consumidor cadastrado com esse CNPJ !\n");
                fclose(arquivo);
                return 0;
                break;
            }
        }
        }
    }
    fclose(arquivo);
    return 1;
}
void consultar_usina_arquivo(char *cnpj){//PEGA O CNPJ DIGITADO, VERIFICA SE TEM NO ARQUIVO, SE TIVER, RETORNA OS DADOS DA USINA E OS CONSUMIDORES QUE TEM CONTRATO COM ESSA USINA
    FILE *arquivo;
    FILE *arquivo_contrato;
    CADASTRAR_USINA usina;
    CADASTRAR_CONTRATO contrato;
    char iden_consumidor[TAM_MAX_CNPJ];

    arquivo = fopen("usinas.txt","rb");
    //IMPRIME OS DADOS DA USINA QUE FOI FEITA A BUSCA
    if(arquivo != NULL){
        rewind(arquivo);
        while(!feof(arquivo)){
            fread(&usina,sizeof(CADASTRAR_USINA),1,arquivo);
            fflush(stdin);
            if(strncmp(cnpj,usina.cnpj_us,14) == 0 ){
                printf("CNPJ usina : %s\nNome Usina :%s\nData de inicio da operacao: %s\nPotencia Gerada : %.2f MW\n",usina.cnpj_us,usina.nome_us,usina.data_us,usina.pot_est);
                printf("Percentual de potencia restante da usina : %.2f %%\n",porcentagem_potencia(cnpj));
                printf("Potencia restante : %.2f MW\n",potencia_restante(cnpj));
                printf("-----------------------------------------------------------\n");
                printf("Consumidores :\n\n");
                fclose(arquivo);
                break;
            }
            
        }
    }
    //PEGA O CNPJ DA USINA, VERFICA NOS CONTRATOS, PEGA AS IDENTIFICACOES DOS CONSUMIDORES QUE TEM CONTRATO E IMPRIME OS DADOS DELES
    arquivo_contrato = fopen("contrato.txt","rb");
    if(arquivo_contrato != NULL){
        while(fread(&contrato,sizeof(CADASTRAR_CONTRATO),1,arquivo_contrato) == 1){
            if(strcmp(cnpj,contrato.cnpj_con_us) == 0){
                strcpy(iden_consumidor,contrato.iden_contr_consu);
                consultar_usina_consumidores(iden_consumidor);//PEGA OS DADOS DOS CONSUMIDORES A PARTIR DA IDENTIFICACAO DELES
                printf("Data de inicio do contrato : %s\nPotencia contratada : %.2f MW\n",contrato.data_con,contrato.pot_cont);
                printf("-----------------------------------------------------------\n");
            }
        }
        fclose(arquivo_contrato);
    }
    system("pause");
    fclose(arquivo_contrato);
}
int arquivo_cpf_contrato(char *cpf){//VERIFICA SE TEM UM CLIENTE COM ESSE CPF JA CADASTRADO, RETORNA 1 SE TIVER, JA QUE E NECESSARIO JA ESTAR CADASTRADO PARA FAZER O CONTRATO
    FILE *arquivo;
    CADASTRAR_CONSUMIDOR consumidor;
    if(verifica_cpf(cpf) == 0){//VERIFICA SE O CPF E VALIDO
        printf("CPF invalido !");
        return 0;
    }else{
        arquivo = fopen("consumidor.txt","rb");
    
    if(arquivo != NULL){
        while(!feof(arquivo)){
            fread(&consumidor,sizeof(CADASTRAR_CONSUMIDOR),1,arquivo);
            if(strcmp(cpf,consumidor.iden_con) == 0 ){

                fclose(arquivo);
                return 1;
                break;
            }
        }
    }
    printf("CPF nao econtrado no banco de dados!\n");
    fclose(arquivo);
    return 0;
    }
}
int arquivo_cnpj_contrato(char *cnpj){//VERIFICA SE TEM UM CLIENTE COM ESSE CNPJ JA CADASTRADO, RETORNA 1 SE TIVER, JA QUE E NECESSARIO JA ESTAR CADASTRADO PARA FAZER O CONTRATO
    FILE *arquivo;
    CADASTRAR_CONSUMIDOR consumidor;
    if(verifica_cnpj(cnpj) == 0){//VERIFIFCA SE O CNPJ E VALIDO
        return 0;
    }else{
        arquivo = fopen("consumidor.txt","rb");

    if(arquivo != NULL){
        while(!feof(arquivo)){
            fread(&consumidor,sizeof(CADASTRAR_CONSUMIDOR),1,arquivo);
            if(strcmp(cnpj,consumidor.iden_con) == 0 ){
                
                fclose(arquivo);
                return 1;
                break;
            }
        }
    }
    printf("CNPJ nao econtrado no banco de dados!\n");
    fclose(arquivo);
    return 0;   
    }
}
void consultar_usina_consumidores(char *iden){//RECEBE UMA IDENTIFICACAO DO CONSUMIDOR E RETORNA OS DADOS DELE
    FILE * arquivo_consumidor;

    CADASTRAR_CONSUMIDOR consumidor;

    arquivo_consumidor = fopen("consumidor.txt","rb");

    if(arquivo_consumidor != NULL){
        while(fread(&consumidor,sizeof(CADASTRAR_CONSUMIDOR),1,arquivo_consumidor) == 1 ){
            if(strcmp(iden,consumidor.iden_con) == 0 ){
                printf("Nome : %s\nCPF/CNPJ : %s\n",consumidor.nome_con,consumidor.iden_con);
            }
        }
        fclose(arquivo_consumidor);
    }
    
}


void apagar_usina(char *cnpj){//APAGA AS USINAS

    FILE* arquivo_temporario;
    FILE* arquivo;
    CADASTRAR_USINA usina;
    //ABRE OS ARQUIVOS
    arquivo = fopen("usinas.txt","rb");
    arquivo_temporario = fopen("usinas_temporario.txt","ab");
    if(arquivo != NULL || arquivo_temporario != NULL){
        //VAI LER LINHA POR LINHA
        while (fread(&usina,sizeof(CADASTRAR_USINA),1,arquivo) == 1){
            //O QUE FOR DIFERENTE DO CNPJ DIGITADO VAI SER GUARDADO EM UM ARQUIVO TEMPORARIO
            if (strcmp(cnpj,usina.cnpj_us) != 0 ){

                fwrite(&usina,sizeof(CADASTRAR_USINA),1,arquivo_temporario);

            }
            
        }
        
    }
    apagar_contratos_usina(cnpj);//APAGA OS CONTRATOS RELACIONADOS A USINA QUE SERA EXCLUIDA

    fclose(arquivo);
    fclose(arquivo_temporario);
    //APAGA O ARQUIVO
    remove("usinas.txt");
    //PEGA O TEMPORARIO E RENOMEIA ELE PARA O ARQUIVO ANTIGO
    rename("usinas_temporario.txt", "usinas.txt");
    
    printf("Usina excluida com sucesso !\n");
}
void apagar_contratos_usina(char *cnpj){ //APAGA OS CONTRATOS RELACIONADOS A USINA QUE SERA EXCLUIDA
    FILE* arquivo;
    FILE* arquivo_temporario;
    CADASTRAR_CONTRATO contrato;

    arquivo = fopen("contrato.txt","rb");
    arquivo_temporario = fopen("contrato_temporario.txt","ab");

    if(arquivo != NULL || arquivo_temporario != NULL){
        //VAI LER LINHA POR LINHA
        while(fread(&contrato,sizeof(CADASTRAR_CONTRATO),1,arquivo) == 1){
            //O QUE FOR DIFERENTE DO CNPJ DIGITADO VAI SER GUARDADO EM UM ARQUIVO TEMPORARIO
            if (strcmp(cnpj,contrato.cnpj_con_us) != 0){
                fwrite(&contrato,sizeof(CADASTRAR_CONTRATO),1,arquivo_temporario);
            }
            
        }
    }

    fclose(arquivo);
    fclose(arquivo_temporario);
    //APAGA O ARQUIVO
    remove("contrato.txt");
    //PEGA O TEMPORARIO E RENOMEIA ELE PARA O ARQUIVO ANTIGO
    rename("contrato_temporario.txt", "contrato.txt");
}

void apagar_consumidor(char *iden){//APAGA O CONSUMIDOR DIGITADO
    
    FILE* arquivo_temporario;
    FILE* arquivo;
    CADASTRAR_CONSUMIDOR consumidor;
    //ABRE OS ARQUIVOS
    arquivo = fopen("consumidor.txt","rb");
    arquivo_temporario = fopen("consumidor_temporario.txt","ab");
    if(arquivo != NULL || arquivo_temporario != NULL){
        //VAI LER LINHA POR LINHA
        while (fread(&consumidor,sizeof(CADASTRAR_CONSUMIDOR),1,arquivo) == 1){
            //O QUE FOR DIFERENTE DO CNPJ DIGITADO VAI SER GUARDADO EM UM ARQUIVO TEMPORARIO
            if (strcmp(iden,consumidor.iden_con) != 0 ){

                fwrite(&consumidor,sizeof(CADASTRAR_CONSUMIDOR),1,arquivo_temporario);

            }
            
        }
        
    }
    apagar_contratos_consumidor(iden);//APAGA OS CONTRATOS RELACIONADOS A USINA QUE SERA EXCLUIDA

    fclose(arquivo);
    fclose(arquivo_temporario);
    //APAGA O ARQUIVO
    remove("consumidor.txt");
    //PEGA O TEMPORARIO E RENOMEIA ELE PARA O ARQUIVO ANTIGO
    rename("consumidor_temporario.txt", "consumidor.txt");
    
    printf("Consumidor excluido com sucesso !\n");
}
void apagar_contratos_consumidor(char *iden){//APAGA OS CONTRATOS RELACIONADOS AO CONMSUMIDOR QUE SERA EXCLUIDO 
    FILE* arquivo;
    FILE* arquivo_temporario;
    CADASTRAR_CONTRATO contrato;

    arquivo = fopen("contrato.txt","rb");
    arquivo_temporario = fopen("contrato_temporario.txt","ab");

    if(arquivo != NULL || arquivo_temporario != NULL){
        //VAI LER LINHA POR LINHA
        while(fread(&contrato,sizeof(CADASTRAR_CONTRATO),1,arquivo) == 1){
            //O QUE FOR DIFERENTE DO CNPJ DIGITADO VAI SER GUARDADO EM UM ARQUIVO TEMPORARIO
            if (strcmp(iden,contrato.iden_contr_consu) != 0){
                fwrite(&contrato,sizeof(CADASTRAR_CONTRATO),1,arquivo_temporario);
            }
            
        }
    }

    fclose(arquivo);
    fclose(arquivo_temporario);
    //APAGA O ARQUIVO
    remove("contrato.txt");
    //PEGA O TEMPORARIO E RENOMEIA ELE PARA O ARQUIVO ANTIGO
    rename("contrato_temporario.txt", "contrato.txt");
}