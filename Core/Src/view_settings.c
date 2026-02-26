/*
 * view_settings.c
 *
 *  Created on: Aug 16, 2025
 *      Author: SAM-Tech
 */

#include "view_settings.h"
#include "config.h"
#include <stdint.h>



char settings_items[2][21];
int settings_ih = -1, settings_br = -1;

uint8_t settings_curr_idx = 0;
uint8_t settings_is_cursor = 0;
unsigned long long int settings_last_cursor = 0;



void view_settings_check_update_values_change(void) {
	int new_ih, new_br;

	new_ih = config_getInitialHealth();
	new_br = config_getBrickRows();

	if (new_ih != settings_ih) {
		settings_ih = new_ih;
		sprintf(settings_items[0], "Initial Health: %d", settings_ih);

		setCursor(0, 0);
		print(settings_items[0]);
	}

	if (new_br != settings_br) {
		settings_br = new_br;
		sprintf(settings_items[1], "Brick Rows: %d", settings_br);

		setCursor(0, 1);
		print(settings_items[1]);
	}
}



void view_settings_show(void) {
	settings_curr_idx = 0;

	settings_ih = -1;
	settings_br = -1;

	clear();
	view_settings_check_update_values_change();
}


uint8_t view_settings_handler(uint8_t new_idx, Settings_State state) {
	settings_curr_idx = new_idx;

	if (settings_curr_idx < 0) {
		settings_curr_idx = 0;
	} else if (settings_curr_idx > 1) {
		settings_curr_idx = 1;
	}

	view_settings_check_update_values_change();

	if (HAL_GetTick() > settings_last_cursor + 500) {
		settings_is_cursor = !settings_is_cursor;
		settings_last_cursor = HAL_GetTick();
	}

	setCursor(strlen(settings_items[settings_curr_idx]) - state, settings_curr_idx);
	if (settings_is_cursor) {
		cursor();
	} else {
		noCursor();
	}

	return settings_curr_idx;
}
