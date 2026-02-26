/*
 * sevseg.c
 *
 *  Created on: Jun 5, 2025
 *      Author: SAM-Tech
 */


#include "stm32f3xx_hal.h"

#include "sevseg.h"


GPIO_TypeDef *class = GPIOD;

uint16_t D_pins[] = {
GPIO_PIN_8,
GPIO_PIN_9,
GPIO_PIN_10,
GPIO_PIN_11, };

uint16_t num_pins[] = {
GPIO_PIN_15,
GPIO_PIN_14,
GPIO_PIN_13,
GPIO_PIN_12, };

uint16_t floating_point_pin = GPIO_PIN_7;

char codes[][CODE_LENGTH] = {
		"0000", // 0
		"0001", // 1
		"0010", // 2
		"0011", // 3
		"0100", // 4
		"0101", // 5
		"0110", // 6
		"0111", // 7
		"1000", // 8
		"1001", // 9
		"1010", // a
		"1011", // b
		"1100", // c
		"1101", // d
		"1110", // e
		"1111", // f
};


char* getBinDigit(char digit) {
	int index;

	if (digit > '9') {
		if (digit >= 'a' && digit <= 'f') {
			index = digit - 'a';
		} else if (digit >= 'A' && digit <= 'F') {
			index = digit - 'A';
		}

		index += 10;
	} else if (digit >= '0') {
		index = digit - '0';
	}

	return codes[index];
}


void resetSevSeg(int index) {
	HAL_GPIO_WritePin(class, D_pins[index], GPIO_PIN_RESET);
}

void setSevSeg(int index) {
	for (int i = 0; i < 4; i++) {
		resetSevSeg(i);
	}

	HAL_GPIO_WritePin(class, D_pins[index], GPIO_PIN_SET);
}

void setFloatingPoint() {
	HAL_GPIO_WritePin(class, floating_point_pin, GPIO_PIN_RESET);
}

void resetFloatingPoint() {
	HAL_GPIO_WritePin(class, floating_point_pin, GPIO_PIN_SET);
}

void setValue(char digit) {
	char *code = getBinDigit(digit);

	for (int i = 0; i < 4; i++) {
		HAL_GPIO_WritePin(class, num_pins[i], (code[i] - '0'));
	}
}

void showDigit(int DNum, char digit) {
	if (digit == 0) {
		resetSevSeg(DNum);
	} else {
		setSevSeg(DNum);
	}

	setValue(digit);
}

void clear7seg() {
	for (int i = 0; i < 4; i++) {
		resetSevSeg(i);
	}
}

void show_text(void (*fn_callback)(int, char *)) {
	static int index_d = 0;
	char text[] = "0000";

	fn_callback(index_d, text);

	showDigit(index_d, text[index_d]);

	index_d = (index_d + 1) % 4;
}
