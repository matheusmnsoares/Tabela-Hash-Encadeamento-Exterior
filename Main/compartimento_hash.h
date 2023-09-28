#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"


Clientes *criarCliente(int chavecliente, char *nomecliente){
    Cliente *novo = (Cliente *) malloc(sizeof(Cliente));
    if (novo) memset(novo, 0, sizeof(Cliente));
    novo->chave = chavecliente;
    strcpy(novo->nome, nomeCliente);
    novo->estado = 1;
    novo->prox = -1;
    
    return novo;
}
void inserir(FILE *hash,FILE *meta,FILE *clientes, Clientes *info){
    int posicao, contador;
    Cliente * checagem = (Cliente *) malloc(sizeof(Cliente));
    posicao = info->cod % 7;

    checagem = busca(hash, clientes, info->chave);
    if(checagem->chave == info->chave){
        printf("A chave escolhida já é cadastrada pelo cliente %s, por favor escolha uma que não esteja em uso", checagem->nome);
        free(checagem);
        break;
    }
   

    rewind(hash);
    if(posicao != 0){
        fseek(hash, sizeof(int)*(posicao), SEEK_SET);
    }
    else{
        fseek(hash, sizeof(int), SEEK_SET);
    }

    fread(&posicao, sizeof(int), 1, hash);
    rewind(meta);

    fread(&contador, sizeof(int), 1, meta);

    if(posicao != -1){
       while(validade == 0){
            rewind(clientes);
            fseek(cliente, sizeof(Cliente)*posicao, SEEK_SET);
            
            fread(&checagem->chave, sizeof(int), 1, clientes);
            fread(checagem->nome, sizeof(char), sizeof(checagem->nome), clientes);
            fread(&checagem->estado, sizeof(int), 1, clientes);
            fread(&checagem->prox, sizeof(int), 1, clientes);
            
            if(checagem->estado == 0){
                validade = 2;
            }
            else if(checagem->prox == -1){
                validade = 1;
            }
            else{
                posicao = checagem->chave;
            }
        }
        rewind(clientes);
        if(validade == 2){
            fseek(cliente, sizeof(Cliente)*posicao, SEEK_SET);
            fwrite(&info->chave, sizeof(int), 1, cliente);
            fwrite(info->nome, sizeof(char), sizeof(info->nome), cliente);
            fwrite(&info->estado, sizeof(int), 1, cliente);
            printf("Cliente cadastrado com sucesso em uma posição vazia");
        }
    }else{
        fseek(cliente, sizeof(Cliente)*contador, SEEK_SET);
        fwrite(&info->chave, sizeof(int), 1, cliente);
        fwrite(info->nome, sizeof(char), sizeof(info->nome), cliente);
        fwrite(&info->estado, sizeof(int), 1, cliente);
        fwrite(&info->prox, sizeof(int), 1, cliente);
        contador++;   
        }
        printf("Cliente cadastrado com sucesso no fim da tabela")
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



Cliente * busca(FILE *hash, FILE*clientes, int chave){
    Cliente *procurado =(Cliente *) malloc(sizeof(Cliente));
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
}
