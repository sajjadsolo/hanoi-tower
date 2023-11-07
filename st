#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#define DELAY 290000
#define MAXRINGS 6
#define SPACER 6

typedef struct {
    int stack[MAXRINGS];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

bool isStackEmpty(Stack* s) {
    return (s->top == -1);
}

bool isStackFull(Stack* s) {
    return (s->top == MAXRINGS - 1);
}

void push(Stack* s, int value) {
    if (isStackFull(s)) {
        printf("Stack overflow\n");
        return;
    }

    // Find the index where the big number should be inserted
    int index = s->top + 1;
    while (index > 0 && s->stack[index - 1] > value) {
        s->stack[index] = s->stack[index - 1];
        index--;
    }

    s->stack[index] = value;
    s->top++;
}

int pop(Stack* s) {
    if (isStackEmpty(s)) {
        printf("Stack underflow\n");
        return -1;
    }

    return s->stack[s->top--];
}

int getTop(Stack* s) {
    if (isStackEmpty(s)) {
        printf("Stack is empty\n");
        return -1;
    }

    return s->stack[s->top];
}

void printStack(Stack* s) {
    Stack tempStack;
    initStack(&tempStack);

    while (!isStackEmpty(s)) {
        int value = pop(s);
        printf("%*d\n", SPACER, value);
        push(&tempStack, value);
    }

    while (!isStackEmpty(&tempStack)) {
        push(s, pop(&tempStack));
    }
}

void printtowers(Stack* stackA, Stack* stackB, Stack* stackC, int moves) {
    int j;
    int i = MAXRINGS;

    moves++;
    printf("\033[%dAMove: %d\n", MAXRINGS + 7, moves);

    while (i > 0) {
        int cella = (i <= stackA->top + 1) ? stackA->stack[stackA->top - i + 1] : 0;
        int cellb = (i <= stackB->top + 1) ? stackB->stack[stackB->top - i + 1] : 0;
        int cellc = (i <= stackC->top + 1) ? stackC->stack[stackC->top - i + 1] : 0;

        printf("%*d%*d%*d\n", SPACER, cella, SPACER, cellb, SPACER, cellc);
        i--;
    }

    for (j = 0; j < SPACER * 2 + 3 * MAXRINGS; j++) {
        printf("-");
    }

    printf("\n");
    printf("%*c%*c%*c\n\n", SPACER, 'A', SPACER, 'B', SPACER, 'C');
}

void move(int n, Stack* stackA, Stack* stackB, Stack* stackC, int* moves) {
    usleep(DELAY);
    if (n == 1) {
        push(stackB, pop(stackA));
        printtowers(stackA, stackB, stackC, (*moves)++);
        return;
    }

    move(n - 1, stackA, stackC, stackB, moves);
    push(stackB, pop(stackA));
    printtowers(stackA, stackB, stackC, (*moves)++);
    move(n - 1, stackC, stackB, stackA, moves);
}

int main() {
    Stack stackA, stackB, stackC;
    int moves = 0;

    initStack(&stackA);
    initStack(&stackB);
    initStack(&stackC);

    for (int i = MAXRINGS; i >= 1; i--) {
        push(&stackA, i);
    }

    printf("\033c");
    move(MAXRINGS, &stackA, &stackC, &stackB, &moves);
    printtowers(&stackA, &stackB, &stackC, moves);

    return 0;
}
