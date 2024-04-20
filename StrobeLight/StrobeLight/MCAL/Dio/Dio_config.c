/*
 * Dio_config.c
 *
 * Created: 4/7/2024 8:51:52 PM
 *  Author: Nada Salloum - https://github.com/nadasalloum
 */ 
#include "Dio_interface.h" 
#include "Dio_config.h"
/* Array to configure individual pin functionalities (output, input, pull-up) */
/*** To perform a bulk configuration of all pins in one go ***/
/**Config ***/
const dio_pinStatus PinsStatusArray[TOTAL_PINS]={
	OUTPUT,      /* Port A Pin 0 */
	OUTPUT,      /* Port A Pin 1 */
	OUTPUT,      /* Port A Pin 2 */
	OUTPUT,      /* Port A Pin 3 */
	OUTPUT,      /* Port A Pin 4 */
	OUTPUT,      /* Port A Pin 5 */
	OUTPUT,      /* Port A Pin 6 */
	INPUT,       /* Port A Pin 7 */
	INPULL,      /* Port B Pin 0 */
	INPULL,      /* Port B Pin 1 */
	INPULL,		 /* Port B Pin 2 */
	OUTPUT,		 /* Port B Pin 3 */
	OUTPUT,		 /* Port B Pin 4 */
	OUTPUT,		 /* Port B Pin 5 */
	INPULL,		 /* Port C Pin 0 */
	OUTPUT,		 /* Port C Pin 1 */
	OUTPUT,		 /* Port C Pin 2 */
	OUTPUT		 /* Port C Pin 3 */

};