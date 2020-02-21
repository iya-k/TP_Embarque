/*
 * fonctions.c
 *
 *  Created on: 15 nov. 2019
 *      Author: KABA_GAUDRE
 */

#include "fonctions.h"


void passe_un(volatile uint32_t* registre, uint32_t index){

	*registre = *registre| (1 << index);
}

void passe_zero(volatile uint32_t* registre, uint32_t index){

	*registre = *registre| ~(1 << index);

}

uint32_t test_zero(volatile uint32_t* registre, uint32_t index){

	passe_zero(registre, index);

	return 0;
}
uint32_t test_un(volatile uint32_t* registre, uint32_t index){

	passe_un(registre, index);

	return 0;
}
