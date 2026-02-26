/*
 * view_main_menu.c
 *
 *  Created on: Aug 9, 2025
 *      Author: SAM-Tech
 */

#include "view_main_menu.h"
#include "stm32f3xx_hal.h"
#include "LiquidCrystal.h"
#include <string.h>
#include <config.h>


char main_menu_items_full[5][21] = {
	"USER: ",
	"resume",
	"start",
	"settings",
	"about"
};
char main_menu_items_without_resume[4][21] = {
	"USER: ",
	"start",
	"settings",
	"about"
};
char (*main_menu_items)[21] = main_menu_items_without_resume;



uint8_t main_menu_curr_idx = 0;
uint8_t main_menu_is_cursor = 0;
uint8_t main_menu_start_item = 0;
uint8_t main_menu_items_state = MAIN_MENU_ITEMS_WITHOUT_RESUME;
unsigned long long int main_menu_last_cursor = 0;


void view_main_menu_show(char username[]) {
	main_menu_curr_idx = 0;
	main_menu_start_item = 0;

	snprintf(main_menu_items[0], 21, "USER: %s", username);
	print_menu(main_menu_curr_idx, main_menu_items);
}

uint8_t view_main_menu_handler(uint8_t new_idx) {
	if (new_idx != main_menu_curr_idx) {
		switch (new_idx) {
			case 0:
				main_menu_curr_idx = 0;
				if (main_menu_start_item > 0) {
					print_menu(0, main_menu_items);
					main_menu_start_item = 0;
				}
				break;
			case 1:
				main_menu_curr_idx = 1;
				break;
			case 2:
				main_menu_curr_idx = 2;
				break;
			case 3:
				main_menu_curr_idx = 3;
				break;
			case 4:
				if (main_menu_items_state == MAIN_MENU_ITEMS_FULL) {
					main_menu_curr_idx = 4;
					if (main_menu_start_item == 0) {
						print_menu(1, main_menu_items);
						main_menu_start_item = 1;
					}
				}
				break;
		}
	}


	if (HAL_GetTick() > main_menu_last_cursor + 500) {
		main_menu_is_cursor = !main_menu_is_cursor;
		main_menu_last_cursor = HAL_GetTick();
	}

	setCursor(strlen(main_menu_items[main_menu_curr_idx]), main_menu_curr_idx - main_menu_start_item);
	if (main_menu_is_cursor) {
		cursor();
	} else {
		noCursor();
	}

	return main_menu_curr_idx;
}


void set_main_menu_items_state(int state) {
	switch(state) {
		case MAIN_MENU_ITEMS_FULL:
			main_menu_items_state = MAIN_MENU_ITEMS_FULL;
			main_menu_items = main_menu_items_full;
			break;
		case MAIN_MENU_ITEMS_WITHOUT_RESUME:
			main_menu_items_state = MAIN_MENU_ITEMS_WITHOUT_RESUME;
			main_menu_items = main_menu_items_without_resume;
			break;
	}
}

Main_State get_main_menu_curr_item() {
	switch(main_menu_items_state) {
		case MAIN_MENU_ITEMS_FULL:
			switch(main_menu_curr_idx) {
				case 0:
					return MS_USER_CLICKED;
				case 1:
					return MS_RESUME_CLICKED;
				case 2:
					return MS_START_GAME_CLICKED;
				case 3:
					return MS_SETTINGS_CLICKED;
				case 4:
					return MS_ABOUT_CLICKED;
			}

		case MAIN_MENU_ITEMS_WITHOUT_RESUME:
			switch(main_menu_curr_idx) {
				case 0:
					return MS_USER_CLICKED;
				case 1:
					return MS_START_GAME_CLICKED;
				case 2:
					return MS_SETTINGS_CLICKED;
				case 3:
					return MS_ABOUT_CLICKED;
			}
			break;
	}
}
