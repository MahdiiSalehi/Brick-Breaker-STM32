/*
 * rtc.c
 *
 *  Created on: Aug 16, 2025
 *      Author: SAM-Tech
 */

#include "rtc.h"
#include "stm32f3xx_hal.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>



RTC_HandleTypeDef rtc_hrtc;
UART_HandleTypeDef rtc_huart;


void rtc_init(RTC_HandleTypeDef *hrtc, UART_HandleTypeDef *huart) {
	rtc_hrtc = *hrtc;
	rtc_huart = *huart;
}

void rtc_request_uart(void) {
	HAL_UART_Transmit(&rtc_huart, "RTC", 3, 50);
}

/*
 * @param response: Y:M:D:H:M:S
 */
void rtc_set_time_date(char *response) {
	RTC_TimeTypeDef rtc_time;
	RTC_DateTypeDef rtc_date;

	int y, mo, d, h, mi, s;

	sscanf(response,
	       "%d:%d:%d:%d:%d:%d",
	       &y, &mo, &d,
	       &h, &mi, &s);

	rtc_date.Year = y;
	rtc_date.Month = mo;
	rtc_date.Date = d;
	rtc_time.Hours = h;
	rtc_time.Minutes = mi;
	rtc_time.Seconds = s;

	HAL_RTC_SetTime(&rtc_hrtc, &rtc_time, RTC_FORMAT_BIN);
	HAL_RTC_SetDate(&rtc_hrtc, &rtc_date, RTC_FORMAT_BIN);
}


void rtc_get_time(RTC_TimeTypeDef *time) {
	HAL_RTC_GetTime(&rtc_hrtc, time, RTC_FORMAT_BIN);
}

void rtc_get_date(RTC_TimeTypeDef *date) {
	HAL_RTC_GetDate(&rtc_hrtc, date, RTC_FORMAT_BIN);
}

