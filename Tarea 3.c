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
#include <time.h>

typedef enum{true, false}Boolean;
typedef enum{deposit=1, withdraw, transfer}Operation;
#define MAX 100

typedef struct{
	short Dia;
	short Mes;
	short Anio;
}FdN;

typedef struct{
	int Id_usuario;
	char Nombre[20];
	char apellidoPaterno[20];
	char apellidoMaterno[20];
	FdN	DoB;
}Usuario;

typedef struct{
	int Id_usuario;
	int Id_cuenta;
	long int Saldo;
	FdN FdA;
}Cuenta;

typedef struct{
	int Id_trans;
	Operation Op;
	int Id_Cuenta_Origen;
	int Id_Cuenta_Destino;
	FdN FdT;
	long int Monto;
}Trans;

void Menu_Principal();

Boolean Menu_Clientes();
Usuario *Crear_Cliente(Usuario*);
Usuario Buscar_Cliente(int);
Boolean Eliminar_Cliente();
Boolean Imprimir_Clientes();

Boolean Menu_Cuentas();
Cuenta *Nueva_Cuenta(Cuenta*);
Cuenta Buscar_Cuenta(int);
Boolean Eliminar_Cuenta(int);
Boolean Imprimir_Cuentas();

Boolean Menu_Transacciones();
Trans *Trans_Deposito(Trans*);
Trans *Trans_Retiro(Trans*);
Trans *Trans_Transferencia(Trans*);
Boolean Imprimir_Transferencias();

void First_Setup();
int size_struct(FILE *aF, int n);

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	FILE *Route;

	Route=fopen("mydb.sys", "r");
	if (Route==NULL)
		First_Setup();
	fclose(Route);

	Menu_Principal();


	return EXIT_SUCCESS;
}

void Menu_Principal(){
	short opcion;

	do{
		printf("\n<< Sistema MyDB >>\n");
		printf("[1] Clientes \n");
		printf("[2] Cuentas \n");
		printf("[3] Transacciones \n");
		printf("[4] Salir \n");
		scanf("%hi", &opcion);

		switch (opcion){
		case 1:
			Menu_Clientes();
			break;

		case 2:
			Menu_Cuentas();
			break;

		case 3:
			Menu_Transacciones();
			break;

		}
	}while (opcion!=4);
}

Boolean Menu_Clientes(){
	short opcion, id;
	Usuario *temp;
	Usuario tempU;

	do{
		printf("<< Menu Clientes >>\n");
		printf("1. Nuevo Cliente\n");
		printf("2. Buscar Cliente\n");
		printf("3. Eliminar Cliente \n");
		printf("4. Imprimir Clientes \n");
		printf("5. <--- \n");
		scanf("%hi", &opcion);

		switch (opcion){
		case 1:
			Crear_Cliente(temp);
			break;

		case 2:
			printf("Numero de ID del Usuario: ");
			scanf("%hi", &id);
			tempU=Buscar_Cliente(id);
			printf("ID_Usuario     Nombre(s)     Apellido Paterno     Apellido Materno     Fecha de Nacimiento\n");
			printf("%-15d%-15s%-21s%-21s%hi/%hi/%hi\n", tempU.Id_usuario, tempU.Nombre, tempU.apellidoPaterno, tempU.apellidoMaterno, tempU.DoB.Dia,tempU.DoB.Mes,tempU.DoB.Anio);

			break;

		case 3:
			printf("Numero de ID del Usuario: ");
			scanf("%hi", &id);
			Eliminar_Cliente(id);
			break;

		case 4:
			Imprimir_Clientes();
			break;
		}
	}while (opcion!=5);

	return true;
}

Usuario *Crear_Cliente(Usuario *quien){
	int nReg, index;
	FILE *aux;
	char aux_r[MAX];
	aux=fopen("mydb.sys", "r");
	fgets(aux_r, MAX, aux);
	fclose(aux);

	strcat(aux_r, "\\clientes.dat");
	aux=fopen(aux_r, "ab");
	if (aux==NULL)
		puts("Error al abrir archivo Clientes");

	nReg=size_struct(aux, 1);
	if (nReg==0)
		index=1;
	else if(nReg!=0)
		index=nReg+1;
	rewind(aux);

	quien=(Usuario*)malloc(sizeof(Usuario));
	if (quien!=NULL){

		quien->Id_usuario=index;

		puts("Introduzca el Nombre del nuevo cliente: ");
		scanf("%s", quien->Nombre);

		puts("Introduzca el Apellido Paterno del nuevo cliente: ");
		scanf("%s", quien->apellidoPaterno);

		puts("Introduzca el Apellido Materno del nuevo cliente: ");
		scanf("%s", quien->apellidoMaterno);

		puts("Introduzca la Fecha de Nacimiento (dd/mm/aaaa): ");
		scanf("%hi/%hi/%hi", &quien->DoB.Dia, &quien->DoB.Mes, &quien->DoB.Anio);
		fflush(stdin);
	}

	fwrite(quien,sizeof(Usuario),1,aux);
	fclose(aux);

	return quien;
}

Usuario Buscar_Cliente(int n){
	FILE *aux;
	Usuario temp;
	char r_aux[MAX];

	aux=fopen("mydb.sys", "r+");
	if (aux==NULL)
		puts("Error abriendo el archivo de Ruta");
	fgets(r_aux, MAX, aux);
	fclose (aux);

	strcat(r_aux, "\\clientes.dat");
	aux=fopen(r_aux, "rb");
	if(aux==NULL)
		puts("Error abriendo el archivo de Clientes");

	fseek(aux, (n-1)*sizeof(Usuario), SEEK_SET);
	fread(&temp, sizeof(Usuario),1, aux);

	fclose(aux);
	return temp;
}

Boolean Eliminar_Cliente(int n){

}

Boolean Imprimir_Clientes(){
	FILE *aux;
	Usuario temp;
	int nReg;
	char aux_r[MAX];

	aux=fopen("mydb.sys", "r+");
	if (aux==NULL)
		puts("Error abriendo el archivo de Ruta");
	fgets(aux_r, MAX, aux);
	fclose (aux);

	strcat(aux_r, "\\clientes.dat");
	aux=fopen(aux_r, "rb");
	if(aux==NULL)
		puts("Error abriendo el archivo de Clientes");

	nReg=size_struct(aux, 1);
	printf("ID_Usuario     Nombre(s)     Apellido Paterno     Apellido Materno     Fecha de Nacimiento\n");

	for (short i=0; i<nReg; i++){
		fread(&temp, sizeof(Usuario),1, aux);
		printf("%-15d%-14s%-21s%-21s%hi/%hi/%hi\n", temp.Id_usuario, temp.Nombre, temp.apellidoPaterno, temp.apellidoMaterno, temp.DoB.Dia,temp.DoB.Mes,temp.DoB.Anio);
	}
	fclose(aux);
	printf("\n");
	return true;
}

Boolean Menu_Cuentas(){
	short opcion, id;
	Cuenta *temp, tempC;
	Usuario tempU;

	do{
		printf("<< Menu Cuentas >>\n");
		printf("1. Nueva Cuenta\n");
		printf("2. Buscar Cuenta\n");
		printf("3. Eliminar Cuenta \n");
		printf("4. Imprimir Cuentas \n");
		printf("5. <---\n");
		scanf("%hi", &opcion);

		switch (opcion){
		case 1:
			Nueva_Cuenta(temp);
			break;

		case 2:
			printf("Numero de ID de la Cuenta: ");
			scanf("%hi", &id);
			tempC=Buscar_Cuenta(id);
			tempU=Buscar_Cliente(tempC.Id_usuario);

			printf("ID_Cuenta     Nombre(s)     Saldo\n");
			printf("%-14d%-14s%li\n", tempC.Id_cuenta, tempU.Nombre, tempC.Saldo);
			break;

		case 3:
			printf("Numero de ID de la Cuenta a Eliminar: ");
			scanf("%hi", &id);
			Eliminar_Cuenta(id);
			break;

		case 4:
			Imprimir_Cuentas();
			break;
		}

	}while (opcion!=5);

	return true;
}

Cuenta *Nueva_Cuenta(Cuenta *cual){
	FILE *aux;
	Usuario tempU;
	char aux_r[MAX];
	int nReg, index, ID;

	aux=fopen("mydb.sys", "r");
	if (aux==NULL)
		puts("Error abriendo el archivo de Ruta");
	fgets(aux_r, MAX, aux);
	fclose (aux);

	strcat(aux_r, "\\cuentas.dat");
	aux=fopen(aux_r, "ab");
	if (aux==NULL)
		puts("Error abriendo el archivo de Cuentas");


	printf("Ingrese el ID del cliente a crear la cuenta: ");
	scanf("%d", &ID);

	nReg=size_struct(aux, 2);
	if (nReg==0)
		index=1;
	else if(nReg!=0)
		index=nReg+1;

	tempU=Buscar_Cliente(ID);

	cual=(Cuenta*)malloc(sizeof(Cuenta));
	if (cual!=NULL){
		cual->Id_cuenta=index;
		cual->Id_usuario=tempU.Id_usuario;

		puts("Ingrese el Saldo inicial: ");
		scanf("%li", &cual->Saldo);

		puts("Ingrese la Fecha de creación (dd/mm/aaaa): ");
		scanf("%hi/%hi/%hi", &cual->FdA.Dia, &cual->FdA.Mes, &cual->FdA.Anio);
		fflush(stdin);
		}
	fwrite(cual, sizeof(Cuenta),1, aux);
	fclose(aux);
	return cual;
}

Cuenta Buscar_Cuenta(int n){
	FILE *aux;
	Cuenta tempC;
	char r_aux[MAX];

	aux=fopen("mydb.sys", "r+");
	if (aux==NULL)
		puts("Error abriendo el archivo de Ruta");
	fgets(r_aux, MAX, aux);
	fclose (aux);

	strcat(r_aux, "\\cuentas.dat");
	aux=fopen(r_aux, "rb");
	if(aux==NULL)
		puts("Error abriendo el archivo de Cuentas");

	fseek(aux, (n-1)*sizeof(Cuenta), SEEK_SET);
	fread(&tempC, sizeof(Cuenta),1, aux);

	fclose(aux);
	return tempC;
}

Boolean Eliminar_Cuenta(int n){
	//FILE *aux;
	//Cuenta tempC;

	//tempC=1;

	return true;
}

Boolean Imprimir_Cuentas(){
	FILE *aux;
	Cuenta tempC;
	Usuario tempU;
	int nReg;
	char aux_r[MAX];

	aux=fopen("mydb.sys", "r+");
	if (aux==NULL)
		puts("Error abriendo el archivo de Ruta");
	fgets(aux_r, MAX, aux);
	fclose (aux);

	strcat(aux_r, "\\cuentas.dat");
	aux=fopen(aux_r, "rb");
	if(aux==NULL)
		puts("Error abriendo el archivo de Clientes");

	nReg=size_struct(aux, 2);

	printf("ID_Cuenta     Nombre(s)     Saldo\n");

	for (short i=0; i<nReg; i++){
		tempC=Buscar_Cuenta(i+1);
		tempU=Buscar_Cliente(tempC.Id_usuario);
		printf("%-14d%-14s%li\n", tempC.Id_cuenta, tempU.Nombre, tempC.Saldo);
	}
	fclose(aux);
	return true;
}

Boolean Menu_Transacciones(){
	short opcion;
	Trans *tempT;
	do{
		printf("<< Menu Transacciones >>\n");
		printf("1. Deposito\n");
		printf("2. Retiro\n");
		printf("3. Transferencia \n");
		printf("4. Imprimir Transferencias\n");
		printf("5. <---\n");

		scanf("%hi", &opcion);

		switch (opcion){
		case 1:
			Trans_Deposito(tempT);
			break;

		case 2:
			Trans_Retiro(tempT);
			break;

		case 3:
			Trans_Transferencia(tempT);
			break;

		case 4:
			Imprimir_Transferencias();
			break;
		}
	}while(opcion!=5);

	return true;
}

Trans *Trans_Deposito(Trans *que){
	FILE *aux, *aux2;
	char aux_r[MAX], aux_r2[MAX];
	int nReg, index, ID, monto;
	Cuenta tempC;

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	aux=fopen("mydb.sys", "r+");
	if (aux==NULL)
		puts("Error abriendo el archivo de Ruta");
	fgets(aux_r, MAX, aux);
	rewind(aux);
	fgets(aux_r2, MAX, aux);
	fclose (aux);

	strcat(aux_r, "\\transacciones.dat");
	aux=fopen(aux_r, "ab");
	if(aux==NULL)
		puts("Error abriendo el archivo de Transacciones");

	nReg=size_struct(aux, 3);
	if (nReg==0)
		index=1;
	else if(nReg!=0)
		index=nReg+1;



	que=(Trans*)malloc(sizeof(Trans));
	if (que!=NULL){
	printf("ID de la cuenta a hacer el Deposito: ");
	scanf("%d", &ID);
	que->Id_Cuenta_Destino=ID;

	tempC=Buscar_Cuenta(ID);

	strcat(aux_r2, "\\cuentas.dat");
	aux2=fopen(aux_r2, "ab+");
	if (aux2==NULL)
		printf("Error abriendo el archivo de Cuentas\n");

	printf("Monto a Depositar: ");
	scanf("%d", &monto);

	fseek(aux2, (ID-1)*sizeof(Trans), SEEK_SET);

	que->Monto=monto;
	tempC.Saldo+=monto;
	fwrite(&tempC, sizeof(Cuenta),1, aux2);
	fclose(aux2);


	que->Id_Cuenta_Origen=0;
	que->Op=deposit;
	que->Id_trans=index;
	que->FdT.Dia=tm.tm_mday;
	que->FdT.Mes=tm.tm_mon;
	que->FdT.Anio=tm.tm_year;
	}

	fwrite(que, sizeof(Trans),1, aux);
	fclose(aux);

	return que;
}

Trans *Trans_Retiro(Trans* que){
	FILE *aux, *aux2;
	char aux_r[MAX],aux_r2[MAX];
	int nReg, index, monto, ID;
	Cuenta tempC;

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	aux=fopen("mydb.sys", "r+");
	if (aux==NULL)
		puts("Error abriendo el archivo de Ruta");
	fgets(aux_r, MAX, aux);
	rewind(aux);
	fgets(aux_r2, MAX, aux);
	fclose (aux);

	strcat(aux_r, "\\transacciones.dat");
	aux=fopen(aux_r, "ab");
	if(aux==NULL)
		puts("Error abriendo el archivo de Transacciones");

	nReg=size_struct(aux, 3);
	if (nReg==0)
		index=1;
	else if(nReg!=0)
		index=nReg+1;

	que=(Trans*)malloc(sizeof(Trans));
	if (que!=NULL){
		printf("ID de la cuenta a hacer el Retiro: ");
		scanf("%d", &ID);
		que->Id_Cuenta_Origen=ID;

		tempC=Buscar_Cuenta(ID);

		strcat(aux_r2, "\\cuentas.dat");
		aux2=fopen(aux_r2, "ab");
		if (aux2==NULL)
			printf("Error abriendo el archivo de Cuentas\n");

		printf("Monto a Retirar: ");
		scanf("%d", &monto);
		if(monto>tempC.Saldo){
			printf("-La cantidad a retirar es mayor al saldo-\n");
			return NULL;
		}
		fseek(aux2, (ID-1)*sizeof(Trans), SEEK_SET);
		que->Monto=monto;
		tempC.Saldo-=monto;
		fwrite(&tempC, sizeof(Cuenta),1, aux2);
		fclose(aux2);


	que->Id_Cuenta_Destino=0;
	que->Op=withdraw;
	que->Id_trans=index;
	que->FdT.Dia=tm.tm_mday;
	que->FdT.Mes=tm.tm_mon;
	que->FdT.Anio=tm.tm_year;
	}

	fwrite(que, sizeof(Trans),1, aux);
	fclose(aux);

	return que;
}

Trans *Trans_Transferencia(Trans* que){
	FILE *aux, *aux2;
	char aux_r[MAX],aux_r2[MAX];
	int nReg, index, monto, ID, ID2;
	Cuenta tempC, tempC2;

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	aux=fopen("mydb.sys", "r+");
	if (aux==NULL)
		puts("Error abriendo el archivo de Ruta");
	fgets(aux_r, MAX, aux);
	rewind(aux);
	fgets(aux_r2, MAX, aux);
	fclose (aux);

	strcat(aux_r, "\\transacciones.dat");
	aux=fopen(aux_r, "ab");
	if(aux==NULL)
		puts("Error abriendo el archivo de Transacciones");

	nReg=size_struct(aux, 3);
	if (nReg==0)
		index=1;
	else if(nReg!=0)
		index=nReg+1;

	que=(Trans*)malloc(sizeof(Trans));
	if (que!=NULL){
		printf("ID de la cuenta Origen a hacer la Transferencia: ");
		scanf("%d", &ID);
		que->Id_Cuenta_Origen=ID;

		printf("ID de la cuenta Destino a hacer la Transferencia: ");
		scanf("%d", &ID2);
		que->Id_Cuenta_Destino=ID2;

		tempC=Buscar_Cuenta(ID);
		tempC2=Buscar_Cuenta(ID2);

		strcat(aux_r2, "\\cuentas.dat");
		aux2=fopen(aux_r2, "ab");
		if (aux2==NULL)
			printf("Error abriendo el archivo de Cuentas\n");

		printf("Monto a Transferir: ");
		scanf("%d", &monto);
		if(monto>tempC.Saldo){
			printf("-La cantidad a transferir es mayor al saldo-\n");
			return NULL;
		}
		fseek(aux2, (ID-1)*sizeof(Trans), SEEK_SET);
		que->Monto=monto;
		tempC.Saldo-=monto;
		tempC2.Saldo+=monto;
		fwrite(&tempC, sizeof(Cuenta),1, aux2);
		fwrite(&tempC2, sizeof(Cuenta),1, aux2);
		fclose(aux2);

	que->Op=transfer;
	que->Id_trans=index;
	que->FdT.Dia=tm.tm_mday;
	que->FdT.Mes=tm.tm_mon;
	que->FdT.Anio=tm.tm_year;
	fflush(stdin);
	}

	fwrite(que, sizeof(Trans),1, aux);
	fclose(aux);

	return que;
}

Boolean Imprimir_Transferencias(){
	FILE *aux;
	Trans temp;
	int nReg;
	char aux_r[MAX], *aux_op;

	aux=fopen("mydb.sys", "r+");
	if (aux==NULL)
		puts("Error abriendo el archivo de Ruta");
	fgets(aux_r, MAX, aux);
	fclose (aux);

	strcat(aux_r, "\\transacciones.dat");
	aux=fopen(aux_r, "rb");
	if(aux==NULL)
		puts("Error abriendo el archivo de Transacciones");

	nReg=size_struct(aux, 3);
	printf("ID_Transaccion     Tipo de Transaccion     ID Cuenta Origen     ID Cuenta Destino     Fecha de Transaccion     Monto de la Transaccion\n");

	for (short i=0; i<nReg; i++){
		fread(&temp, sizeof(Usuario),1, aux);

		switch (temp.Op){
		case 1:
			aux_op="Deposito";
			break;
		case 2:
			aux_op="Retiro";
			break;
		case 3:
			aux_op="Transferencia";
			break;
		}
		printf("%-19d%-24s%-21d%-22d%hi/%hi/%-20hi%li\n", temp.Id_trans, aux_op, temp.Id_Cuenta_Origen, temp.Id_Cuenta_Destino, temp.FdT.Dia,(temp.FdT.Mes)+1,(temp.FdT.Anio)+1900, temp.Monto);
	}
	fclose(aux);

	return true;
}

void First_Setup(){
	FILE *Ruta, *Aux;
	char ruta[MAX], temp[MAX];

	puts("---Bienvenido al sistema MyDB---");
 	printf("Ingrese la ruta de acceso a los archivos: ");
	gets(ruta);

	Ruta=fopen("mydb.sys", "a+");
	if(Ruta!=NULL)
		fputs(ruta, Ruta);

	for (short i=0; i<3; i++){
		rewind(Ruta);
		fgets(temp, MAX, Ruta);
		switch(i){
		case 0:
			strcat(temp,"\\clientes.dat");
			Aux=fopen(temp, "wb");
			fclose(Aux);
			break;
		case 1:
			strcat(temp,"\\cuentas.dat");
			Aux=fopen(temp, "wb");
			fclose(Aux);
			break;
		case 2:
			strcat(temp,"\\transacciones.dat");
			Aux=fopen(temp, "wb");
			fclose(Aux);
			break;
		}
	}
	fclose(Ruta);
}

int size_struct(FILE *aF, int n){
	int bytes;
	switch (n){
	case 1:
		fseek(aF, 0, SEEK_END);
		bytes=ftell(aF)/sizeof(Usuario);
		rewind(aF);
		break;

	case 2:
		fseek(aF, 0, SEEK_END);
		bytes=ftell(aF)/sizeof(Cuenta);
		rewind(aF);
		break;

	case 3:
		fseek(aF, 0, SEEK_END);
		bytes=ftell(aF)/sizeof(Trans);
		rewind(aF);
		break;
	}
	return bytes;
}
