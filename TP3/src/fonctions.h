/*
 * fonctions.h
 *
 *  Created on: 15 nov. 2019
 *      Author: KABA_GAUDRE
 */

#ifndef FONCTIONS_H_
#define FONCTIONS_H_


#include <stdint.h>


void passe_zero(volatile uint32_t* registre, uint32_t index);

void passe_un(volatile uint32_t* registre, uint32_t index);

uint32_t test_zero(volatile uint32_t* registre, uint32_t index);

uint32_t test_un(volatile uint32_t* registre, uint32_t index);

#endif /* FONCTIONS_H_ */
