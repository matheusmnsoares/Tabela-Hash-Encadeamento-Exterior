#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"



void inserir(){
    cliente *cliente = (Cliente *);
    FILE *hash;
    FILE *meta;
    FILE *clientes;

    int posicao, contador;
    
    printf("Digite o código do cliente:");
    scanf("%d", &cliente.cod);
    printf("Digite o nome do cliente:");
    scanf("%s", cliente.nome);
    cliente.estado = 1;
    cliente.prox = -1;

    posicao = cliente.cod % 7;

    if ((hash = fopen("tabHash.dat", "r+b")) == NULL){
    printf("Erro ao abrir o arquivo da tabela Hash");
    exit(1);
    }
    rewind(hash);
    if(posicao != 0){
        fseek(hash, sizeof(int)*(posicao-1), SEEK_SET);
    }
    else{
        fseek(hash, sizeof(int), SEEK_SET);
    }

    fread(posicao, sizeof(int), 1, hash);
    
    if ((meta = fopen("meta.dat", "r+b")) == NULL){
    printf("Erro ao abrir o arquivo da tabela meta");
    exit(1);
    }
    rewind(meta);

    fread(contador, sizeof(int), 1, meta);

    if ((clientes = fopen("clientes.dat", "r+b")) == NULL){
    printf("Erro ao abrir o arquivo da tabela Clientes");
    exit(1);
    }

    if(posicao != -1){
        Cliente * atual = (Cliente *);
        fseek(clientes,sizeof(cliente)*posicao, SEEK_SET);

        while(0 < fread(&atual->cod, sizeof(int), 1, clientes)){
            fread(atual->nome, sizeof(char),sizeof(atual->nome) )

        }
    }



}

void deletar(){

}

void busca(){

}

void zerar(){

FILE *hash;
FILE *meta;
FILE *clientes;

int contador = 0;

int a = -1;

if ((hash = fopen("tabHash.dat", "w+b")) == NULL){
    printf("Erro ao abrir o arquivo da tabela Hash");
    exit(1);
}
for(int i = 0; i<6; i++){
    fwrite(&a, sizeof(int),  1, hash);
}
fclose(hash);

if ((meta = fopen("meta.dat", "w+b")) == NULL){
    printf("Erro ao abrir o arquivo da tabela meta");
    exit(1);
}

fwrite(&contador, sizeof(int), 1, meta);
fclose(meta);

if ((clientes = fopen("clientes.dat", "w+b")) == NULL){
    printf("Erro ao abrir o arquivo da tabela clientes");
    exit(1);
}
fclose(clientes);
}

Cliente *percorrer(int pos, File* busc){
    rewind(busc);

    

}
