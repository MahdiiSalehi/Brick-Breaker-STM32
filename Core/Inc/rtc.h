/*
 * rtc.h
 *
 *  Created on: Aug 16, 2025
 *      Author: SAM-Tech
 */

#ifndef INC_RTC_H_
#define INC_RTC_H_

#include "stm32f3xx_hal.h"


void rtc_init(RTC_HandleTypeDef *hrtc, UART_HandleTypeDef *huart);
void rtc_request_uart(void);

void rtc_set_time_date(char *response);
void rtc_get_time(RTC_TimeTypeDef *time);
void rtc_get_date(RTC_TimeTypeDef *date);


#endif /* INC_RTC_H_ */
