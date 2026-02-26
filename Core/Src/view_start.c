/*
 * view_start.c
 *
 *  Created on: Aug 15, 2025
 *      Author: SAM-Tech
 */

#include "view_start.h"
#include "LiquidCrystal.h"
#include "game_loop.h"


void show_start(void) {
	const char items[2][8] = {
			"Brick",
			"Breaker"
	};

	game_elements_init(2, 3);
	game_elements_draw();

	setCursor(7, 1);
	print(items[0]);

	setCursor(6, 2);
	print(items[1]);
}
