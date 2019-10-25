/*
 * fonctions.c
 *
 *  Created on: 25 oct. 2019
 *      Author: KABA
 */

#include "fonctions.h"

float  poids = 0.0f;

struct s calcul_barycentre(float * f, float * m){


	return barycentre;
}

float photometrie_ouverture(float * f, float * m, int size){


	int i;
	for(i=0 ; i < size; i++){

		if(m[i] != 0){
			poids += f[i];
		}

	}

	return poids;

}
