/*
 ============================================================================
 Name        : TP2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <stdint.h>

struct barycentre{
	float x;
	float y;
};

/* Fonction de calcul de la photométrie d'ouverture*/
float calcul_photometrie_ouverture(float * fenetre, float * masque){
	float poids = 0;
	int size = 36;
	int i;

	for(i=0;i<size;i++){
		if(masque[i]!=0) poids += fenetre[i];
	}

	return poids;
}

/* Fonction de calcul de la photométrie par masque pondéré */
float calcul_photometrie_pondere(float * fenetre, float * masque){
	float poids = 0;
	int size = 36;
	int i;

	for(i=0;i<size;i++) poids += fenetre[i] * masque[i];

	return poids;
}

/* Fonction de calcul des coordonnées du centroide */
struct barycentre calcul_centroide(float * fenetre, float * masque){
	int tabs_size = 36;
	float poids = 0;
	int i, cpt_ligne = 0;
	struct barycentre coord_barycentre;
	float abs_ponderee[tabs_size];
	float ord_ponderee[tabs_size];

	//Calcul de l'absisse pondérée et de l'ordonnée pondérée et du poids
	for(i=0 ; i<tabs_size; i++){
		if((i % 6 + 1) == 1) cpt_ligne++;
		if(masque[i]==0){
			abs_ponderee[i] = 0;
			ord_ponderee[i] = 0;
		}else{
			abs_ponderee[i] = fenetre[i] * (i % 6 + 1);
			ord_ponderee[i] = fenetre[i] * cpt_ligne;
			poids += fenetre[i];
		}
	}

	//Calcul des coordonnées du centroïde
	coord_barycentre.x = 0;
	coord_barycentre.y = 0;

	for(i=0 ; i<tabs_size ; i++){
		coord_barycentre.x += abs_ponderee[i];
		coord_barycentre.y += ord_ponderee[i];
	}
	coord_barycentre.x = coord_barycentre.x / poids;
	coord_barycentre.y = coord_barycentre.y / poids;

	return coord_barycentre;
}

uint32_t break_simu(const char * break_name, uint32_t break_id,int32_t time)
{
	uint32_t static test_counter = 0;
	return test_counter++;
}

int32_t get_elapsed_time() {
	static int32_t last_time = 0;
	int32_t elpased_time = 0;
	int32_t current_time = clock();

	elpased_time =  current_time - last_time;
	last_time = current_time;
	return elpased_time;
}

int main(void) {
	/* performance statistic initialization */
	break_simu("start",0,get_elapsed_time());

	float window[] = {2.4, 52.38, 2.36, 2.34, 82.32, 92.3,
			12.4, 1710.38, 3716.36, 3558.34, 7.32, 1.3,
			7.4, 1852.38, 4516.36, 6558.34, 1689.32, 1.3,
			2.4, 52.38, 1289.36, 1289.34, 1646.32, 92.3,
			2.4, 52.38, 9.36, 1610.34, 1486.32, 92.3,
			2.4, 52.38, 2.36, 2.34, 1486.32, 92.3,
	};

	float mask[] = {0, 0, 0.12, 0.14, 0, 0,
			0, 0, 1, 0.9, 0, 0,
			0.09, 0.19, 0.96, 0.75, 0.47, 0.19,
			0, 0.13, 0.15, 0.39, 0.88, 0,
			0, 0, 0.15, 0.39, 0.88, 0,
			0, 0, 0.07, 0.19, 0, 0
	};

	struct barycentre barycentre_centroide;
	float poids_ouverture = 0;
	float poids_masque_pondere = 0;

	//puts("!!!Hello World!!!");

	barycentre_centroide = calcul_centroide(window, mask);
	//printf("\nCoordonnees du centroide : \n\t x : %f \n\t y : %f", barycentre_centroide.x, barycentre_centroide.y);
	break_simu("calcul_centroide",1,get_elapsed_time());

	poids_ouverture = calcul_photometrie_ouverture(window, mask);
	//printf("\nPoids de la photometrie d'ouverture : %f", poids_ouverture);
	break_simu("calcul_photometrie_ouverture",1,get_elapsed_time());

	poids_masque_pondere = calcul_photometrie_pondere(window, mask);
	//printf("\nPoids de la photometrie par masque pondere : %f \n", poids_masque_pondere);
	/* end of performance measurements */
	break_simu("calcul_photometrie_pondere",1,get_elapsed_time());
	break_simu("end",2,get_elapsed_time());
	return EXIT_SUCCESS;
}
