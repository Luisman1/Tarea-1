/*
 ============================================================================
 Name        : Tarea.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <ctype.h>
#include <assert.h>


void crearStack();
int push(char Elem);
int pop(char *Elem);
int aridadOp(char Exp[], int position);
int prioridadOp(char Operator);
void compactarF(char Descomp[], char Compac[]);
int cambiarExp(char exp[], char exp_pos[]);

#define MAX 100
char stack[MAX];
int top;

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
    char Exp[MAX];
    char Exp_compactarF[MAX] = {0};
    char Exp_pos[MAX] = {0};

    printf("Introduce la expresion: \n");
    fgets(Exp, MAX, stdin);
    compactarF(Exp, Exp_compactarF);

    cambiarExp(Exp_compactarF, Exp_pos);
    printf("Expresion postfija: ");
    puts(Exp_pos);
    return 0;
}

void crearStack() {
    top = -1;
}

int push(char Elem) {
    if (top == MAX - 1)
        return -1;
    stack[++top] = Elem;
    return 0;
}

int pop(char *Elem) {
    if (top == -1)
        return -1;
    *Elem = stack[top--];
    return 0;
}

int aridadOp(char Exp[], int position) {
    if ( prioridadOp(Exp[position]) == 1 ) {
        if ( (position == 0) ||
             ((prioridadOp(Exp[position - 1]) >= 1) &&
              (prioridadOp(Exp[position - 1]) <= 3)) ) {
            return 1;
        } else {
            return 2;
        }
    } else if ( (prioridadOp(Exp[position]) > 1) &&
                (prioridadOp(Exp[position]) <= 3) ) {
        return 2;
    } else {
        return prioridadOp(Exp[position]);
    }
}

int prioridadOp(char Operator) {
    switch (Operator) {
        case '+':
            return 1;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 2;
        case '^':
            return 3;
        case '(':
            return 4;
        case ')':
            return 5;
        default:
            return 0;
    }
}

void compactarF(char Descomp[], char Compac[]) {
    int i = 0;
    int j = 0;

    while ( Descomp[j] ) {
        if ( !isspace(Descomp[j]) ) {
            Compac[i++] = Descomp[j];
        }
        j++;
    }
}

int cambiarExp(char exp[], char exp_pos[]) {
    int i = 0, j = 0, ind = 0;
    char trash = ' ';

    crearStack();

    while ( exp[i] ) {
        if ( aridadOp(exp, i) == 0 ) {
            exp_pos[j++] = exp[i];
        } else if ( aridadOp(exp, i) == 1 ) {
            switch (exp[i]) {
                case '-':
                    exp_pos[j++] = exp[i];
                    break;
                case '+':
                    trash = exp_pos[i];
                    break;
                default:
                    assert(0);
            }
        } else if (aridadOp(exp, i) == 2) {
            while ( (top != -1) &&
                    (prioridadOp(stack[top]) >= prioridadOp(exp[i])) &&
                    stack[top] != '(' ) {
                ind = pop(&exp_pos[j++]);
            }
            ind = push(exp[i]);
        } else if ( prioridadOp(exp[i]) == 4 ) {
            ind = push(exp[i]);
        } else if ( prioridadOp(exp[i]) == 5 ) {
            while ( (top != -1) && (stack[top] != '(') ) {
                ind = pop(&exp_pos[j++]);
            }
            if ( (top != - 1) && stack[top] == '(') {
                ind = pop(&trash);
            }
        }
        i++;
    }

    while (top != -1) {
        ind = pop(&exp_pos[j++]);
    }

    return ind;
}
