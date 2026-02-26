/*
 * custom_chars.c
 *
 *  Created on: Aug 9, 2025
 *      Author: SAM-Tech
 */

#include "custom_chars.h"
#include "LiquidCrystal.h"


typedef unsigned char byte;


byte paddle_sign[8] = {
  0x01, // 0b00001,
	0x01, // 0b00001,
	0x01, // 0b00001,
	0x01, // 0b00001,
	0x01, // 0b00001,
	0x01, // 0b00001,
	0x01, // 0b00001,
	0x01 	// 0b00001
};

byte ball_sign[8] = {
  0x00, // 0b00000,
	0x00, // 0b00000,
	0x0e, // 0b01110,
	0x0e, // 0b01110,
	0x0e, // 0b01110,
	0x0e, // 0b01110,
	0x00, // 0b00000,
	0x00	// 0b00000
};

byte block_normal_sign[8] = {
  0x0e, // 0b01110,
	0x11, // 0b10001,
	0x11, // 0b10001,
	0x11, // 0b10001,
	0x11, // 0b10001,
	0x11, // 0b10001,
	0x11, // 0b10001,
	0x0e	// 0b01110
};

byte block_negative_sign[8] = {
  0x00, // 0b00000,
	0x04, // 0b00100,
	0x04, // 0b00100,
	0x04, // 0b00100,
	0x04, // 0b00100,
	0x04, // 0b00100,
	0x04, // 0b00100,
	0x00	// 0b00000
};

byte block_health_sign[8] = {
	0x00, // 0b00000,
	0x06, // 0b00110,
	0x0F, // 0b01111,
	0x1e, // 0b11110,
	0x0e, // 0b01110,
	0x0f, // 0b01111,
	0x06, // 0b00110,
	0x00  // 0b00000
};

byte block_luck_sign[8] = {
	0x04, // 0b00100
  0x15, // 0b10101
  0x0E, // 0b01110
  0x1F, // 0b11111
  0x0E, // 0b01110
  0x15, // 0b10101
  0x04, // 0b00100
  0x00  // 0b00000
};




void createChars() {
	createChar(PADDLE_SIGN, paddle_sign);
	createChar(BALL_SIGN, ball_sign);

	createChar(BLOCK_NORMAL_SIGN, block_normal_sign);
	createChar(BLOCK_NEGATIVE_SIGN, block_negative_sign);
	createChar(BLOCK_HEALTH_SIGN, block_health_sign);
	createChar(BLOCK_LUCK_SIGN, block_luck_sign);
}
