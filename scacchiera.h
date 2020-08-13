// Chess! E' un programma by Carlo Rossi 2002
// Funzione Printa() printa ovviamente l'array scacchiera.
// basta cosi'.

// To be Implemented:
// la funzione Controllamossa(x,y,X,Y)
// che controlli la validita' della mossa inserita
// all'interno della funzione Muovi();

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define UNSENSE -1
#define DEEP 20
#define UMANO 1
#define CPU (!UMANO)
#define NESSUNO -1

/* STRUTTURA SCACCHIERA */

typedef struct scac {
        char board[8][8];
} SCACCHIERA;

// Linked List
typedef struct Nodo {
        SCACCHIERA skak;
        struct Nodo* father;
        struct Nodo* next;
        int player;
        int score;
        int level;
//    uint8_t player;
//    uint8_t score;
//    uint8_t level;
} NODO;

/* Dichiarazione Funzioni */
void ShowIntro();
void Init(SCACCHIERA* scacchiera);
void Printa(SCACCHIERA scacchiera);
void Muovi(SCACCHIERA* scacchiera, char x, char y, char x2, char y2);
int MossePossibili(SCACCHIERA s, SCACCHIERA* mp, char x, char y);
int MossaCorretta(SCACCHIERA s, char x, char y, char x2, char y2);
int Punteggio(SCACCHIERA s);
void CopyScacchiera(SCACCHIERA s, SCACCHIERA * d);
int Player(SCACCHIERA sc, int a, int b);
void Rispondi(SCACCHIERA s, int diff, SCACCHIERA* mossa);

//END
