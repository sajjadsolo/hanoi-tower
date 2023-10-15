 // Copyright 2023 Sajjad Argahvani
 /*
  *  This file is for displaying Hanoi towers in C language
  *  Author: Sajjad Arghavani <sajjad.arghavani@gmail.com>
  */
#include <stdio.h>
#include <unistd.h>

#define DELAY 30000
#define MAXRINGS 6
#define SPACER 6


int a[MAXRINGS], b[MAXRINGS], c[MAXRINGS];
int moves = 0;


int getcell(int t[], int i) {
    if (i <= MAXRINGS) {
        return t[i - 1];
    }
    return -1;
}


void print_towers_char() {
    int i = MAXRINGS + 1;
    moves++;
    printf("\033[%dAMove: %d\n", MAXRINGS + 7, moves);

    while (i > 0) {
        int cell_a = getcell(a, i);
        int cell_b = getcell(b, i);
        int cell_c = getcell(c, i);

        char char_a = (cell_a == -1) ? '|' : cell_a + '0';
        char char_b = (cell_b == -1) ? '|' : cell_b + '0';
        char char_c = (cell_c == -1) ? '|' : cell_c + '0';

        printf("%*c%*c%*c\n", SPACER, char_a, SPACER, char_b, SPACER, char_c);
        i--;
    }

    for (int j = 0; j < SPACER * 2 + 3 * MAXRINGS; j++) {
        printf("-");
    }
    printf("\n");
    printf("%*c%*c%*c\n\n", SPACER, 'A', SPACER, 'B', SPACER, 'C');
}


void move(int n, int *ta, int *tb, int *tc) {
    usleep(DELAY);

    if (n == 1) {
        int empty_index = -1;
        for (int i = 0; i < MAXRINGS; i++) {
            if (tb[i] == -1) {
                empty_index = i;
                break;
            }
        }
        tb[empty_index] = ta[n - 1];
        ta[n - 1] = -1;
        print_towers_char();
        return;
    }

    move(n - 1, ta, tc, tb);
    int empty_index = -1;
    for (int i = 0; i < MAXRINGS; i++) {
        if (tb[i] == -1) {
            empty_index = i;
            break;
        }
    }
    int moved_ring = ta[n - 1];
    int temp_index = empty_index;

    while (temp_index > 0 && tb[temp_index - 1] > moved_ring) {
        tb[temp_index] = tb[temp_index - 1];
        temp_index--;
    }
    tb[temp_index] = moved_ring;
    ta[n - 1] = -1;
    print_towers_char();
    move(n - 1, tc, tb, ta);
}


void sort_tower_c() {
    for (int i = 0; i < MAXRINGS - 1; i++) {
        for (int j = 0; j < MAXRINGS - i - 1; j++) {
            if (c[j] < c[j + 1]) {
                int temp = c[j];
                c[j] = c[j + 1];
                c[j + 1] = temp;
            }
        }
    }
}


int main() {
    for (int i = 0; i < MAXRINGS; i++) {
        a[i] = MAXRINGS - i;
        b[i] = -1;
        c[i] = -1;
    }

    printf("\033c");
    print_towers_char();
    move(MAXRINGS, a, c, b);
    sort_tower_c();
    moves--; 
    print_towers_char();

    return 0;
}
