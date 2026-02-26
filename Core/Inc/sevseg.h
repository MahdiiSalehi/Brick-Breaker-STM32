/*
 * sevseg.h
 *
 *  Created on: Jun 5, 2025
 *      Author: SAM-Tech
 */

#ifndef INC_SEVSEG_H_
#define INC_SEVSEG_H_

#define CODE_LENGTH 4

void show_text(void (*fn_callback)(int, char *));

void setFloatingPoint();
void resetFloatingPoint();

void clear7seg();

#endif /* INC_SEVSEG_H_ */
