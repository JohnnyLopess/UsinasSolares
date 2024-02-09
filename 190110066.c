#include <stdio.h>
#include <string.h>
#include "190110066.h"

int main(){
    int opcao;
    
    do{
        cabecalho();
        menu_opcoes();
        scanf("%d",&opcao);
        switch (opcao){
        case 1:
            cabecalho();
            cadastrar_usina();
        break;
        case 2:
            cabecalho();
            cadastrar_consumidor();
        break;  
        case 3:
            cabecalho();
            cadastrar_contrato();
        break;
        case 4:
            cabecalho();
            consultar_usina();
        break;
        case 5:
            cabecalho();
            consultar_consumidor();
        break;
        case 6:
            cabecalho();
            excluir_usina();
        break;
        case 7:
            cabecalho();
            excluir_consumidor();
        break;
        case 8:
            cabecalho();
            printf("Obrigado por usar esse software !\n");
        break;
        default:
            printf("Opcao invalida !\n");
            getch();
        break;
        }
    }while(opcao!=8);

    return 0;
}