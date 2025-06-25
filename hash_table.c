#include "hash_table.h"

// Função auxiliar para criar um novo nó (item da lista)
static No* criarNo(int chave) {
    No *novoNo = (No*) malloc(sizeof(No));
    if (novoNo == NULL) {
        perror("Erro de memória ao criar nó");
        exit(EXIT_FAILURE);
    }
    novoNo->chave = chave;
    novoNo->proximo = NULL;
    return novoNo;
}

// 1. Cria a Tabela Hash
TabelaHash* criarTabelaHash(int tamanho) {
    if (tamanho <= 0) {
        fprintf(stderr, "Erro: Tamanho da tabela deve ser positivo.\n");
        return NULL;
    }
    TabelaHash *novaTabela = (TabelaHash*) malloc(sizeof(TabelaHash));
    if (novaTabela == NULL) {
        perror("Erro de memória ao criar tabela hash");
        exit(EXIT_FAILURE);
    }
    novaTabela->tamanho = tamanho;
    novaTabela->numElementos = 0;
    novaTabela->colisoes_insercao = 0;
    novaTabela->colisoes_busca = 0;

    // Aloca o array de ponteiros e inicializa todos para NULL (gavetas vazias)
    novaTabela->buckets = (No**) calloc(tamanho, sizeof(No*));
    if (novaTabela->buckets == NULL) {
        perror("Erro de memória ao criar buckets");
        free(novaTabela);
        exit(EXIT_FAILURE);
    }
    return novaTabela;
}

// 2. Função de Hash (Método da Divisão) 
int funcaoHashDivisao(int chave, int tamanhoTabela) {
    if (tamanhoTabela <= 0) {
        return 0; // Evita divisão por zero
    }
    return chave % tamanhoTabela; // O resto da divisão indica a "gaveta" 
}

// 3. Insere um item na Tabela Hash 
int inserir(TabelaHash *tabela, int chave) {
    if (tabela == NULL) {
        fprintf(stderr, "Erro: Tabela não inicializada (inserir).\n");
        return 0;
    }

    int indice = funcaoHashDivisao(chave, tabela->tamanho); // Acha a "gaveta" 

    // Verifica se a lista da gaveta já tem itens (colisão na inserção)
    if (tabela->buckets[indice] != NULL) {
        tabela->colisoes_insercao++; // Contabiliza a colisão 
    }

    // Percorre a lista para ver se a chave já existe (evita duplicatas)
    No *atual = tabela->buckets[indice];
    while (atual != NULL) {
        if (atual->chave == chave) {
            return 0; // Chave já existe
        }
        atual = atual->proximo;
    }

    // Adiciona o novo item no INÍCIO da lista encadeada da "gaveta" 
    No *novoNo = criarNo(chave);
    novoNo->proximo = tabela->buckets[indice];
    tabela->buckets[indice] = novoNo;
    tabela->numElementos++;
    return 1; // Inserido com sucesso
}

// 4. Busca um item na Tabela Hash 
No* buscar(TabelaHash *tabela, int chave) {
    if (tabela == NULL) {
        fprintf(stderr, "Erro: Tabela não inicializada (buscar).\n");
        return NULL;
    }

    int indice = funcaoHashDivisao(chave, tabela->tamanho); // Acha a "gaveta" 
    No *atual = tabela->buckets[indice]; // Pega o primeiro item da lista da gaveta

    // Percorre a lista procurando o item
    while (atual != NULL) {
        if (atual->chave == chave) {
            return atual; // Item encontrado
        }
        tabela->colisoes_busca++; // Contabiliza que teve que olhar outro item na lista 
        atual = atual->proximo;
    }
    return NULL; // Item não encontrado
}

// 5. Remove um item da Tabela Hash 
int remover(TabelaHash *tabela, int chave) {
    if (tabela == NULL) {
        fprintf(stderr, "Erro: Tabela não inicializada (remover).\n");
        return 0;
    }

    int indice = funcaoHashDivisao(chave, tabela->tamanho); // Acha a "gaveta" 
    No *atual = tabela->buckets[indice]; // Pega o primeiro item da lista
    No *anterior = NULL; // Guarda o item anterior para "religar" a lista

    // Percorre a lista até encontrar o item ou o fim da lista
    while (atual != NULL && atual->chave != chave) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) { // Item não encontrado
        return 0;
    }

    // Se o item a ser removido for o primeiro da lista
    if (anterior == NULL) {
        tabela->buckets[indice] = atual->proximo;
    } else { // Se o item estiver no meio ou fim da lista
        anterior->proximo = atual->proximo;
    }
    free(atual); // Libera a memória do item removido
    tabela->numElementos--;
    return 1; // Removido com sucesso
}

// 6. Libera toda a memória da Tabela Hash
void liberarTabelaHash(TabelaHash *tabela) {
    if (tabela == NULL) return;

    for (int i = 0; i < tabela->tamanho; i++) {
        No *atual = tabela->buckets[i];
        while (atual != NULL) {
            No *temp = atual;
            atual = atual->proximo;
            free(temp); // Libera cada nó da lista
        }
    }
    free(tabela->buckets); // Libera o array de ponteiros
    free(tabela); // Libera a própria estrutura da tabela
}

// Calcula o Fator de Carga (quão cheia a tabela está)
// Em hash_table.c, na função calcularFatorCarga
double calcularFatorCarga(TabelaHash *tabela) {
    if (tabela == NULL || tabela->tamanho == 0) return 0.0;
    return (double)tabela->numElementos / tabela->tamanho; // 
}
