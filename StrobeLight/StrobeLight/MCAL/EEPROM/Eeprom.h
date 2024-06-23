/*
 * Eeprom.h
 *
 * Created: 4/22/2024 10:45:58 PM
 *  Author: Nada salloum
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#define  ModeAddr       USERROW_ADDR            // EEPROM PAGE 
// MEMORIE SECTION
#define EEPEOM_START_ADRR   0X1400 // 8 pages with 32 bytes per page 
#define USERROW_START_ADDR  0X1300 // external page of eeprom doesn't get erased while flashing

//CONFIG Values
#define EEPROM_USED_START_ADDR    EEPEOM_START_ADRR    /*will write to the USER_Row page 
                                                          change to EEPROM if wants to write on EEPROM
														 */  
#define MODE_ADRR    (EEPROM_USED_START_ADDR+0X000B)    //config between 0 to 32 byte 

// APIS 
void writeModeToEeprom(uint8_t data);

void readModeFromEeprom(uint8_t *pMode);

#endif /* EEPROM_H_ */