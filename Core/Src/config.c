/*
 * config.c
 *
 *  Created on: Aug 16, 2025
 *      Author: SAM-Tech
 */


#include "config.h"
#include "stm32f3xx_hal.h"
#include <string.h>



// متغیرهای داخلی ماژول
static uint8_t config_initial_health  = CONFIG_DEFAULT_INITIAL_HEALTH;
static uint8_t config_brickRows      = CONFIG_DEFAULT_BRICK_ROWS;

UART_HandleTypeDef config_huart;


void config_request_uart() {
	HAL_UART_Transmit(&config_huart, "CONFIG", 6, 50);
}

void config_init(UART_HandleTypeDef *huart)
{
	config_huart = *huart;
}

uint8_t config_getInitialHealth(void)
{
	return config_initial_health;
}

void config_setInitialHealth(uint8_t health)
{
	config_initial_health = health;

	if (config_initial_health > CONFIG_MAX_HEALTH) {
		config_initial_health = CONFIG_MAX_HEALTH;
	} else if (config_initial_health < CONFIG_MIN_HEALTH) {
		config_initial_health = CONFIG_MIN_HEALTH;
	}

	config_save("IH", (int)health);
}

uint8_t config_getBrickRows(void)
{
	return config_brickRows;
}

void config_setBrickRows(uint8_t rows)
{
	config_brickRows = rows;

	if (config_brickRows > CONFIG_MAX_BRICK_ROWS) {
		config_brickRows = CONFIG_MAX_BRICK_ROWS;
	} else if (config_brickRows < CONFIG_MIN_BRICK_ROWS) {
		config_brickRows = CONFIG_MIN_BRICK_ROWS;
	}

	config_save("BR", rows);
}

/*
 * @param response: initialHealth,brickRows
 */
void config_load(char *response)
{
	int ih, br;
	sscanf(response, "%d,%d", &ih, &br);

	if (ih == -1) {
		config_initial_health = CONFIG_DEFAULT_INITIAL_HEALTH;
	} else {
		config_initial_health = ih;
	}

	if (br == -1) {
		config_brickRows = CONFIG_DEFAULT_BRICK_ROWS;
	} else {
		config_brickRows = br;
	}

}

void config_save(char *key, int value)
{
	char send[20];
	sprintf(send, "UPDATE/%s:%d", key, value);

	HAL_UART_Transmit(&config_huart, send, strlen(send), 50);
}
