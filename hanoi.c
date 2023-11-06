// Copyright 2023 Sajjad Arghavani
/*
* This file is for displaying Hanoi towers in C language
* Author: Sajjad Arghavani <sajjad.arghavani@gmail.com>
*/
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>


#define DELAY 190000
#define MAXRINGS 6
#define SPACER 6


char a[MAXRINGS], b[MAXRINGS], c[MAXRINGS];
int moves = 0;


void 
ascending(char *arr, int length) {
    int i, j;
    char temp;
    
    for (i = 0; i < length; i++) {
        for (j = i + 1; j < length; j++) {
            if (arr[i] == ' ' && arr[j] != ' ') {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}


char 
getcell(char *t, int i) {
    if (i >= 1 && i <= MAXRINGS) {
        return t[i - 1];
    }

    return ' ';
}


void 
printtowers() {
    int j;
    int i = MAXRINGS;
    char tempa[MAXRINGS], tempb[MAXRINGS], tempc[MAXRINGS];

    moves++;
    printf("\033[%dAMove: %d\n", MAXRINGS + 7, moves);
        for (int k = 0; k < MAXRINGS; k++) {
        tempa[k] = a[k];
        tempb[k] = b[k];
        tempc[k] = c[k];
    }
    ascending(tempa, MAXRINGS);
    ascending(tempb, MAXRINGS);
    ascending(tempc, MAXRINGS);
    int maxHeight = i;
    if (i < MAXRINGS) {
        maxHeight = MAXRINGS;
    }

    while (i > 0) {
        char cella = getcell(tempa, i);
        char cellb = getcell(tempb, i);
        char cellc = getcell(tempc, i);
        
        if (cella == ' ') {
            cella = '|';
        }
        if (cellb == ' ') {
            cellb = '|';
        }
        if (cellc == ' ') {
            cellc = '|';
        }

        printf("%*c%*c%*c\n", SPACER, cella, SPACER, cellb, SPACER, cellc);
        i--;
    }

    for (j = 0; j < SPACER * 2 + 3 * maxHeight; j++) {
        printf("-");
    }

    printf("\n");
    printf("%*c%*c%*c\n\n", SPACER, 'A', SPACER, 'B', SPACER, 'C');
}


void 
move(int n, char *ta, char *tb, char *tc) {
    int nextindex = (MAXRINGS - n) + 1;
    int length = sizeof(ta) / sizeof(ta[0]);

    usleep(100000);
    if (n == 1) {
        tb[MAXRINGS - n] = ta[MAXRINGS - n];
        ta[MAXRINGS - n] = ' ';
        printtowers();
        return;
    }

    move(n - 1, ta, tc, tb); 
    tb[MAXRINGS - n] = ta[MAXRINGS - n];
    ta[MAXRINGS - n] = ' ';
    printtowers();
    move(n - 1, tc, tb, ta);
}


int 
main() {
    int length = sizeof(a) / sizeof(a[0]);
    
    for (int i = 0; i < MAXRINGS; i++) {
        a[i] = MAXRINGS - i + '0';
        b[i] = ' ';
        c[i] = ' ';
    }
    
   

    printf("\033c");
    move(MAXRINGS, a, c, b);
    printtowers();

    return 0;
}
