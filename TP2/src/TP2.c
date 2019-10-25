/*
 ============================================================================
 Name        : TP2.c
 Author      : Kaba Saran
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "tp1.h"

#define SIZE 4

int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */

	float f[SIZE];
	float m[SIZE];

	f[0]= 0;
	f[1]= 0;
	f[2]= 2.36;
	f[3]= 3716.36;

	m[0]= 1;
	m[1]= 1;
	m[2]= 2.36;
	m[3]= 3716.36;

	printf("%f\n",photometrie_ouverture(f,m,SIZE));

	return EXIT_SUCCESS;
}
