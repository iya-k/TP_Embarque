/*
 ============================================================================
 Name        : TP3.c
 Author      : Kaba_Gaudre
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <asm-leon/irq.h>
#include <asm-leon/timer.h>
#include "fonctions.h"

#define REGISTER 	0x80000204

volatile uint32_t* registre = (uint32_t*)REGISTER;


int main(void) {
	puts("!!!MODIFICATION DES REGISTRES!!!"); /* prints !!!MODIFICATION DES REGISTRES!!! */


	printf("Avant REGISTER = %08X\n",registre);

	test_zero(REGISTER, 1);

	printf("Apres 0 REGISTER = %08X\n",registre);

	return EXIT_SUCCESS;
}
