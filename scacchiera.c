#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "scacchiera.h"

void ShowIntro()
{
        printf("\r\n   ___   _   _   ____      _____    _____       __                  3333333");
        printf(  "\n  / __) | | | | |  __)    |  ___)  |  ___)     |  |                     33     (Che Scacchi Stupidi!)");
        printf(  "\n | |    | |_| | | |__     | |___   | |___      |  |       __    __    333");
        printf(  "\n | |    |  _  | |  __)    |___  |  |___  |     |__|       \\ \\  / /      33");
        printf(  "\n | |__  | | | | | |__      ___| |   ___| |      __         \\ \\/ /   33   33    (C) 2002-2020");
        printf( "\n  \\___) |_| |_| |____)    (_____|  (_____|     (__)         \\__/     33333     by Carlo Rossi");

        printf(  "\n\n Comandi (finora) disponibili:");
        printf(  "\n\n <m xyXY>  Muove un pezzo posto in xy nel punto XY");
        printf(    "\n <p>       Mostra la disposizione della scacchiera");
        printf(    "\n <r>       la CPU risponde");
        printf(    "\n <? xy>    Mostra le possibili mosse del pezzo in xy");
        printf(    "\n <q>       Esci \n\n");
}

//---------------------------------------------

void Init(SCACCHIERA * scacchiera)
{
        char x, y;
        for (x = 0; x <= 7; x++) {
                scacchiera->board[x][6]='P';
                scacchiera->board[x][1]='p';
                for (y=2; y<=5; y++)
                        scacchiera->board[x][y]=' ';
        }

        scacchiera->board[0][0]='t';
        scacchiera->board[1][0]='c';
        scacchiera->board[2][0]='a';
        scacchiera->board[3][0]='q';
        scacchiera->board[4][0]='k';
        scacchiera->board[5][0]='a';
        scacchiera->board[6][0]='c';
        scacchiera->board[7][0]='t';
        scacchiera->board[0][7]='T';
        scacchiera->board[1][7]='C';
        scacchiera->board[2][7]='A';
        scacchiera->board[3][7]='Q';
        scacchiera->board[4][7]='K';
        scacchiera->board[5][7]='A';
        scacchiera->board[6][7]='C';
        scacchiera->board[7][7]='T';
}

//---------------------------------------------

void Printa(SCACCHIERA scacchiera)
{
// Posto
//      X
//   +-----
//   |
// Y |
        int x, y;
        printf("\n     A   B   C   D   E   F   G   H");
        printf("\n   +---+---+---+---+---+---+---+---+ \n %d ",1);
        for (y = 0; y <= 7; y++) {
                for(x = 0; x <= 7; x++) {
                        printf("| %c ", scacchiera.board[x][y]);
                }

                if (y < 7) printf("|\n   +---+---+---+---+---+---+---+---+\n %d ", y + 2);
                else printf("|\n   +---+---+---+---+---+---+---+---+\n");
        }

}

//---------------------------------------------

void Muovi(SCACCHIERA *scacchiera, char x, char y, char x2, char y2)
{
        scacchiera->board[x2][y2] = scacchiera->board[x][y];
        scacchiera->board[x][y] = ' ';
}

//---------------------------------------------

int MossePossibili(SCACCHIERA s, SCACCHIERA* mp, char x, char y)
{

// esempio comando
//
// 012345
// m a7b2

        char a,b;
        int counter = 0;

        for (a=0; a<=7; a++)
                for(b=0; b<=7; b++) mp->board[a][b]=' ';

        /* MOSSE DELL'UMANO*/

// Pedone

        if (s.board[x][y]=='P') {
                if (s.board[x][y-1]==' ') {mp->board[x][y-1]='x'; counter++;}
                if (x+1<=7 && y-1>=0)
                        if (s.board[x+1][y-1]>96) {mp->board[x+1][y-1]='x'; counter++;}
                if (x-1>=0 && y-1>=0)
                        if (s.board[x-1][y-1]>96) {mp->board[x-1][y-1]='x'; counter++;}

                if (s.board[x][y-2]==' ' && y==6) {mp->board[x][y-2]='x'; counter++;}
        }

// Re !

        if (s.board[x][y]=='K') {
                if (x+1<=7 && y-1>=0)
                        if (s.board[x+1][y-1]==' ' || s.board[x+1][y-1]>96 ) {mp->board[x+1][y-1]='x'; counter++;}
                if (x+1<=7)
                        if (s.board[x+1][y]==' '   || s.board[x+1][y]>96 )     {mp->board[x+1][y]='x'; counter++;}
                if (x+1<=7 && y+1<=7)
                        if (s.board[x+1][y+1]==' ' || s.board[x+1][y+1]>96 ) {mp->board[x+1][y+1]='x'; counter++;}
                if (y+1<=7)
                        if (s.board[x][y+1]==' '   || s.board[x][y+1]>96 )     {mp->board[x][y+1]='x'; counter++;}

                if (x-1>=0 && y+1<=7)
                        if (s.board[x-1][y+1]==' ' || s.board[x-1][y+1]>96 ) {mp->board[x-1][y+1]='x'; counter++;}
                if (x-1>=0)
                        if (s.board[x-1][y]==' '   || s.board[x-1][y]>96 )     {mp->board[x-1][y]='x'; counter++;}
                if (x-1>=0 && y-1>=0)
                        if (s.board[x-1][y-1]==' ' || s.board[x-1][y-1]>96 ) {mp->board[x-1][y-1]='x'; counter++;}
                if (y-1>=0)
                        if (s.board[x][y-1]==' '   || s.board[x][y-1]>96  )    {mp->board[x][y-1]='x'; counter++;}
        }

// Cavallo !

        if (s.board[x][y]=='C') {
                if (x+1<=7 && y-2>=0)
                        if (s.board[x+1][y-2]==' ' || s.board[x+1][y-2]>96 ) {mp->board[x+1][y-2]='x'; counter++;}
                if (x+2<=7 && y-1>=0)
                        if (s.board[x+2][y-1]==' ' || s.board[x+2][y-1]>96 ) {mp->board[x+2][y-1]='x'; counter++;}
                if (x+2<=7 && y+1<=7)
                        if (s.board[x+2][y+1]==' ' || s.board[x+2][y+1]>96 ) {mp->board[x+2][y+1]='x'; counter++;}
                if (x+1<=7 && y+2<=7)
                        if (s.board[x+1][y+2]==' ' || s.board[x+1][y+2]>96 ) {mp->board[x+1][y+2]='x'; counter++;}
                if (x-1>=0 && y+2<=7)
                        if (s.board[x-1][y+2]==' ' || s.board[x-1][y+2]>96 ) {mp->board[x-1][y+2]='x'; counter++;}
                if (x-2>=0 && y+1<=7)
                        if (s.board[x-2][y+1]==' ' || s.board[x-2][y+1]>96 ) {mp->board[x-2][y+1]='x'; counter++;}
                if (x-2>=0 && y-1>=0)

                        if (s.board[x-2][y-1]==' ' || s.board[x-2][y-1]>96 ) {mp->board[x-2][y-1]='x'; counter++;}
                if (x-1>=0 && y-2>=0)
                        if (s.board[x-1][y-2]==' ' || s.board[x-1][y-2]>96 ) {mp->board[x-1][y-2]='x'; counter++;}
        }

// Alfiere!

        if (s.board[x][y]=='A' || s.board[x][y]=='Q') {
                for (a=1; a<=7; a++) {
                        if (x+a<=7 && y-a>=0)
                                if (s.board[x+a][y-a]==' ') {mp->board[x+a][y-a]='x'; counter++;}
                                else if (s.board[x+a][y-a]>96 ) {mp->board[x+a][y-a]='x'; counter++;break;}
                                else break;
                }

                for (a=1; a<=7; a++) {
                        if (x+a<=7 && y+a<=7)
                                if (s.board[x+a][y+a]==' ') {mp->board[x+a][y+a]='x'; counter++;}
                                else if (s.board[x+a][y+a]>96 ) {mp->board[x+a][y+a]='x'; counter++;break;}
                                else break;
                }

                for (a=1; a<=7; a++) {
                        if (x-a>=0 && y+a<=7)
                                if (s.board[x-a][y+a]==' ') {mp->board[x-a][y+a]='x'; counter++;}
                                else if (s.board[x-a][y+a]>96 ) {mp->board[x-a][y+a]='x'; counter++;break;}
                                else break;
                }

                for (a=1; a<=7; a++) {
                        if (x-a>=0 && y-a>=0)
                                if (s.board[x-a][y-a]==' ') {mp->board[x-a][y-a]='x'; counter++;}
                                else if (s.board[x-a][y-a]>96 ) {mp->board[x-a][y-a]='x'; counter++;break;}
                                else break;
                }
        }

// Torre!

        if (s.board[x][y]=='T' || s.board[x][y]=='Q') {
                for (a=1; a<=7; a++) {
                        if (x+a<=7)
                                if (s.board[x+a][y]==' ') {mp->board[x+a][y]='x'; counter++;}
                                else if (s.board[x+a][y]>96) {mp->board[x+a][y]='x'; counter++;break;}
                                else break;
                }

                for (a=1; a<=7; a++) {
                        if (y+a<=7)
                                if (s.board[x][y+a]==' ') {mp->board[x][y+a]='x'; counter++;}
                                else if (s.board[x][y+a]>96) {mp->board[x][y+a]='x'; counter++;break;}
                                else break;
                }

                for (a=1; a<=7; a++) {
                        if (x-a>=0)
                                if (s.board[x-a][y]==' ') {mp->board[x-a][y]='x'; counter++;}
                                else if (s.board[x-a][y]>96) {mp->board[x-a][y]='x'; counter++;break;}
                                else break;
                }

                for (a=1; a<=7; a++) {
                        if (x-a>=0 && y-a>=0)
                                if (s.board[x][y-a]==' ') {mp->board[x][y-a]='x'; counter++;}
                                else if (s.board[x][y-a]>96) {mp->board[x][y-a]='x'; counter++;break;}
                                else break;
                }
        }

        /* MOSSE CPU */

// Pedone

        if (s.board[x][y]=='p') {
                if (s.board[x][y+1]==' ') {mp->board[x][y+1]='x'; counter++;}
                if (x+1<=7 && y+1>=0)
                        if (s.board[x+1][y+1]<96 && s.board[x+1][y+1]!= ' ') {mp->board[x+1][y+1]='x'; counter++;}
                if (x-1>=0 && y+1>=0)
                        if (s.board[x-1][y+1]<96 && s.board[x-1][y+1]!= ' ') {mp->board[x-1][y+1]='x'; counter++;}
                if (s.board[x][y+2]==' ' && y==1) {mp->board[x][y+2]='x'; counter++;}
        }

// Re !
        if (s.board[x][y]=='k') {
                if (x+1<=7 && y-1>=0)
                        if (s.board[x+1][y-1]==' ' || s.board[x+1][y-1]<96 ) {mp->board[x+1][y-1]='x'; counter++;}
                if (x+1<=7)
                        if (s.board[x+1][y]==' '   || s.board[x+1][y]<96 )     {mp->board[x+1][y]='x'; counter++;}
                if (x+1<=7 && y+1<=7)
                        if (s.board[x+1][y+1]==' ' || s.board[x+1][y+1]<96 ) {mp->board[x+1][y+1]='x'; counter++;}
                if (y+1<=7)
                        if (s.board[x][y+1]==' '   || s.board[x][y+1]<96 )     {mp->board[x][y+1]='x'; counter++;}

                if (x-1>=0 && y+1<=7)
                        if (s.board[x-1][y+1]==' ' || s.board[x-1][y+1]<96 ) {mp->board[x-1][y+1]='x'; counter++;}
                if (x-1>=0)
                        if (s.board[x-1][y]==' '   || s.board[x-1][y]<96 )     {mp->board[x-1][y]='x'; counter++;}
                if (x-1>=0 && y-1>=0)
                        if (s.board[x-1][y-1]==' ' || s.board[x-1][y-1]<96 ) {mp->board[x-1][y-1]='x'; counter++;}
                if (y-1>=0)
                        if (s.board[x][y-1]==' '   || s.board[x][y-1]<96  )    {mp->board[x][y-1]='x'; counter++;}
        }

// Cavallo !

        if (s.board[x][y]=='c') {
                if (x+1<=7 && y-2>=0)
                        if (s.board[x+1][y-2]==' ' || s.board[x+1][y-2]<96 ) {mp->board[x+1][y-2]='x'; counter++;}
                if (x+2<=7 && y-1>=0)
                        if (s.board[x+2][y-1]==' ' || s.board[x+2][y-1]<96 ) {mp->board[x+2][y-1]='x'; counter++;}
                if (x+2<=7 && y+1<=7)
                        if (s.board[x+2][y+1]==' ' || s.board[x+2][y+1]<96 ) {mp->board[x+2][y+1]='x'; counter++;}
                if (x+1<=7 && y+2<=7)
                        if (s.board[x+1][y+2]==' ' || s.board[x+1][y+2]<96 ) {mp->board[x+1][y+2]='x'; counter++;}
                if (x-1>=0 && y+2<=7)
                        if (s.board[x-1][y+2]==' ' || s.board[x-1][y+2]<96 ) {mp->board[x-1][y+2]='x'; counter++;}
                if (x-2>=0 && y+1<=7)
                        if (s.board[x-2][y+1]==' ' || s.board[x-2][y+1]<96 ) {mp->board[x-2][y+1]='x'; counter++;}
                if (x-2>=0 && y-1>=0)

                        if (s.board[x-2][y-1]==' ' || s.board[x-2][y-1]<96 ) {mp->board[x-2][y-1]='x'; counter++;}
                if (x-1>=0 && y-2>=0)
                        if (s.board[x-1][y-2]==' ' || s.board[x-1][y-2]<96 ) {mp->board[x-1][y-2]='x'; counter++;}
        }

// Alfiere!

        if (s.board[x][y]=='a' || s.board[x][y]=='q') {
                for (a=1; a<=7; a++) {
                        if (x+a<=7 && y-a>=0)
                                if (s.board[x+a][y-a]==' ') {mp->board[x+a][y-a]='x'; counter++;}
                                else if (s.board[x+a][y-a]<96 ) {mp->board[x+a][y-a]='x'; counter++;break;}
                                else break;
                }

                for (a=1; a<=7; a++) {
                        if (x+a<=7 && y+a<=7)
                                if (s.board[x+a][y+a]==' ') {mp->board[x+a][y+a]='x'; counter++;}
                                else if (s.board[x+a][y+a]<96 ) {mp->board[x+a][y+a]='x'; counter++;break;}
                                else break;
                }

                for (a=1; a<=7; a++) {
                        if (x-a>=0 && y+a<=7)
                                if (s.board[x-a][y+a]==' ') {mp->board[x-a][y+a]='x'; counter++;}
                                else if (s.board[x-a][y+a]<96 ) {mp->board[x-a][y+a]='x'; counter++;break;}
                                else break;
                }

                for (a=1; a<=7; a++) {
                        if (x-a>=0 && y-a>=0)
                                if (s.board[x-a][y-a]==' ') {mp->board[x-a][y-a]='x'; counter++;}
                                else if (s.board[x-a][y-a]<96 ) {mp->board[x-a][y-a]='x'; counter++;break;}
                                else break;
                }
        }

// Torre!

        if (s.board[x][y]=='t' || s.board[x][y]=='q') {
                for (a=1; a<=7; a++) {
                        if (x+a<=7)
                                if (s.board[x+a][y]==' ') {mp->board[x+a][y]='x'; counter++;}
                                else if (s.board[x+a][y]<96) {mp->board[x+a][y]='x'; counter++;break;}
                                else break;
                }

                for (a=1; a<=7; a++) {
                        if (y+a<=7)
                                if (s.board[x][y+a]==' ') {mp->board[x][y+a]='x'; counter++;}
                                else if (s.board[x][y+a]<96) {mp->board[x][y+a]='x'; counter++;break;}
                                else break;
                }

                for (a=1; a<=7; a++) {
                        if (x-a>=0)
                                if (s.board[x-a][y]==' ') {mp->board[x-a][y]='x'; counter++;}
                                else if (s.board[x-a][y]<96) {mp->board[x-a][y]='x'; counter++;break;}
                                else break;
                }

                for (a=1; a<=7; a++) {
                        if (x-a>=0 && y-a>=0)
                                if (s.board[x][y-a]==' ') {mp->board[x][y-a]='x'; counter++;}
                                else if (s.board[x][y-a]<96) {mp->board[x][y-a]='x'; counter++;break;}
                                else break;
                }
        }


        return counter;
}

//---------------------------------------------

int MossaCorretta(SCACCHIERA s, char x, char y, char x2, char y2)
{
        SCACCHIERA tmp;
        if (s.board[x][y] == ' ' || s.board[x2][y2] == 'K' || s.board[x2][y2] == 'k') return UNSENSE;

        if (MossePossibili(s, &tmp, x, y) > 0 && tmp.board[x2][y2] == 'x')
                return TRUE;

        return FALSE;
}

//---------------------------------------------

int Punteggio(SCACCHIERA s)
{
        char a, b;
        int punteggio = 0;

        for (a = 0; a <= 7; a++)
                for (b = 0; b <= 7; b++)
                        switch (s.board[a][b]) {
                                case 't' :
                                        punteggio += 5;
                                        break;
                                case 'c' :
                                        punteggio += 3;
                                        break;
                                case 'a' :
                                        punteggio += 3;
                                        break;
                                case 'k' :
                                        punteggio += 50;
                                        break;
                                case 'q' :
                                        punteggio += 9;
                                        break;
                                case 'p' :
                                        punteggio += 1;
                                        break;
                                case 'T' :
                                        punteggio -= 5;
                                        break;
                                case 'C' :
                                        punteggio -= 3;
                                        break;
                                case 'A' :
                                        punteggio -= 3;
                                        break;
                                case 'K' :
                                        punteggio -= 50;
                                        break;
                                case 'Q' :
                                        punteggio -= 9;
                                        break;
                                case 'P' :
                                        punteggio -= 1;
                                        break;
                        }
        return punteggio;
}

//---------------------------------------------

void CopyScacchiera(SCACCHIERA s, SCACCHIERA* d)
{
        int a, b;
        for (a = 0; a < 8; a++)
                for (b = 0; b < 8; b++)
                        d->board[a][b] = s.board[a][b];
}

//---------------------------------------------

int Player(SCACCHIERA sc, int a, int b)
{
        if (sc.board[a][b] >= 65 && sc.board[a][b] <= 90) return UMANO;
        else if (sc.board[a][b] >= 97 && sc.board[a][b] <= 122) return CPU;
        return NESSUNO;
}

//---------------------------------------------

NODO* GeneraListaMosse(SCACCHIERA s, int p, int deep, NODO* list)
{
        int a, b;
        int x, y;
        int c, counter = 0;
        SCACCHIERA tmp, new;
        NODO* father = list;

        for (a = 0; a < 8; a++)
                for (b = 0; b < 8; b++) {
                        if (Player(s, a, b) == p && (c = MossePossibili(s, &tmp, a, b)) > 0) {
                                counter += c;
                                for (x = 0; x < 8; x++)
                                        for (y = 0; y < 8; y++)
                                                if (tmp.board[x][y] == 'x') {
                                                        //---------------------------
                                                        // Qui devo aggiungere nodo
                                                        //---------------------------
                                                        CopyScacchiera(s, &new);
                                                        Muovi(&new, a, b, x, y);

                                                        NODO* nodo_tmp = NULL;
                                                        nodo_tmp = (NODO*)malloc(sizeof(NODO));
                                                        nodo_tmp->father = father;
                                                        nodo_tmp->skak = new;
                                                        nodo_tmp->player = p;
                                                        nodo_tmp->score = Punteggio(new);
                                                        nodo_tmp->level = deep;
                                                        nodo_tmp->next = list;
                                                        list = nodo_tmp;

                                                        if (deep > 0) {
                                                                list = GeneraListaMosse(new, !p, deep - 1, list);        
                                                        }
                                                }
                                } 
                        }
                
        return list;
}

//---------------------------------------------

void PropagaScore(NODO* list, int deep)
{
        NODO* iter = list;

        while (iter != NULL) {
                if (iter->level == deep) {
                        if (iter->player == UMANO && iter->father->score > (iter->father->score + iter->score)) {
                                iter->father->score = iter->father->score + iter->score;
                                //printf("(%d-%d) Entro Ciclo %d\n", iter->level, iter->father->level, iter->father->score);
                        } else if (iter->player == CPU && iter->father->score < (iter->father->score + iter->score)){
                                iter->father->score = iter->father->score + iter->score;
                                //printf("(%d-%d) Entro Ciclo2 %d\n", iter->level, iter->father->level, iter->father->score);
                        }
                }
                iter = iter->next;
        }
}       

//---------------------------------------------

void Rispondi(SCACCHIERA s, int diff, SCACCHIERA* mossa) {

        NODO* list = NULL;
        list = GeneraListaMosse(s, CPU, diff, list);

        for (int i = 0; i < diff; i++) {
                PropagaScore(list, i);
        }

        NODO* iter = list;
        int possible_moves = 0;
        int max_score = INT_MIN;
        int selected_move = 0;
        time_t t;
        srand((unsigned) time(&t));

        /* Calcolo max score e numero nodi con max score*/
        while (iter != NULL) {
                if (iter->level == diff) {     
                        if (iter->score > max_score) {
                                max_score = iter->score;
                                possible_moves = 1;
                        } else if (iter->score == max_score) {
                                max_score = iter->score;
                                possible_moves++;
                        }
                }
                iter = iter->next;
        }

        selected_move = (rand() % possible_moves) + 1;
        printf("%d Mosse possibili. (score %d, diff %d). Selected move is %d\n", possible_moves, max_score, diff, selected_move);

        /* Seleziono mossa */
        iter = list;
        int c = 0;
        while (iter != NULL) {
                if (iter->level == diff && iter->score == max_score) {     
                        c++;
                        if (c == selected_move) {
                                CopyScacchiera(iter->skak, mossa);
                                break;
                        }            
                }
                iter = iter->next;
        }        
}

//END
