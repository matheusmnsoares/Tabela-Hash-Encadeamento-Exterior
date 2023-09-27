#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"


Clientes *criarCliente(int chavecliente, char *nomecliente){
    Cliente *novo = (Cliente *) mallock(sizeof(Cliente));
    if (novo) memset(novo, 0, sizeof(Cliente));
    novo->chave = chavecliente;
    strcpy(novo->nome, nomeCliente);
    novo->estado = 1;
    novo->prox = -1;
    
    return novo;
}
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
    int cod;
    printf("Digite o código do cliente que deseja deletar:");
    scanf("%d", &cod);

    FILE *hash;
    FILE *clientes;

    int posicao = cod % 7;

    if ((hash = fopen("tabHash.dat", "r+b")) == NULL){
        printf("Erro ao abrir o arquivo da tabela Hash");
        exit(1);
    }
    rewind(hash);
    if(posicao != 0){
        fseek(hash, sizeof(int)*(posicao), SEEK_SET);
    }
    else{
        fseek(hash, sizeof(int), SEEK_SET);
    }

    fread(&posicao, sizeof(int), 1, hash);

    if ((clientes = fopen("clientes.dat", "r+b")) == NULL){
        printf("Erro ao abrir o arquivo da tabela Clientes");
        exit(1);
    }

    Cliente * atual = (Cliente *);
    fseek(clientes,sizeof(cliente)*posicao, SEEK_SET);

    while(0 < fread(&atual->cod, sizeof(int), 1, clientes)){
        fread(atual->nome, sizeof(char),sizeof(atual->nome) )
        if(atual->cod == cod){
            atual->estado = 0; // Mark the client as deleted
            fseek(clientes,sizeof(cliente)*posicao, SEEK_SET);
            fwrite(atual, sizeof(cliente), 1, clientes); // Write the updated client back to the file
            printf("Cliente deletado\n");
            return;
        }
        if(atual->prox == -1){
            break;
        }
        posicao = atual->prox;
        fseek(clientes,sizeof(cliente)*posicao, SEEK_SET);
    }
    
    printf("Cliente não encontrado\n");
}


void busca(FILE *hash, FILE*clientes, int chave){
    Cliente *procurado =(Cliente *) mallock(sizeof(Cliente));
    int validade=0;
    
    int posicao = chave%7;
    
    rewind(hash);
    if(posicao == 0){
        fread(&posicao, sizeof(int), 1, hash);
    }
    else{
        fseek(hash, sizeof(int)*posicao, SEEK_SET);
        fread(&posicao, sizeof(int), 1, hash);
    }
    if(posicao != -1){
        
        while(validade == 0){
            rewind(clientes);
            fseek(cliente, sizeof(Cliente)*posicao, SEEK_SET);
            
            fread(&procurado->chave, sizeof(int), 1, clientes);
            fread(procurado->nome, sizeof(char), sizeof(procurado->nome), clientes);
            fread(&procurado->estado, sizeof(int), 1, clientes);
            fread(&procurado->prox, sizeof(int), 1, clientes);
            
            if(procurado->chave == chave){
                validade = 1;
            }
            else if(procurado->prox == -1){
                validade = -1;
                procurado->chave = -1;
            }
            else{
                posicao = procurado->chave;
            }
        }
        return procurado;
        
    }
    else{
        procurado->chave = -1;
        return procurado;
    }
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
