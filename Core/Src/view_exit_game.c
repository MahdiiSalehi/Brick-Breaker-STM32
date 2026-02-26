/*
 * view_exit_game.c
 *
 *  Created on: Aug 15, 2025
 *      Author: SAM-Tech
 */

#include "view_exit_game.h"
#include "stm32f3xx_hal.h"
#include "LiquidCrystal.h"
#include <string.h>


char exit_game_items[3][21] = {
	"score",
	"restart",
	"exit",
};

uint8_t exit_game_curr_idx = 0;
uint8_t exit_game_is_cursor = 0;
unsigned long long int exit_game_last_cursor = 0;


void view_exit_game_show(const int score) {
	exit_game_curr_idx = 1;

	snprintf(exit_game_items[0], 21, "score: %d", score);
	print_menu(0, exit_game_items);
}


uint8_t view_exit_game_handler(uint8_t new_idx) {
	exit_game_curr_idx = new_idx;

	if (exit_game_curr_idx < 1) {
		exit_game_curr_idx = 1;
	} else if (exit_game_curr_idx > 2) {
		exit_game_curr_idx = 2;
	}

	if (HAL_GetTick() > exit_game_last_cursor + 500) {
		exit_game_is_cursor = !exit_game_is_cursor;
		exit_game_last_cursor = HAL_GetTick();
	}

	setCursor(strlen(exit_game_items[exit_game_curr_idx]), exit_game_curr_idx);
	if (exit_game_is_cursor) {
		cursor();
	} else {
		noCursor();
	}

	return exit_game_curr_idx;
}
