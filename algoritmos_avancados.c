#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de uma sala
typedef struct Sala 
{
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

// Criar uma nova sala
Sala* criarSala(const char* nome, Sala* esquerda, Sala* direita) 
{
    Sala* novaSala = (Sala*) malloc(sizeof(Sala));
    if (novaSala == NULL) 
    {
        printf("Erro ao alocar memória para a sala. \n");
        exit(1);
    }
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = esquerda;
    novaSala->direita = direita;
    return novaSala;
}

// Função de exploração
void explorarSalas(Sala* atual) 
{
    char escolha;

    while (atual != NULL) 
    {
        printf("\n Você está na sala: %s \n", atual -> nome);

        // Verifica se é um nó folha
        if (atual -> esquerda == NULL && atual -> direita == NULL) 
        {
            printf("Você chegou ao fim do caminho. Fim da exploração. \n");
            return;
        }

        // Mostra opções de escolha
        printf("Para onde deseja ir?\n");
        if (atual->esquerda != NULL) 
        {
            printf(" [e] Esquerda  %s\n", atual -> esquerda -> nome);
        }
        if (atual->direita != NULL) {
            printf(" [d] Direita  %s\n", atual -> direita -> nome);
        }
        printf(" [s] Sair da exploração \n");
        printf("Escolha (e/d/s): ");
        scanf(" %c", &escolha);

        // Processa escolha
        switch (escolha) 
        {
            case 'e':
                if (atual -> esquerda != NULL)
                    atual = atual -> esquerda;
                else
                    printf("Caminho à esquerda não existe! \n");
                break;
            case 'd':
                if (atual -> direita != NULL)
                    atual = atual -> direita;
                else
                    printf("Caminho à direita não existe! \n");
                break;
            case 's':
                printf("Você saiu da exploração. \n");
                return;
            default:
                printf("Opção inválida. \n");
        }
    }
}

// Função principal
int main() 
{
    Sala* quarto = criarSala("Quarto", NULL, NULL);
    Sala* biblioteca = criarSala("Biblioteca", NULL, NULL);

    Sala* sala1 = criarSala("Sala de Estar", quarto, NULL);
    Sala* sala2 = criarSala("Sala de Jantar", NULL, biblioteca);

    Sala* entrada = criarSala("Entrada da Mansão", sala1, sala2);

    explorarSalas(entrada);

    free(quarto);
    free(biblioteca);
    free(sala1);
    free(sala2);
    free(entrada);

    return 0;
}