#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum {
    OUROS,
    PAUS,
    COPAS,
    ESPADAS
} Naipe;

typedef struct {
    int valor;
    Naipe naipe;
} Carta;

typedef struct No {
    Carta carta;
    struct No *proximo;
} No;

Carta criarCarta(int valor, Naipe naipe) {
    Carta nova;
    nova.valor = valor;
    nova.naipe = naipe;
    return nova;
}

No *inserirCarta(No *topo, Carta carta) {
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    novo->carta = carta;
    novo->proximo = topo;
    return novo;
}

No *criarBaralho() {
    No *topo = NULL;
    for (int naipe = OUROS; naipe <= ESPADAS; naipe++) {
        for (int valor = 1; valor <= 13; valor++) {
            topo = inserirCarta(topo, criarCarta(valor, naipe));
        }
    }
    return topo;
}

void imprimirCarta(Carta c) {
    char *nomesNaipe[] = {"Ouros", "Paus", "Copas", "Espadas"};
    char *nomesValor[] = {"", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    printf("%s de %s\n", nomesValor[c.valor], nomesNaipe[c.naipe]);
}

void imprimirBaralho(No *topo) {
    No *atual = topo;
    while (atual != NULL) {
        imprimirCarta(atual->carta);
        atual = atual->proximo;
    }
}

void liberarBaralho(No *topo) {
    No *atual = topo;
    while (atual != NULL) {
        No *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
}

int main() {
    srand(time(NULL));
    No *baralho = criarBaralho();

    int pos_inicial = rand() % 52;
    No *atual = baralho;
    for (int i = 0; i < pos_inicial; i++) {
        atual = atual->proximo;
    }
    Carta carta_inicial = atual->carta;
    printf("Carta inicial: ");
    imprimirCarta(carta_inicial);

    char escolha;
    printf("A proxima carta sera maior (x) ou menor (y)? ");
    scanf(" %c", &escolha);

    int pos_proxima = rand() % 52;
    atual = baralho;
    for (int i = 0; i < pos_proxima; i++) {
        atual = atual->proximo;
    }
    Carta carta_proxima = atual->carta;
    printf("Proxima carta: ");
    imprimirCarta(carta_proxima);

    if ((escolha == 'x' && carta_proxima.valor > carta_inicial.valor) ||
        (escolha == 'y' && carta_proxima.valor < carta_inicial.valor)) {
        printf("Voce acertou!\n");
    } else if (carta_proxima.valor == carta_inicial.valor) {
        printf("Empate! As cartas tem o mesmo valor.\n");
    } else {
        printf("Voce errou!\n");
    }

    liberarBaralho(baralho);
    return 0;
}
