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
#include <string.h>

typedef struct{
	char nombre[15];
	float calificacion;
} Profesor;

//float averageArray(Profesor *lista, int n);
void readArray(Profesor *lista, int n);
void mergeArrays (Profesor *lista1, int n1, Profesor *lista2, int n2, Profesor *listaf, int n3);
void sortArray(Profesor *lista, int n);
void printArray(Profesor *lista, int n );


void main(){
	Profesor arr1[20];  //Primer arreglo
	Profesor arr2[20];  //Segundo arreglo
	Profesor arrF[40];  //Arreglo final, con elementos fusionados y ordenados
	int n1, n2, n3; //Longitud de los arreglos

	scanf("%d", &n1);
	readArray(arr1, n1); //leer el primer arreglo
	scanf("%d", &n2);
	readArray(arr2, n2); //leer el segundo arreglo
	n3=n1+n2;
	mergeArrays(arr1, n1, arr2, n2, arrF, n3);  //Fusionar los dos arreglos en un tercer arreglo

	sortArray(arrF, n3);  //Ordenar los elementos del tercer arreglo, recuerde que pueden
	//existir profesores repetidos

	printArray(arrF, n3);   //Imprimir el resultado final

}

void readArray (Profesor *lista, int n){
	short i;

	for (i=0; i<n ; i++){
		scanf("%s",lista[i].nombre);
		scanf("%f", &lista[i].calificacion);
	}
}

void mergeArrays (Profesor *lista1, int n1, Profesor *lista2, int n2, Profesor *listaf, int n3){
	short i, j;

	for (i=0; i<n1; i++){
		strcpy(listaf[i].nombre, lista1[i].nombre);
		listaf[i].calificacion=lista1[i].calificacion;
	}
	j=i;
	for (i=0; i<n2; i++, j++){
		strcpy(listaf[j].nombre, lista2[i].nombre);
		listaf[j].calificacion=lista2[i].calificacion;
	}

}

/*void avarageArray (Profesor *lista, int *n){
	short i, j, ntemp;
	char temp[*n], repetir=0, repetir2=0;
	float ctemp;

	ntemp=*n;
	for (i=0; i<*n ; i++){
		for (j=i; j<*n; j++){
			if (strcmp(lista[i].nombre, lista[j].nombre)){
				temp[j]=1;
				repetir++;
			}
		}

		if (repetir){
			repetir2=repetir;
			ctemp=lista[i].calificacion;
			for (j=i; repetir>0; j++){
				if (temp[j]==1){
					ctemp+=lista[j].calificacion;
					lista[j]=lista[j+1];
					*n =*n-1;
				}
			}
			lista[i].calificacion=ctemp/repetir2;
			for (j=0; j<ntemp; j++){
				temp[j]=0;
			}
		}
	}
}
*/


void sortArray (Profesor *lista, int n){
	Profesor temp;
	short i, j;
	for(i=0; i<n; i++){
		for (j=i+1; j<n; j++){
			if (lista[i].calificacion<lista[j].calificacion){
				temp=lista[i];
				lista[i]=lista[j];
				lista[j]=temp;
			}
		}
	}
	//avarageArray(lista,&n);
}

void printArray (Profesor *lista, int n){
	short i;
	for(i=0; i<n; i++){
		printf("%s %0.1f\n",lista[i].nombre, lista[i].calificacion);
	}
}
