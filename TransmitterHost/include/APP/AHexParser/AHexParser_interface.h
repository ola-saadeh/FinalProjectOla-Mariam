/*
 * AHexParser_interface.h
 *
 *  Created on: Jan 11, 2025
 *      Author: ZBOOK
 */

#ifndef AHEXPARSER_INTERFACE_H_
#define AHEXPARSER_INTERFACE_H_

#include "LIB/STD_Types.h"

void AHexParser_voidParseRecord(const char *Copy_u8Record);
void AHexParser_voidParseData(const char *Copy_u8Record);
u8 AHexParser_u8ASCIToHex(u8 Copy_u8Variable);



#endif /* AHEXPARSER_INTERFACE_H_ */
