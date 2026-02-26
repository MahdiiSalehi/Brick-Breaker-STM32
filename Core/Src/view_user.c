/*
 * view_user.c
 *
 *  Created on: Aug 21, 2025
 *      Author: SAM-Tech
 */


#include "view_about.h"
#include "stm32f3xx_hal.h"
#include "LiquidCrystal.h"

char user_items[2][21];


void view_user_show(char *username, int score) {
	snprintf(user_items[0], 21, "USER: %s", username);
	snprintf(user_items[1], 21, "score: %d", score);

	print_menu(0, user_items);
}


uint8_t view_user_handler(uint8_t idx) {
	return 0;
}
