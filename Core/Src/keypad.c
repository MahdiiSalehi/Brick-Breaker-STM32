/*
 * keypad.c
 *
 *  Created on: Jun 6, 2025
 *      Author: SAM-Tech
 */

#include "keypad.h"
#include "stm32f3xx_hal.h"




GPIO_TypeDef *const Row_ports[] = {GPIOE, GPIOE, GPIOE, GPIOE};
const uint16_t Row_pins[] = {GPIO_PIN_7, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10};

GPIO_TypeDef *const Column_ports[] = {GPIOE, GPIOE, GPIOE, GPIOE};
const uint16_t Column_pins[] = {GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14};




void setup_keypad() {
	HAL_GPIO_WritePin(Column_ports[0], Column_pins[0], 1);
	HAL_GPIO_WritePin(Column_ports[1], Column_pins[1], 1);
	HAL_GPIO_WritePin(Column_ports[2], Column_pins[2], 1);
	HAL_GPIO_WritePin(Column_ports[3], Column_pins[3], 1);
}


int8_t get_key_num(uint16_t GPIO_Pin) {
	int8_t row_number = -1;
	int8_t column_number = -1;

	for (uint8_t row = 0; row < 4; row++) { // Loop through Rows
		if (GPIO_Pin == Row_pins[row]) {
			row_number = row;
		}
	}

	HAL_GPIO_WritePin(Column_ports[0], Column_pins[0], 0);
	HAL_GPIO_WritePin(Column_ports[1], Column_pins[1], 0);
	HAL_GPIO_WritePin(Column_ports[2], Column_pins[2], 0);
	HAL_GPIO_WritePin(Column_ports[3], Column_pins[3], 0);


	for (uint8_t col = 0; col < 4; col++) { // Loop through Columns
		HAL_GPIO_WritePin(Column_ports[col], Column_pins[col], 1);

		if (HAL_GPIO_ReadPin(Row_ports[row_number], Row_pins[row_number])) {
			column_number = col;
		}

		HAL_GPIO_WritePin(Column_ports[col], Column_pins[col], 0);
	}

	HAL_GPIO_WritePin(Column_ports[0], Column_pins[0], 1);
	HAL_GPIO_WritePin(Column_ports[1], Column_pins[1], 1);
	HAL_GPIO_WritePin(Column_ports[2], Column_pins[2], 1);
	HAL_GPIO_WritePin(Column_ports[3], Column_pins[3], 1);

	if (row_number == -1 || column_number == -1) {
		return -1; // Reject invalid scan
	}

//	uart_print("_____ row{%d} col{%d}\n", row_number, column_number);

	return row_number * 4 + column_number + 1;
}



void keypad_EXTI_callback(unsigned int GPIO_Pin, void (*fn_callback)(unsigned int)) {
	static unsigned int enter_time = 0;
	int8_t key_num, is_kaypad = 0;

	for (int i = 0; i < 4; i ++) {
		if (GPIO_Pin == Row_pins[i]) {
			is_kaypad = 1;
			break;
		}
	}

	if (!is_kaypad) {
		return;
	}

	if (enter_time + KEYPAD_DEBOUNCE_TIME >= HAL_GetTick()) {
		return;
	}

	enter_time = HAL_GetTick();

	key_num = get_key_num(GPIO_Pin);
	if (key_num != -1) {
		fn_callback(key_num);
	} else {
//		uart_print("KP -1\n");
	}
}
