/*
 * game_loop.c
 *
 *  Created on: Aug 15, 2025
 *      Author: SAM-Tech
 */

#include "game_loop.h"

#include "LiquidCrystal.h"

#include "stm32f3xx_hal.h"

#include "ball.h"
#include "paddle.h"
#include "block.h"

#include "config.h"

#include "music.h"

#include <stdint.h>


Game_Info game_info;


uint8_t ball_number = 1;
uint8_t block_rows_number;

Paddle *paddle;
Ball balls[MAX_BALLS];
Block (*blocks)[4];


void blocks_init() {
	block_rows_number = config_getBrickRows();
	blocks = malloc(block_rows_number * sizeof(Block));

	for (int i = 0; i < block_rows_number; i ++) {
		for (int j = 0; j < 4; j ++) {
			block_init(&(blocks[i][j]), j, 19-i, random_block_type());
		}
	}
}

void blocks_draw() {
	for (int i = 0; i < block_rows_number; i ++) {
		for (int j = 0; j < 4; j ++) {
			block_draw(&(blocks[i][j]));
		}
	}
}


void game_elements_init(int8_t ball_x, int8_t ball_y) {
	paddle = malloc(sizeof(Paddle));
	paddle_init(paddle, 2, 2, 3);

	ball_init(&(balls[0]), ball_x, ball_y, 3, 20);

	blocks_init();

	game_info.score = 0;
	game_info.health = config_getInitialHealth();
}

void game_elements_draw() {
	clear();

	paddle_draw(paddle);
	ball_draw(&(balls[0]));
	blocks_draw();
}


/*
 * @return GameLoopStatus
 */
GameLoopStatus game_loop() {
	static uint64_t last_run = 0;

	if (last_run == 0) {
		last_run = HAL_GetTick();
		return GAME_RESUME;
	} else if (HAL_GetTick() - last_run < 100) {
		return GAME_RESUME;
	}

	last_run = 0;

	play_music();

	paddle_draw(paddle);

	// balls-paddle collision
	for (int i = 0; i < ball_number; i ++) {
		if (balls[i].y -1 == paddle->y && balls[i].x == paddle->x && balls[i].dy < 0) {
			balls[i].dy = -balls[i].dy;
		} else if (balls[i].y +1 == paddle->y && balls[i].x == paddle->x && balls[i].dy > 0) {
			balls[i].dy = -balls[i].dy;
		}
	}

	// balls-blocks collisions & update blocks
	for (int i = 0; i < ball_number; i ++) {
		int8_t nextX, nextY;
		Block *tmp_block;
		ball_next_position(&(balls[i]), &nextX, &nextY);

		while ((19-nextY) < block_rows_number && blocks[19-nextY][nextX].active) {
			tmp_block = &(blocks[19-nextY][nextX]);
			block_destroy(tmp_block);
			int16_t score = get_block_score(tmp_block);

			set_special_music(tmp_block->type);

			switch (tmp_block->type) {
				case BLOCK_NORMAL:
					game_info.score += get_block_score(tmp_block);
					break;
				case BLOCK_NEGATIVE:
					game_info.score += get_block_score(tmp_block);
					break;
				case BLOCK_HEALTH:
					game_info.health += get_block_score(tmp_block);
					break;
				case BLOCK_BALL:
					if (ball_number < MAX_BALLS) {
						ball_init(&(balls[ball_number++]), -1, -1, 3, 20);
					}
					break;
			}

			ball_update_direction_random_down(&(balls[i]));
			ball_next_position(&(balls[i]), &nextX, &nextY);
		}


		// update ball
		ball_update(&(balls[i]));
	}

	// health update
	for (int i = 0; i < ball_number; i ++) {
		if (balls[i].y == paddle->y && balls[i].dy < 0) {
			game_info.health -= 1;
		}
	}

	// check losing condition
	if (game_info.health < 1) {
		return GAME_LOSE;
	}

	// check winning condition
	int is_win = 1;

	for (int i = 0; i < block_rows_number && is_win; i ++) {
		for (int j = 0; j < 4; j ++) {
			if (blocks[i][j].active) {
				is_win = 0;
				break;
			}
		}
	}

	if (is_win) {
		return GAME_WIN;
	}

	// Resume Game
	return GAME_RESUME;
}


int start_game_timer(void) {
	static unsigned long long int timer = 0;
	unsigned int diff, delay = 3000;
	uint8_t ch = 0;

	if (timer == 0) {
		timer = HAL_GetTick();
	} else {
		diff = timer + delay - HAL_GetTick();

		if (diff <= 0) {
			timer = 0;
			setCursor(0, 0);
			write(' ');

			return 1;
		} else if (diff <= 1000 && diff > 0 && ch != '1') {
			ch = '1';
			setCursor(0, 0);
			write(ch);
		} else if (diff <= 2000 && diff > 1000 && ch != '2') {
			ch = '2';
			setCursor(0, 0);
			write(ch);
		} else if (diff <= 3000 && diff > 2000 && ch != '3') {
			ch = '3';
			setCursor(0, 0);
			write(ch);
		}

	}
	return 0;
}

Game_Info* get_game_info() {
	return &game_info;
}

Paddle* get_game_paddle() {
	return paddle;
}
