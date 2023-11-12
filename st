// Copyright 2023 Sajjad Arghavani
/*
* This file is for displaying Hanoi towers in C language
* Author: Sajjad Arghavani <sajjad.arghavani@gmail.com>
*/
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>


#define DELAY 200000
#define MAXRINGS 6
#define SPACER 6


typedef struct {
    int stack[MAXRINGS];
    int top;
}stacks;


void
initstack(stacks* s) {
    s->top = -1;
}


bool
isstackempty(stacks* s) {
    return (s->top == -1);
}


bool
isstackfull(stacks* s) {
    return (s->top == MAXRINGS - 1);
}


void
push(stacks* s, int value) {
    int index = s->top + 1;

    if (isstackfull(s)) {
        printf("Stack is full\n");
        return;
    }

    while (index > 0 && s->stack[index - 1] > value) {
        s->stack[index] = s->stack[index - 1];
        index--;
    }

    s->stack[index] = value;
    s->top++;
}


int
pop(stacks* s) {
    if (isstackempty(s)) {
        printf("Stack is empty\n");
        return -1;
    }

    return s->stack[s->top--];
}


void
printtowers(stacks* stacka, stacks* stackb, stacks* stackc, int moves) {
    int j;
    int i = MAXRINGS - 1;

    moves++;
    printf("\033[%dAMove: %d\n", MAXRINGS + 7, moves);

while (i > 0) {
    int cella = (i <= stacka->top) ? stacka->stack[stacka->top - (i)] : 0;
    int cellb = (i <= stackb->top) ? stackb->stack[stackb->top - (i)] : 0;
    int cellc = (i <= stackc->top) ? stackc->stack[stackc->top - (i)] : 0;
    


    printf("%*d%*d%*d\n", SPACER, cella, SPACER, cellb, SPACER, cellc);
    i--;
}

    for (j = 0; j < SPACER * 2 + 3 * MAXRINGS; j++) {
        printf("-");
    }

    printf("\n");
    printf("%*c%*c%*c\n\n", SPACER, 'A', SPACER, 'B', SPACER, 'C');
}


void
move(int n, stacks* stacka, stacks* stackb, stacks* stackc, int* moves) {
    usleep(DELAY);
    if (n == 1) {
        push(stackb, pop(stacka));
        printtowers(stacka, stackb, stackc, (*moves)++);
        return;
    }

    move(n - 1, stacka, stackc, stackb, moves);
    push(stackb, pop(stacka));
    printtowers(stacka, stackb, stackc, (*moves)++);
    move(n - 1, stackc, stackb, stacka, moves);
}


int
main() {
    int moves = 0;
    stacks stacka, stackb, stackc;

    initstack(&stacka);
    initstack(&stackb);
    initstack(&stackc);
    for (int i = MAXRINGS; i >= 1; i--) {
        push(&stacka, i);
    }

    printf("\033c");
    move(MAXRINGS, &stacka, &stackc, &stackb, &moves);
    printtowers(&stacka, &stackb, &stackc, moves);

    return 0;
}
