/*
 * view_settings.h
 *
 *  Created on: Aug 16, 2025
 *      Author: SAM-Tech
 */

#ifndef INC_VIEW_SETTINGS_H_
#define INC_VIEW_SETTINGS_H_

#include <stdint.h>


typedef enum {
	NO_SELECTED_ITEM,
	HAS_SELECTED_ITEM
}Settings_State;


void view_settings_show(void);
uint8_t view_settings_handler(uint8_t new_idx, Settings_State state);

#endif /* INC_VIEW_SETTINGS_H_ */
