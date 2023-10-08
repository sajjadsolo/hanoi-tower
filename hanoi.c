#include <stdio.h>

#define MAXRINGS 16
#define SPACER 16

char a[MAXRINGS], b[MAXRINGS], c[MAXRINGS];
int moves = 0;

char getcell(char t[], int i) {
    if (i <= MAXRINGS) {
        return t[i - 1];
    }
    return '|';
}

void print_towers() {
    int i = MAXRINGS + 1;

    moves++;
    printf("\033[%dAMove: %d\n", MAXRINGS + 7, moves);

    while (i > 0) {
        printf("%*c%*c%*c\n", SPACER, getcell(a, i), SPACER, getcell(b, i), SPACER, getcell(c, i));
        i--;
    }

    for (int j = 0; j < SPACER * 2 + 3 * MAXRINGS; j++) {
        printf("-");
    }
    printf("\n");
    printf("%*c%*c%*c\n\n", SPACER, 'A', SPACER, 'B', SPACER, 'C');
}

void move(int n, char ta[], char tb[], char tc[]) {
    if (n == 1) {
        tb[0] = ta[0];
        ta[0] = '|';
        print_towers();
        return;
    }

    move(n - 1, ta, tc, tb);
    tb[n - 1] = ta[n - 1];
    ta[n - 1] = '|';
    print_towers();
    move(n - 1, tc, tb, ta);
}

int main() {
    for (int i = 0; i < MAXRINGS; i++) {
        a[i] = MAXRINGS - i + '0';
        b[i] = '|';
        c[i] = '|';
    }

    printf("\033c"); // Clear the console

    print_towers();
    move(MAXRINGS, a, c, b);

    return 0;
}
