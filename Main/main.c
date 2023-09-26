#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include "compartimento_hash.h"

int main(){
    
    menu();

    return 0;
}

void menu(){
    int escolha;
    FILE *hash;
    FILE *meta;
    FILE *clientes;


    printf("Menu:\n 1 - Inserir \n 2 - Deletar \n 3 - Busca \n 4 - Zerar \n 5 - Sair \n");
    scanf("%d", &escolha);
    switch (escolha)
    {
    case 1:
        inserir();
        menu();
        break;
    case 2:
        deletar();
        menu();
        break;
    case 3:
        busca();
        menu();
        break;
    case 4:
        zerar();
        menu();
        break;
    case 5:
        exit(1);
        break;
    default:
        printf("Escolha um dos números do menu\n");
        menu();
        break;
    }

}
