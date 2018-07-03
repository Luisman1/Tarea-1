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
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include "Stack.h"
#include "Queue.h"

void compactar(char Descomp[], char Compac[]);
int opPrioridad(char Operator);
int aridad(char Exp[], int position);
Boolean cambiarExp(char exp[], char exp_pos[]);

#define MAX 50
char stack[MAX];

int main(void) {
    char Exp[MAX];
    char Exp_compacta[MAX] = {0};
    char Exp_pos[MAX] = {0};


    printf("Escribe la expresion: ");
    gets(Exp);
    compactar(Exp, Exp_compacta);

    cambiarExp(Exp_compacta, Exp_pos);
    puts(Exp_pos);
    return 0;
}

void compactar(char Descomp[], char Compac[]) {
    int i = 0;
    int j = 0;

    while ( Descomp[j] ) {
        if ( !isspace(Descomp[j]) ) {
            Compac[i++] = Descomp[j];
        }
        j++;
    }
}

int opPrioridad(char Op) {
    switch (Op) {
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

int aridad(char Exp[], int pos) {
    if ( opPrioridad(Exp[pos]) == 1 ) {
        if ( (pos == 0) ||
             ((opPrioridad(Exp[pos - 1]) >= 1) &&
              (opPrioridad(Exp[pos - 1]) <= 3)) ) {
            return 1;
        } else {
            return 2;
        }
    } else if ( (opPrioridad(Exp[pos]) > 1) &&
                (opPrioridad(Exp[pos]) <= 3) ) {
        return 2;
    } else {
        return opPrioridad(Exp[pos]);
    }
}

Boolean cambiarExp(char exp[], char exp_pos[]) {
    int i = 0, j = 0;
    char trash = ' ';
    char temp;
    Stack s1;

    s1=createStack();

    while ( exp[i] ) {
    	temp=*((char*)top(s1));
        if ( aridad(exp, i) == 0 ) {
            exp_pos[j++] = exp[i];
        }
        else if ( aridad(exp, i) == 1 ) {
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
        } else if (aridad(exp, i) == 2) {
            while ( (isEmpty(s1)!=true) &&
                    (opPrioridad(temp) >= opPrioridad(exp[i])) &&
                    temp != '(' ) {
            	pop(s1);
            }
           push(s1, &exp[i]);
        } else if ( opPrioridad(exp[i]) == 4 ) {
            push(s1, &exp[i]);
        } else if ( opPrioridad(exp[i]) == 5 ) {
            while ( (isEmpty(s1)!=true) && (temp != '(') ) {
                pop(s1);
            }
            if ( (isEmpty(s1)!=true) && temp == '(') {
                pop(s1);
            }
        }
        i++;
    }

    while (isEmpty(s1)!=true) {
        pop(s1);
    }

    return true;
}
