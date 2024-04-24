/*
 * Eeprom_private.h
 *
 * Created: 4/22/2024 10:47:55 PM
 *  Author: Nada Salloum
 */ 


#ifndef EEPROM_PRIVATE_H_
#define EEPROM_PRIVATE_H_
#include "StdTypes.h"
#define SPM 0X9D         // key for Registers under Configuration Change Protection                                                      
// REG 

#define NVMCTRL_STATUS  _SFR_MEM8(0x1002)
#define NVMCTRL_DATA    _SFR_MEM16(0x1006)
#define NVMCTRL_ADDR    _SFR_MEM16(0x1008)



#define FlASHBUSY      0  /* Flash busy bit position in Nvmctrl.status register .*/
#define EEPROMBUSY     1  /* EEPROM busy bit position Nvmctrl.status register .*/

// NVMCTRL COMMANDS 
typedef enum 
{
	NVMCTRL_CMD_NONE = (0x00<<0),  /* No Command */
	NVMCTRL_CMD_PAGEWRITE = (0x01<<0),  /* Write page buffer to selected address (user row)*/
	NVMCTRL_CMD_PAGEERASE = (0x02<<0),  /* Erase page */ /*( Erase the selected address page (user row) */
	NVMCTRL_CMD_PAGEERASEWRITE = (0x03<<0),  /* Erase and write the selected address page (user row) */
	NVMCTRL_CMD_PAGEBUFCLR= (0x04<<0),  /* Page buffer clear */
	NVMCTRL_CMD_EEERASE = (0x06<<0)  /* EEPROM erase */
} CMD_t;


#endif /* EEPROM_PRIVATE_H_ */