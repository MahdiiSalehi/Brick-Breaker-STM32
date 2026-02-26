/*
 * view_main_menu.h
 *
 *  Created on: Aug 9, 2025
 *      Author: SAM-Tech
 */

#ifndef INC_VIEW_MAIN_MENU_H_
#define INC_VIEW_MAIN_MENU_H_

#include <stdint.h>
#include "config.h"

// Items States
#define MAIN_MENU_ITEMS_FULL 0
#define MAIN_MENU_ITEMS_WITHOUT_RESUME 1


void view_main_menu_show(char []);
uint8_t view_main_menu_handler(uint8_t new_idx);
void set_main_menu_items_state(int);

Main_State get_main_menu_curr_item();

#endif /* INC_VIEW_MAIN_MENU_H_ */
