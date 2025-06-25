#include "hash_table.h" // Inclui as definicoes da sua Tabela Hash

int main() {
    // Escolha um numero primo para o tamanho da tabela para melhor distribuicao
    // com o Metodo da Divisao. Ex: 101, 199, 503, 997.
    int tamanhoTabela = 101; 
    TabelaHash *minhaTabela = criarTabelaHash(tamanhoTabela);

    if (minhaTabela == NULL) {
        return EXIT_FAILURE; // Sai se a tabela nao foi criada
    }

    printf("--- Testando Tabela Hash ---\n");

    // --- Medicao de Insercao ---
    clock_t inicio_insercao = clock(); // Marca o tempo inicial
    // Inserindo algumas chaves
    inserir(minhaTabela, 5);
    inserir(minhaTabela, 106); // Colide com 5 (106 % 101 = 5)
    inserir(minhaTabela, 207); // Colide com 5 e 106 (207 % 101 = 5)
    inserir(minhaTabela, 1);
    inserir(minhaTabela, 102); // Colide com 1 (102 % 101 = 1)
    inserir(minhaTabela, 50);
    inserir(minhaTabela, 151); // Colide com 50 (151 % 101 = 50)
    inserir(minhaTabela, 99);
    inserir(minhaTabela, 200); // Colide com 99 (200 % 101 = 99)
    inserir(minhaTabela, 0); // Exemplo: chave 0
    inserir(minhaTabela, 101); // Exemplo: chave 101 colide com 0 (101 % 101 = 0)

    clock_t fim_insercao = clock(); // Marca o tempo final
    double tempo_insercao = (double)(fim_insercao - inicio_insercao) / CLOCKS_PER_SEC; // Calcula o tempo em segundos

    // --- Medicao de Busca ---
    clock_t inicio_busca = clock(); // Marca o tempo inicial
    // Buscando algumas chaves existentes e nao existentes
    buscar(minhaTabela, 106); // Deve encontrar
    buscar(minhaTabela, 1);   // Deve encontrar
    buscar(minhaTabela, 999); // Nao deve encontrar
    buscar(minhaTabela, 207); // Deve encontrar
    buscar(minhaTabela, 50);  // Deve encontrar
    buscar(minhaTabela, 100); // Nao deve encontrar
    buscar(minhaTabela, 0);   // Deve encontrar

    clock_t fim_busca = clock(); // Marca o tempo final
    double tempo_busca = (double)(fim_busca - inicio_busca) / CLOCKS_PER_SEC; // Calcula o tempo em segundos

    // --- Teste de Remocao ---
    printf("\n--- Testando Remocoes ---\n");
    remover(minhaTabela, 106); // Remove uma chave que existe e esta em uma lista
    remover(minhaTabela, 999); // Tenta remover uma chave que nao existe
    remover(minhaTabela, 5);   // Remove a primeira chave de uma lista com colisoes

    printf("\n--- Resultados de Desempenho ---\n"); 
    
    printf("Numero total de elementos na tabela: %d\n", minhaTabela->numElementos);
    printf("Tamanho da Tabela (quantidade de gavetas): %d\n", minhaTabela->tamanho);
    printf("Fator de Carga (quao cheia a tabela esta): %.2f\n", calcularFatorCarga(minhaTabela)); 
    printf("Numero de Colisoes durante a Insercao: %lld\n", minhaTabela->colisoes_insercao); 
    printf("Numero de Colisoes durante a Busca (itens percorridos na lista): %lld\n", minhaTabela->colisoes_busca); 
    printf("Tempo total gasto na Insercao: %.6f segundos\n", tempo_insercao); 
    printf("Tempo total gasto na Busca: %.6f segundos\n", tempo_busca); 

    // Libera toda a memoria usada pela tabela
    liberarTabelaHash(minhaTabela);

    printf("\nPrograma finalizado.\n");
    return 0;
}
