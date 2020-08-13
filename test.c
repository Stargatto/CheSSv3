// Chess! E' un programma by Carlo Rossi 2002
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "scacchiera.h"

void InitTest(SCACCHIERA * scacchiera)
{
        char x, y;
        for (x = 0; x <= 7; x++) 
                for (y=0; y<=7; y++)
                scacchiera->board[x][y]=' ';

        scacchiera->board[0][0]='t';
        scacchiera->board[2][0]='a';
        scacchiera->board[3][0]='q';
        scacchiera->board[5][0]='t';
        scacchiera->board[6][0]='k';
        scacchiera->board[5][1]='p';
        scacchiera->board[6][1]='p';
        scacchiera->board[7][1]='p';
        scacchiera->board[0][2]='p';
        scacchiera->board[2][2]='p';
        scacchiera->board[3][2]='a';
        scacchiera->board[3][3]='p';
        scacchiera->board[3][4]='A';
        scacchiera->board[6][4]='c';
        scacchiera->board[2][5]='C';
        scacchiera->board[3][5]='A';
        scacchiera->board[5][5]='Q';               
        scacchiera->board[6][5]='P';        
        scacchiera->board[0][6]='P';
        scacchiera->board[1][6]='P';
        scacchiera->board[2][6]='P';               
        scacchiera->board[5][6]='P';        
        scacchiera->board[6][6]='P';      
        scacchiera->board[0][7]='T';
        scacchiera->board[5][7]='T';
        scacchiera->board[6][7]='K';
}

// Globali
int diff = 3;

int main()
{       
        for(int i=0; i<20;i++) printf("%d",rand()%2);

        SCACCHIERA scacchiera;
        SCACCHIERA mp;
        SCACCHIERA mossa;
        InitTest(&scacchiera);
        Printa(scacchiera);
        //MossePossibili(scacchiera, &mp, 3, 2);
        //Printa(mp);
        Rispondi(scacchiera, diff, &mossa);
        /*
        NODO* nodo = NULL;
        int c = 0;
        int p = -100000;

        nodo = GeneraMosse(scacchiera, CPU, diff, nodo);
        SelezionaMosse(nodo, 0);
        SelezionaMosse(nodo, 1);
        SelezionaMosse(nodo, 2);
        //SelezionaMosse(nodo, 3);
        //SelezionaMosse(nodo, 4);

        NODO* iter = nodo;

        while (iter != NULL) {
                if (iter->level == 3) {
                                c++;
                        if (iter->score > p) {
                                p = iter->score;
                                CopyScacchiera(iter->skak, &mossa);
                                //Printa(iter->skak);

                        }
                                //printf("%d (%d) (%d)\n", iter->father, iter->level, iter->score);
                }

                iter = iter->next;
        }

        printf("%d Mosse possibili. (diff %d)", c, diff);
        */
        Printa(mossa);
        return 0;
}