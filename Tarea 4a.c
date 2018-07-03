/*
 ============================================================================
 Name        : Tarea.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"
#include <string.h>

#define MAX 50

Boolean balancedBrackets(char *);

int main(void){
	setvbuf(stdout, NULL, _IONBF, 0);
	char exp[MAX];

	printf("Introduzca su expresion: \n");
	gets(exp);

	if(balancedBrackets(exp)==true)
		printf("---La ecuacion esta bien balanceada---");
	else
		printf("---Error. La ecuacion esta mal balanceada---\n");

	return 0;
}

Boolean balancedBrackets(char *exp){
	short len, cont=0;
	len=strlen(exp);
	Stack s1=createStack();
	char temp;

	for (short i=0; i<len; i++){
		if (exp[i]=='(' || exp[i]=='['){
			push(s1, &exp[i]);
			cont++;
		}

		else if (exp[i]==')'){
			if (isEmpty(s1)!=true){
				temp=*((char*)top(s1));
				if (temp=='(')
					pop(s1);
				else
					return false;
			}
			else
				return false;
		}
		else if (exp[i]==']'){
			if (isEmpty(s1)!=true){
				temp=*((char*)top(s1));
				if (temp=='[')
					pop(s1);
				else
					return false;
			}
			else
				return false;
		}
	}
	if (isEmpty(s1)==true)
		return true;
	else
		return false;
}
