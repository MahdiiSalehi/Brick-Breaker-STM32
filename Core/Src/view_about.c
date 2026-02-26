/*
 * view_about.c
 *
 *  Created on: Aug 16, 2025
 *      Author: SAM-Tech
 */


#include "view_about.h"
#include "stm32f3xx_hal.h"
#include "LiquidCrystal.h"
#include "rtc.h"



char about_items[2][21];

RTC_TimeTypeDef about_time;
RTC_DateTypeDef about_date;



void view_about_set_items() {
	snprintf(about_items[0], 21, "20%02d/%02d/%02d", about_date.Year, about_date.Month, about_date.Date);
	snprintf(about_items[1], 21, "%02d:%02d:%02d", about_time.Hours, about_time.Minutes, about_time.Seconds);
}


void view_about_show(void) {
	rtc_get_time(&about_time);
	rtc_get_date(&about_date);

	view_about_set_items();
	print_menu(0, about_items);
}



uint8_t view_about_handler(uint8_t idx) {
	rtc_get_time(&about_time);
	rtc_get_date(&about_date);

	view_about_set_items();

	setCursor(0, 0);
	print(about_items[0]);

	setCursor(0, 1);
	print(about_items[1]);

	return 0;
}
