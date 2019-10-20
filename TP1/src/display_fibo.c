/*
 * display_fibo.c
 *
 *  Created on: 19 oct. 2019
 *      Author: KABA
 */

#include "display_fibo.h"

void display_fibo( uint32_t * array, uint32_t n)
{
	uint32_t j = 0;

	for ( j = 0; j < n; j++)
	{
		printf("%d : %d\n", j+1, array[j]);
	}
}
