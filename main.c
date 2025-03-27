#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura Produto
typedef struct Produto {
    int id;
    char nome[100];
    float preco;
    int quantidade;
    struct Produto* esquerda;
    struct Produto* direita;
} Produto;

// Função para criar um novo produto
Produto* criarProduto(int id, char nome[], float preco, int quantidade) {
    Produto* novoProduto = (Produto*)malloc(sizeof(Produto));
    novoProduto->id = id;
    strcpy(novoProduto->nome, nome);
    novoProduto->preco = preco;
    novoProduto->quantidade = quantidade;
    novoProduto->esquerda = NULL;
    novoProduto->direita = NULL;
    return novoProduto;
}

// Função para inserir um produto na árvore binária de busca
Produto* inserirProduto(Produto* raiz, Produto* novoProduto) {
    if (raiz == NULL) {
        return novoProduto;
    }
    
    // Comparação baseada no ID do produto
    if (novoProduto->id < raiz->id) {
        raiz->esquerda = inserirProduto(raiz->esquerda, novoProduto);
    } else if (novoProduto->id > raiz->id) {
        raiz->direita = inserirProduto(raiz->direita, novoProduto);
    } else {
        // Se os IDs forem iguais, comparar pelo nome
        if (strcmp(novoProduto->nome, raiz->nome) < 0) {
            raiz->esquerda = inserirProduto(raiz->esquerda, novoProduto);
        } else {
            raiz->direita = inserirProduto(raiz->direita, novoProduto);
        }
    }
    return raiz;
}

// Função para buscar um produto na árvore binária de busca
Produto* buscarProduto(Produto* raiz, int id) {
    if (raiz == NULL || raiz->id == id) {
        return raiz;
    }
    
    if (id < raiz->id) {
        return buscarProduto(raiz->esquerda, id);
    } else {
        return buscarProduto(raiz->direita, id);
    }
}

// Função para encontrar o produto com o menor ID na subárvore
Produto* minimo(Produto* raiz) {
    while (raiz->esquerda != NULL) {
        raiz = raiz->esquerda;
    }
    return raiz;
}

// Função para remover um produto da árvore binária de busca
Produto* removerProduto(Produto* raiz, int id) {
    if (raiz == NULL) {
        return raiz;
    }

    if (id < raiz->id) {
        raiz->esquerda = removerProduto(raiz->esquerda, id);
    } else if (id > raiz->id) {
        raiz->direita = removerProduto(raiz->direita, id);
    } else {
        // Caso 1: Produto sem filhos
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            return NULL;
        }
        // Caso 2: Produto com um filho
        if (raiz->esquerda == NULL) {
            Produto* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            Produto* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        
        // Caso 3: Produto com dois filhos
        Produto* sucessor = minimo(raiz->direita);
        raiz->id = sucessor->id;
        strcpy(raiz->nome, sucessor->nome);
        raiz->preco = sucessor->preco;
        raiz->quantidade = sucessor->quantidade;
        raiz->direita = removerProduto(raiz->direita, sucessor->id);
    }
    return raiz;
}

// Função para exibir todos os produtos na árvore em ordem crescente de ID
void exibirProdutos(Produto* raiz) {
    if (raiz != NULL) {
        exibirProdutos(raiz->esquerda);
        printf("ID: %d | Nome: %s | Preço: %.2f | Quantidade: %d\n", raiz->id, raiz->nome, raiz->preco, raiz->quantidade);
        exibirProdutos(raiz->direita);
    }
}

// Função para atualizar o preço e a quantidade de um produto dado seu ID
Produto* atualizarProduto(Produto* raiz, int id, float preco, int quantidade) {
    Produto* produto = buscarProduto(raiz, id);
    if (produto != NULL) {
        produto->preco = preco;
        produto->quantidade = quantidade;
    } else {
        printf("Produto com ID %d não encontrado.\n", id);
    }
    return raiz;
}

int main() {
    Produto* estoque = NULL;
    
    // Inserindo produtos
    estoque = inserirProduto(estoque, criarProduto(1, "Produto A", 10.5, 100));
    estoque = inserirProduto(estoque, criarProduto(2, "Produto B", 20.0, 200));
    estoque = inserirProduto(estoque, criarProduto(3, "Produto C", 15.75, 150));
    
    // Exibindo todos os produtos
    printf("Produtos no estoque:\n");
    exibirProdutos(estoque);
    
    // Buscando um produto
    Produto* produto = buscarProduto(estoque, 2);
    if (produto != NULL) {
        printf("\nProduto encontrado: %d - %s\n", produto->id, produto->nome);
    } else {
        printf("\nProduto não encontrado.\n");
    }
    
    // Atualizando um produto
    printf("\nAtualizando preço e quantidade do Produto B:\n");
    estoque = atualizarProduto(estoque, 2, 22.0, 250);
    
    // Exibindo todos os produtos após atualização
    printf("\nProdutos no estoque após atualização:\n");
    exibirProdutos(estoque);
    
    // Removendo um produto
    printf("\nRemovendo o Produto A:\n");
    estoque = removerProduto(estoque, 1);
    
    // Exibindo todos os produtos após remoção
    printf("\nProdutos no estoque após remoção:\n");
    exibirProdutos(estoque);
    
    return 0;
}
