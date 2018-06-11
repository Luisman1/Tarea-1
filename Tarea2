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
#include <time.h>
#include <windows.h>
#include <process.h>
#define TERMINO 50000000000

typedef struct {
	signed long long inicio;
	signed long long fin;
	double suma;
	double sumaFinal;
}Rango;

DWORD WINAPI sumaPi (void *param);

int main(void) {
	short n;
	setvbuf(stdout, NULL, _IONBF, 0);
	printf("Hilos para calcular(1,2,4,8,16): ");
	scanf("%hi", &n);

	switch(n){
	case 1: ;
		Rango rango[]={{1,TERMINO,0}};
		HANDLE h1;
		clock_t inicio, fin;

		inicio= clock();
		h1=CreateThread(NULL, 0, sumaPi, (void *)&rango[0], 0, NULL);
		WaitForSingleObject(h1, INFINITE);
		fin=clock();
		int tiempo_final= 1000* (fin-inicio)/CLOCKS_PER_SEC;
		printf("Pi: %0.10lf \n", rango->suma);
		printf("Tiempo: %d ms\n", tiempo_final);

		break;

	case 2: ;
		Rango rango2[2];
		for (short i=1; i<=2; i++){
			long long m;
			m=TERMINO/2;
			if (i==1){
				rango2[i-1].inicio=1;
				rango2[i-1].fin=m;
				rango2[i-1].suma=0;
			}
			else{
				rango2[i-1].inicio=m+1;
				rango2[i-1].fin=m*i;
				rango2[i-1].suma=0;
			}
		}

		double temp=0;
		HANDLE h2,h3;
		clock_t inicio2, fin2;
		inicio2= clock();

		h2=CreateThread(NULL, 0, sumaPi, (void *)&rango2[0], 0, NULL);
		h3=CreateThread(NULL, 0, sumaPi, (void *)&rango2[1], 0, NULL);
		WaitForSingleObject(h2, INFINITE);
		WaitForSingleObject(h3, INFINITE);
		fin2=clock();

		int tiempo_final2= 1000* (fin2-inicio2)/CLOCKS_PER_SEC;

		for (short i=0; i<2; i++){
			temp+=rango2[i].sumaFinal;
		}

		printf("Pi: %0.10lf \n", temp);
		printf("Tiempo: %d ms\n", tiempo_final2);
		break;

	case 4: ;
		Rango rango3[4];
		for (short i=1; i<=4; i++){
			long long m;
			m=TERMINO/4;
			if (i==1){
				rango3[i-1].inicio=1;
				rango3[i-1].fin=m;
				rango3[i-1].suma=0;
			}
			else{
				rango3[i-1].inicio=m+1;
				rango3[i-1].fin=m*i;
				rango3[i-1].suma=0;
			}
		}
		double temp2=0;
		HANDLE h4,h5,h6,h7;
		clock_t inicio3, fin3;
		inicio3= clock();

		h4=CreateThread(NULL, 0, sumaPi, (void *)&rango3[0], 0, NULL);
		h5=CreateThread(NULL, 0, sumaPi, (void *)&rango3[1], 0, NULL);
		h6=CreateThread(NULL, 0, sumaPi, (void *)&rango3[2], 0, NULL);
		h7=CreateThread(NULL, 0, sumaPi, (void *)&rango3[3], 0, NULL);
		WaitForSingleObject(h4, INFINITE);
		WaitForSingleObject(h5, INFINITE);
		WaitForSingleObject(h6, INFINITE);
		WaitForSingleObject(h7, INFINITE);

		fin3=clock();
		int tiempo_final3= 1000* (fin3-inicio3)/CLOCKS_PER_SEC;

		for (short i=0; i<4; i++){
			temp2+=rango3[i].sumaFinal;
		}

		printf("Pi: %0.10lf \n",temp2);
		printf("Tiempo: %d ms\n", tiempo_final3);
		break;

	case 8: ;
		Rango rango4[8];
		for (short i=1; i<=8; i++){
			long long m;
			m=TERMINO/8;
			if (i==1){
				rango4[i-1].inicio=1;
				rango4[i-1].fin=m;
				rango4[i-1].suma=0;
			}
			else{
				rango4[i-1].inicio=m+1;
				rango4[i-1].fin=m*i;
				rango4[i-1].suma=0;
			}
		}
		double temp3=0;
		HANDLE h8,h9,h10,h11,h12,h13,h14,h15;
		clock_t inicio4, fin4;
		inicio4= clock();

		h8=CreateThread(NULL, 0, sumaPi, (void *)&rango4[0], 0, NULL);
		h9=CreateThread(NULL, 0, sumaPi, (void *)&rango4[1], 0, NULL);
		h10=CreateThread(NULL, 0, sumaPi, (void *)&rango4[2], 0, NULL);
		h11=CreateThread(NULL, 0, sumaPi, (void *)&rango4[3], 0, NULL);
		h12=CreateThread(NULL, 0, sumaPi, (void *)&rango4[4], 0, NULL);
		h13=CreateThread(NULL, 0, sumaPi, (void *)&rango4[5], 0, NULL);
		h14=CreateThread(NULL, 0, sumaPi, (void *)&rango4[6], 0, NULL);
		h15=CreateThread(NULL, 0, sumaPi, (void *)&rango4[7], 0, NULL);
		WaitForSingleObject(h8, INFINITE);
		WaitForSingleObject(h9, INFINITE);
		WaitForSingleObject(h10, INFINITE);
		WaitForSingleObject(h11, INFINITE);
		WaitForSingleObject(h12, INFINITE);
		WaitForSingleObject(h13, INFINITE);
		WaitForSingleObject(h14, INFINITE);
		WaitForSingleObject(h15, INFINITE);


		fin4=clock();
		int tiempo_final4= 1000* (fin4-inicio4)/CLOCKS_PER_SEC;

		for (short i=0; i<8; i++){
			temp3+=rango4[i].sumaFinal;
		}

		printf("Pi: %0.10lf \n",temp3);
		printf("Tiempo: %d ms\n", tiempo_final4);
		break;


	case 16: ;
		Rango rango5[16];
		for (short i=1; i<=16; i++){
			long long m;
			m=TERMINO/16;
			if (i==1){
				rango5[i-1].inicio=1;
				rango5[i-1].fin=m;
				rango5[i-1].suma=0;
			}
			else{
				rango5[i-1].inicio=m+1;
				rango5[i-1].fin=m*i;
				rango5[i-1].suma=0;
			}
		}
		double temp4=0;
		HANDLE h16,h17,h18,h19,h20,h21,h22,h23,h24,h25,h26,h27,h28,h29,h30,h31;
		clock_t inicio5, fin5;
		inicio5= clock();

		h16=CreateThread(NULL, 0, sumaPi, (void *)&rango5[0], 0, NULL);
		h17=CreateThread(NULL, 0, sumaPi, (void *)&rango5[1], 0, NULL);
		h18=CreateThread(NULL, 0, sumaPi, (void *)&rango5[2], 0, NULL);
		h19=CreateThread(NULL, 0, sumaPi, (void *)&rango5[3], 0, NULL);
		h20=CreateThread(NULL, 0, sumaPi, (void *)&rango5[4], 0, NULL);
		h21=CreateThread(NULL, 0, sumaPi, (void *)&rango5[5], 0, NULL);
		h22=CreateThread(NULL, 0, sumaPi, (void *)&rango5[6], 0, NULL);
		h23=CreateThread(NULL, 0, sumaPi, (void *)&rango5[7], 0, NULL);
		h24=CreateThread(NULL, 0, sumaPi, (void *)&rango5[8], 0, NULL);
		h25=CreateThread(NULL, 0, sumaPi, (void *)&rango5[9], 0, NULL);
		h26=CreateThread(NULL, 0, sumaPi, (void *)&rango5[10], 0, NULL);
		h27=CreateThread(NULL, 0, sumaPi, (void *)&rango5[11], 0, NULL);
		h28=CreateThread(NULL, 0, sumaPi, (void *)&rango5[12], 0, NULL);
		h29=CreateThread(NULL, 0, sumaPi, (void *)&rango5[13], 0, NULL);
		h30=CreateThread(NULL, 0, sumaPi, (void *)&rango5[14], 0, NULL);
		h31=CreateThread(NULL, 0, sumaPi, (void *)&rango5[15], 0, NULL);
		WaitForSingleObject(h16, INFINITE);
		WaitForSingleObject(h17, INFINITE);
		WaitForSingleObject(h18, INFINITE);
		WaitForSingleObject(h19, INFINITE);
		WaitForSingleObject(h20, INFINITE);
		WaitForSingleObject(h21, INFINITE);
		WaitForSingleObject(h22, INFINITE);
		WaitForSingleObject(h23, INFINITE);
		WaitForSingleObject(h24, INFINITE);
		WaitForSingleObject(h25, INFINITE);
		WaitForSingleObject(h26, INFINITE);
		WaitForSingleObject(h27, INFINITE);
		WaitForSingleObject(h28, INFINITE);
		WaitForSingleObject(h29, INFINITE);
		WaitForSingleObject(h30, INFINITE);
		WaitForSingleObject(h31, INFINITE);


		fin5=clock();
		int tiempo_final5= 1000* (fin5-inicio5)/CLOCKS_PER_SEC;

		for (short i=0; i<16; i++){
			temp4+=rango5[i].sumaFinal;
		}

		printf("Pi: %0.10lf \n",temp4);
		printf("Tiempo: %d ms\n", tiempo_final5);
		break;

	default:
		printf("Cantidad incorrecta. Intente de nuevo");
		break;
	}
	return EXIT_SUCCESS;
}


DWORD WINAPI sumaPi (void *param){
	Rango *aR=(Rango*)param;
	long long i;

	for(i=aR->inicio; i<=aR->fin; i++)
		if (i%2==0){
			aR->suma-= (float)4/(2*i-1);
		}
		else{
			aR->suma+= (float)4/(2*i-1);
		}
	aR->sumaFinal=aR->suma;

	return 0;
}
