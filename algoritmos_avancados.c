#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura da sala
typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

// Estrutura de nó armazena pistas
typedef struct PistaNode {
    char pista[100];
    struct PistaNode* esquerda;
    struct PistaNode* direita;
} PistaNode;

// Criar uma nova sala
Sala* criarSala(const char* nome, Sala* esquerda, Sala* direita) {
    Sala* novaSala = (Sala*) malloc(sizeof(Sala));
    if (novaSala == NULL) {
        printf("Erro ao alocar memória para a sala.\n");
        exit(1);
    }
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = esquerda;
    novaSala->direita = direita;
    return novaSala;
}

// Inserir uma pista
PistaNode* inserir(PistaNode* raiz, const char* novaPista) {
    if (raiz == NULL) {
        PistaNode* novo = (PistaNode*) malloc(sizeof(PistaNode));
        if (novo == NULL) {
            printf("Erro ao alocar memória para pista.\n");
            exit(1);
        }
        strcpy(novo->pista, novaPista);
        novo->esquerda = novo->direita = NULL;
        return novo;
    }

    if (strcmp(novaPista, raiz->pista) < 0) {
        raiz->esquerda = inserir(raiz->esquerda, novaPista);
    } else if (strcmp(novaPista, raiz->pista) > 0) {
        raiz->direita = inserir(raiz->direita, novaPista);
    }
    return raiz;
}

// Mostrar todas as pistas
void emOrdem(PistaNode* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        emOrdem(raiz->direita);
    }
}

// Liberar memória
void liberarPistas(PistaNode* raiz) {
    if (raiz != NULL) {
        liberarPistas(raiz->esquerda);
        liberarPistas(raiz->direita);
        free(raiz);
    }
}

// Adiciona pista
void verificarPista(Sala* atual, PistaNode** pistas) {
    if (strcmp(atual->nome, "Quarto") == 0) {
        printf("Você encontrou uma pista: Chave Misteriosa\n");
        *pistas = inserir(*pistas, "Chave Misteriosa");
    } else if (strcmp(atual->nome, "Biblioteca") == 0) {
        printf("Você encontrou uma pista: Página Rasgada\n");
        *pistas = inserir(*pistas, "Página Rasgada");
    } else if (strcmp(atual->nome, "Cozinha") == 0) {
        printf("Você encontrou uma pista: Faca Ensanguentada\n");
        *pistas = inserir(*pistas, "Faca Ensanguentada");
    } else if (strcmp(atual->nome, "Porão") == 0) {
        printf("Você encontrou uma pista: Fotografia Antiga\n");
        *pistas = inserir(*pistas, "Fotografia Antiga");
    } else if (strcmp(atual->nome, "Jardim") == 0) {
        printf("Você encontrou uma pista: Pegadas na Terra\n");
        *pistas = inserir(*pistas, "Pegadas na Terra");
    }
}

// exploração com coleta de pistas
void explorarSalas(Sala* atual, PistaNode** pistas) {
    char escolha;

    while (atual != NULL) {
        printf("\nVocê está na sala: %s\n", atual->nome);

        verificarPista(atual, pistas);

        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Você chegou ao fim do caminho. Fim da exploração.\n");
            return;
        }

        printf("\nPara onde deseja ir?\n");
        if (atual->esquerda != NULL)
            printf(" [e] Esquerda  (%s)\n", atual->esquerda->nome);
        if (atual->direita != NULL)
            printf(" [d] Direita   (%s)\n", atual->direita->nome);
        printf(" [p] Ver pistas encontradas\n");
        printf(" [s] Sair da exploração\n");
        printf("Escolha (e/d/p/s): ");
        scanf(" %c", &escolha);

        switch (escolha) {
            case 'e':
                if (atual->esquerda != NULL)
                    atual = atual->esquerda;
                else
                    printf("Caminho à esquerda não existe!\n");
                break;
            case 'd':
                if (atual->direita != NULL)
                    atual = atual->direita;
                else
                    printf("Caminho à direita não existe!\n");
                break;
            case 'p':
                printf("\nPistas encontradas até agora:\n");
                if (*pistas == NULL) {
                    printf("(Nenhuma pista encontrada ainda)\n");
                } else {
                    emOrdem(*pistas);
                }
                break;
            case 's':
                printf("Você saiu da exploração.\n");
                return;
            default:
                printf("Opção inválida.\n");
        }
    }
}

// Função principal
int main() {
    Sala* quarto = criarSala("Quarto", NULL, NULL);

    Sala* cozinha = criarSala("Cozinha", NULL, NULL);
    Sala* jardim = criarSala("Jardim", NULL, NULL);
    Sala* porao = criarSala("Porão", NULL, jardim);
    Sala* biblioteca = criarSala("Biblioteca", cozinha, porao);
    Sala* sala1 = criarSala("Sala de Estar", quarto, NULL);
    Sala* sala2 = criarSala("Sala de Jantar", NULL, biblioteca);

    Sala* entrada = criarSala("Entrada da Mansão", sala1, sala2);

    PistaNode* pistas = NULL;

    explorarSalas(entrada, &pistas);

    //  memória
    free(quarto);
    free(cozinha);
    free(jardim);
    free(porao);
    free(biblioteca);
    free(sala1);
    free(sala2);
    free(entrada);
    liberarPistas(pistas);

    return 0;
}