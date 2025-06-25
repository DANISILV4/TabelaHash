#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h> // Para malloc e free
#include <time.h>   // Para medir o tempo

// Estrutura para cada item na lista (nó)
typedef struct No {
    int chave;
    struct No *proximo;
} No; 

// Estrutura principal da Tabela Hash
typedef struct TabelaHash {
    No **buckets;       // Array de "gavetas", cada uma apontando para uma lista
    int tamanho;        // Quantidade de gavetas (tamanho do array)
    int numElementos;   // Quantos itens estão guardados na tabela
    long long colisoes_insercao; // Contador de colisões durante a inserção
    long long colisoes_busca;    // Contador de colisões durante a busca
} TabelaHash;

// --- Protótipos das Funções ---
TabelaHash* criarTabelaHash(int tamanho); // Cria a tabela
int funcaoHashDivisao(int chave, int tamanhoTabela); // Calcula a "gaveta"
int inserir(TabelaHash *tabela, int chave); // Coloca um item na tabela
No* buscar(TabelaHash *tabela, int chave);  // Procura um item
int remover(TabelaHash *tabela, int chave); // Tira um item
void liberarTabelaHash(TabelaHash *tabela); // Limpa a memória

// Função para análise
double calcularFatorCarga(TabelaHash *tabela); // Calcula o quão "cheia" a tabela está

#endif // HASH_TABLE_H
