/*
 * fibo.h
 *
 *  Created on: 16 oct. 2019
 *      Author: KABA
 */

#ifndef FIBO_H_
#define FIBO_H_

#include <stdint.h>

/**
* Remplis un tableau avec la suite de Fibonnacci.
* @param output_array tableau o� la suite est enregistr�
* @param size nombre de valeur � inscrire dans \a output_array
* @param min_value valeur jusqu'� laquelle les nombres ne sont pas enregistr�s
*/
void fibonacci(uint32_t output_array[], uint32_t size, uint32_t min_value);


#endif /* FIBO_H_ */
