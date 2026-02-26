/*
 * music.h
 *
 *  Created on: Jun 5, 2025
 *      Author: SAM-Tech
 */

#ifndef INC_MUSIC_H_
#define INC_MUSIC_H_

#define MAX_NOTE_NUMBERS 1024
#define NOTE_NAME_NUMBERS 12

#include "block.h"

void init_music(TIM_HandleTypeDef *_htim);
void playing();

void set_new_music_str(char notes_str[]);
void set_volume_value(unsigned int value);
void set_repeat(uint8_t repeat);
void play_music();
void set_special_music(BlockType);

void mute();
void pause_music();
void reset();


#endif /* INC_MUSIC_H_ */
