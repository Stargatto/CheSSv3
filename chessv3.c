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
#include "scacchiera.h"

#define DIFF 3

int main()
{
        SCACCHIERA scacchiera;
        SCACCHIERA test;
        char input[10];
        char x,y,x2,y2;
        int diff = DIFF;

        ShowIntro();
        Init(&scacchiera);
        Printa(scacchiera);

        while (input[0] != 'q') {
                printf("\n> ");
                fgets(input, 10, stdin);
                if (input[0] == 'p') Printa(scacchiera);
                if (input[0] == 'd') {
                        diff = atoi(&input[2]);
                        printf("Diff=%d", diff);
                }
                if (input[0] == 'm') {
                        x = ((int)input[2] - 97);
                        y = (int)input[3] - 49;
                        x2 = ((int)input[4] - 97);
                        y2 = (int)input[5] - 49;
                        MossePossibili(scacchiera, &test, x, y);
                        if (MossaCorretta(scacchiera, x, y, x2, y2)) {
                                Muovi(&scacchiera, x, y, x2, y2);
                                Rispondi(scacchiera, diff, &scacchiera);
                                Printa(scacchiera);
                                printf("\nPunteggio attuale: %d", -Punteggio(scacchiera));
                        } else {
                                printf("Mossa non Corretta, le posse possibili sono:\n");
                                Printa(test);
                                printf("\nCiucciati il tonno");
                        }
                }
                if (input[0] == 'r') Rispondi(scacchiera, diff, &scacchiera);

                if (input[0] == '?') {
                        int c;
                        x = ((int)input[2] - 97);
                        y = (int)input[3] - 49;
                        if (MossePossibili(scacchiera, &test, x, y) == 0)
                                printf("\nNon ci sono mosse possibili");
                        else
                                Printa(test);
                }

        }
        printf("\nBuona Giornata! \n");
        return 0;
}
