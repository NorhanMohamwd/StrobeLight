/*
 * Eeprom.c
 *
 * Created: 4/22/2024 10:45:37 PM
 *  Author: Nada Salloum
 */ 
#include <avr/io.h>
#include "StdMacros.h"
#include "Interrupt.h"
#include "Eeprom_private.h"
#include "Eeprom.h"
/*#include <xmega.h>*/

static CMD_t cmd_t;   
void writeModeToEeprom(uint8_t Mode)

{

cmd_t=NVMCTRL_CMD_PAGEERASEWRITE;     //choose the NVM Command (Earse and write )

/* Confirm that any previous operation is completed by reading the Busy Flags*/
 while (GET_BIT(NVMCTRL_STATUS ,EEPROMBUSY));
 
/*disable global interrupt cause the interrupts write on eeprom may cause data corruption  */
disableGlobalInterrupt();

/*current_eepromadress=(EEPROM_USED_START_ADDR +i);  // update the write address */

*(uint8_t*)(MODE_ADRR )=Mode;         // write to buffer page with Mode 

/* Write the NVM command unlock to the Configuration Change Protection register in the CPU
(CPU.CCP) and Write the desired command value to the CMD bits in the Control A register (NVMCTRL.CTRLA)
*/
    CPU_CCP = (SPM<<0);
    __asm__ __volatile__  ( "mov r16 , %0\n"
    "STS 0x1000, r16\n"
    ::"r" (cmd_t)  /* set timer interval with config value */
    );

/* Confirm that any previous operation is completed by reading the Busy Flags*/
 while (GET_BIT(NVMCTRL_STATUS ,EEPROMBUSY));
enableGlobalInterrupt(); //enable the interrupt 
}



void readModeFromEeprom(uint8_t *pMode) {
  uint8_t value;
 while (GET_BIT(NVMCTRL_STATUS ,EEPROMBUSY));
	__asm__ __volatile__ (
	"LDS r16, 0x140B  \n"                   // Load actual user row address     // ( the config MODE_ADRR )
	"STS 0x1008, r16 \n"                   // Write address to NVMCTRL address register
	 "LDS r18, 0x1006 \n"                 // Read data from NVMCTRL data register
	 "mov %0, r18 \n"                    // Move data to 'value'
	 : "=r" (value)   :                 // store result in 'value'
	 );
	 
	 *pMode=value;
}

