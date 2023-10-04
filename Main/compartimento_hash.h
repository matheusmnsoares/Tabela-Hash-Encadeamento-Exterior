#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"

#define HASH_SIZE 7
#define CLIENTS_FILENAME "clientes.dat"
#define HASH_FILENAME "tabHash.dat"


Cliente *criarCliente(int chavecliente, char *nomecliente){
    Cliente *novo = (Cliente *)malloc(sizeof(Cliente));
    if (novo) {
        memset(novo, 0, sizeof(Cliente));
        novo->chave = chavecliente;
        strcpy(novo->nome, nomecliente);
        novo->estado = 1;
        novo->prox = -1;
    }
    return novo;
}

Cliente *busca(FILE *hash, FILE*clientes, int chave){
   Cliente *procurado = (Cliente *)malloc(sizeof(Cliente));
    int validade = 0;

    int posicao = chave % HASH_SIZE;

    rewind(hash);
    if (posicao == 0) {
        fread(&posicao, sizeof(int), 1, hash);
    } else {
        fseek(hash, sizeof(int) * posicao, SEEK_SET);
        fread(&posicao, sizeof(int), 1, hash);
    }
    if (posicao != -1) {
        while (validade == 0) {
            rewind(clientes);
            fseek(clientes, sizeof(Cliente) * posicao, SEEK_SET);

            fread(&procurado->chave, sizeof(int), 1, clientes);
            fread(procurado->nome, sizeof(char), sizeof(procurado->nome), clientes);
            fread(&procurado->estado, sizeof(int), 1, clientes);
            fread(&procurado->prox, sizeof(int), 1, clientes);

            if (procurado->chave == chave) {
                validade = 1;
            } else if (procurado->prox == -1) {
                validade = -1;
                procurado->chave = -1;
            } else {
                posicao = procurado->prox;
            }
        }
        return procurado;

    } else {
        procurado->chave = -1;
        return procurado;
    }
}

void inserir(FILE *hash, FILE *meta, FILE *clientes, Cliente *info){
     int posicao, contador;
    int validade = 0;
    Cliente *checagem = (Cliente *)malloc(sizeof(Cliente));
    posicao = info->chave % HASH_SIZE;

    checagem = busca(hash, clientes, info->chave);
    if (checagem->chave == info->chave) {
        printf("A chave escolhida já é cadastrada pelo cliente %s, por favor escolha uma que não esteja em uso", checagem->nome);
        free(checagem);
        free(info);
        return;
    }

    rewind(hash);
    if (posicao != 0) {
        fseek(hash, sizeof(int) * (posicao), SEEK_SET);
        fread(&posicao, sizeof(int), 1, hash);
    } else {
        fread(&posicao, sizeof(int), 1, hash);
    }

    rewind(meta);

    fread(&contador, sizeof(int), 1, meta);

    if (posicao != -1) {
        while (validade == 0) {
            rewind(clientes);
            fseek(clientes, sizeof(Cliente) * posicao, SEEK_SET);

            fread(&checagem->chave, sizeof(int), 1, clientes);
            fread(checagem->nome, sizeof(char), sizeof(checagem->nome), clientes);
            fread(&checagem->estado, sizeof(int), 1, clientes);
            fread(&checagem->prox, sizeof(int), 1, clientes);

            if (checagem->estado == 0) {
                validade = 2;
            } else if (checagem->prox == -1) {
                validade = 1;
                fseek(clientes, sizeof(int) * -1, SEEK_SET);
                fwrite(&contador, sizeof(int), 1, clientes);
            } else {
                posicao = checagem->prox;
            }
        }

        rewind(clientes);
        if (validade == 2) {
            fseek(clientes, sizeof(Cliente) * posicao, SEEK_SET);
            fwrite(&info->chave, sizeof(int), 1, clientes);
            fwrite(info->nome, sizeof(char), sizeof(info->nome), clientes);
            fwrite(&info->estado, sizeof(int), 1, clientes);
            printf("Cliente cadastrado com sucesso em uma posição vazia");
        }
    }
    if (validade != 2) { // Não existe cliente naquela hash
        rewind(clientes);
        fseek(clientes, sizeof(Cliente) * contador, SEEK_SET);
        fwrite(&info->chave, sizeof(int), 1, clientes);
        fwrite(info->nome, sizeof(char), sizeof(info->nome), clientes);
        fwrite(&info->estado, sizeof(int), 1, clientes);
        fwrite(&info->prox, sizeof(int), 1, clientes);
        contador++;
        rewind(meta);
        fwrite(&contador, sizeof(int), 1, meta);
        if (validade == 0) {
            rewind(hash);
            posicao = info->chave % HASH_SIZE;
            fseek(hash, sizeof(int) * (posicao), SEEK_SET);
            fwrite(&posicao, sizeof(int), 1, hash);
        }
    }
    free(checagem);
    free(info);
       
}

void deletar(FILE *hash, FILE *meta, FILE *clientes, int chave){
    int validade = 0, proximo;
    int posicao = chave % HASH_SIZE;
    Cliente *atual = (Cliente *)malloc(sizeof(Cliente));
    rewind(hash);

    fseek(hash, sizeof(int) * (posicao), SEEK_SET);

    fread(&posicao, sizeof(int), 1, hash);
    if (posicao != -1) {
        while (validade != 0) {
            rewind(clientes);
            fseek(clientes, sizeof(Cliente) * posicao, SEEK_SET);
            fread(&atual->chave, sizeof(int), 1, clientes);
            fread(atual->nome, sizeof(char), sizeof(atual->nome), clientes);
            fread(&atual->estado, sizeof(int), 1, clientes);
            fread(&atual->prox, sizeof(int), 1, clientes);

            if (atual->chave == chave) {
                validade = 1;
                atual->chave = -1;
                strcpy(atual->nome, "----");
                atual->estado = 0;
                proximo = atual->prox;
                fseek(clientes, sizeof(Cliente) * -1, SEEK_SET);

                fwrite(&atual->chave, sizeof(int), 1, clientes);
                fwrite(atual->nome, sizeof(char), sizeof(atual->nome), clientes);
                fwrite(&atual->estado, sizeof(int), 1, clientes);

                printf("Cliente deletado\n");
                return;
            } else if (atual->prox == -1) {
                validade = -1;
                printf("Cliente não encontrado\n");
                break;
            } else {
                posicao = atual->prox;
            }
        }
    } else {
        printf("Cliente não existe\n");
    }
    free(atual);
}
    

void zerar(FILE *hash,FILE *meta,FILE *clientes){
    int contador = 0;
    int a = -1;

    rewind(hash);
    for (int i = 0; i < HASH_SIZE; i++) {
        fwrite(&a, sizeof(int), 1, hash);
    }

    rewind(meta);
    fwrite(&contador, sizeof(int), 1, meta);
    fclose(clientes);

    if ((clientes = fopen(CLIENTS_FILENAME, "w+b")) == NULL) {
        printf("Erro ao abrir o arquivo da tabela clientes\n");
        exit(1);
    }
    fclose(clientes);
}

