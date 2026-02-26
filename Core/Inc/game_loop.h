/*
 * game_loop.h
 *
 *  Created on: Aug 15, 2025
 *      Author: SAM-Tech
 */

#ifndef INC_GAME_LOOP_H_
#define INC_GAME_LOOP_H_

#include <stdint.h>
#include "paddle.h"

#define MAX_BALLS 3



typedef enum {
	GAME_WIN,
	GAME_LOSE,
	GAME_RESUME
} GameLoopStatus;

typedef struct {
	uint8_t health;
	int8_t score;
	int8_t max_score;
}Game_Info;


void game_elements_init(int8_t ball_x, int8_t ball_y);
void game_elements_draw();

GameLoopStatus game_loop();

int start_game_timer(void);

Game_Info* get_game_info();

Paddle* get_game_paddle();

#endif /* INC_GAME_LOOP_H_ */
