/*
 * keypad.h
 *
 *  Created on: Jun 6, 2025
 *      Author: SAM-Tech
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_

#define KEYPAD_DEBOUNCE_TIME 300

void setup_keypad();
void keypad_EXTI_callback(unsigned int GPIO_Pin, void (*fn_callback)(unsigned int));


#endif /* INC_KEYPAD_H_ */
