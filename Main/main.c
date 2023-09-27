#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include "compartimento_hash.h"

int main(){
    FILE *hash;
    FILE *meta;
    FILE *clientes;


    if ((hash = fopen("tabHash.dat", "r+b")) == NULL){
    printf("Erro ao abrir o arquivo da tabela Hash");
    exit(1);
    }
    if ((meta = fopen("meta.dat", "r+b")) == NULL){
    printf("Erro ao abrir o arquivo da tabela Meta");
    exit(1);
    }

    if ((hash = fopen("clientes.dat", "r+b")) == NULL){
    printf("Erro ao abrir o arquivo da tabela Clientess");
    exit(1);
    }
    
    menu(hash, meta, clientes);

    return 0;
}

void menu(FILE *hash, FILE *meta, FILE *clientes){
    int escolha, chave;
    char nome[100];
    Cliente *novo;
    

    printf("Menu:\n 1 - Inserir \n 2 - Deletar \n 3 - Busca \n 4 - Zerar \n 5 - Sair \n");
    scanf("%d", &escolha);
    switch (escolha)
    {
    case 1:
        printf("Digite o número da chave do cliente: \n");
        scanf("%d", &chave);
        printf("Digite o nome do cliente:\n");
        scanf("%s", nome);
        novo = criarCliente(chave, nome);
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
