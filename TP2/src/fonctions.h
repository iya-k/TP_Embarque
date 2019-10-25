/*
 * pondere.h
 *
 *  Created on: 25 oct. 2019
 *      Author: KABA
 */

#ifndef FONCTIONS_H_
#define FONCTIONS_H_

#include <stdio.h>
#include <stdlib.h>

struct s{
	float x;
	float y;
}barycentre;

struct s calcul_barycentre(float * fenetre, float * mask);

centroide();

float photometrie_ouverture(float * fenetre, float * mask, int size);

photometrie_mask();


#endif /* FONCTIONS_H_ */
