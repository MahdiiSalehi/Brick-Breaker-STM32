/*
 * config.h
 *
 *  Created on: Aug 16, 2025
 *      Author: SAM-Tech
 */

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

#include <stdint.h>
#include "stm32f3xx_hal.h"

typedef enum {
	MS_START_PROGRAM,
	MS_START_PROGRAM_VIEW,

	MS_MAIN_MENU,
	MS_MAIN_MENU_VIEW,

	MS_USER_CLICKED,
	MS_USER,
	MS_RESUME_CLICKED,
	MS_RESUME,
	MS_START_GAME_CLICKED,
	MS_START_GAME,
	MS_GAME_LOOP,
	MS_SETTINGS_CLICKED,
	MS_SETTINGS,
	MS_ABOUT_CLICKED,
	MS_ABOUT,

	MS_EXIT_MENU,
	MS_EXIT_MENU_VIEW,

	MS_EXIT_CLICKED,
	MS_RESTART_CLICKED,

	// ----------------

	MS_NEW_MENU_INDEX,
	MS_BACK_CLICKED,
	MS_ENTER_CLICKED,

	MS_REQUEST_RTC,
	MS_REQUEST_CONFIG,
	MS_PENDING,
	MS_GAME_TIMER,

	MS_PADDLE_MOVE_RIGHT,
	MS_PADDLE_MOVE_LEFT,
	MS_PADDLE_MOVE_VOLUME
}Main_State;

// مقادیر پیش‌فرض کانفیگ
#define CONFIG_DEFAULT_INITIAL_HEALTH   (3)
#define CONFIG_MAX_HEALTH								(5)
#define CONFIG_MIN_HEALTH								(2)

#define CONFIG_DEFAULT_BRICK_ROWS       (5)
#define CONFIG_MAX_BRICK_ROWS						(6)
#define CONFIG_MIN_BRICK_ROWS						(2)

// فراخوانی برای مقداردهی اولیه (بارگذاری از حافظه یا مقدار پیش‌فرض)
void    config_init(UART_HandleTypeDef *huart);

// گتر و ستر برای سلامتی اولیه
uint8_t config_getInitialHealth(void);
void    config_setInitialHealth(uint8_t health);

// گتر و ستر برای تعداد ردیف آجرها
uint8_t config_getBrickRows(void);
void    config_setBrickRows(uint8_t rows);

void config_load(char *response);
void config_request_uart(void);


#endif /* INC_CONFIG_H_ */
