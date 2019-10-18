/*
 * fibo.c
 *
 *  Created on: 16 oct. 2019
 *      Author: KABA
 *
 *      fn = f(n-2) + f(n-1)
 */

#include "fibo.h"



void fibonacci(uint32_t output_array[], uint32_t size, uint32_t min_value){
/*
 * Tester si l'utilisateur donne des nombres negatifs
 */
	if(size < 0 || min_value < 0){
		puts("!!!La taille doit etre superieur a 0 et le minimum positive !!!");
		exit(1);
	}
	if(size < 2)
		output_array[1] = min_value;
	else{

		uint32_t p, d;
			p = min_value; d = min_value + 1;

			output_array[0] = p;
			output_array[1] = d;

			uint32_t i = 0;
			for( i = 2; i < size; i++){

				output_array[i] = output_array[i-2] + output_array[i-1];
			}

	}

	uint32_t j = 0;
	for( j = 0; j < size; j++)
		printf("%d : %d\n", j+1, output_array[j]);
}
