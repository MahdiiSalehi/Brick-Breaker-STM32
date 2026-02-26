/*
 * music.c
 *
 *  Created on: Jun 5, 2025
 *      Author: SAM-Tech
 */

#include <string.h>
#include <math.h>
#include "stm32f3xx_hal.h"
#include "music.h"
#include "block.h"


TIM_HandleTypeDef *htim;
uint8_t tim_channel = TIM_CHANNEL_4;


char note_names[NOTE_NAME_NUMBERS][3] = {
	"A",
	"AS",
	"B",
	"C",
	"CS",
	"D",
	"DS",
	"E",
	"F",
	"FS",
	"G",
	"GS"
};

int note_freqs[NOTE_NAME_NUMBERS][8] = {
/* A   */{ 27, 55, 110, 220, 440, 880, 1760, -1 },
/* A#  */{ 29, 58, 116, 233, 466, 932, 1864, -1 },
/* B   */{ 31, 62, 123, 247, 494, 988, 1975, -1 },
/* C   */{ -1, 33, 65, 131, 262, 523, 1046, 2093 },
/* C#  */{ -1, 35, 69, 139, 277, 554, 1108, 2217 },
/* D   */{ -1, 37, 73, 147, 294, 587, 1174, 2349 },
/* D#  */{ -1, 39, 78, 156, 311, 622, 1244, 2489 },
/* E   */{ -1, 41, 82, 165, 330, 659, 1318, 2637 },
/* F   */{ -1, 44, 87, 175, 349, 698, 1396, 2793 },
/* F#  */{ -1, 46, 92, 185, 370, 740, 1480, 2960 },
/* G   */{ -1, 49, 98, 196, 392, 784, 1568, 3136 },
/* G#  */{ -1, 52, 104, 208, 415, 831, 1661, 3322 }
};

typedef struct Note {
	unsigned int freq;
	unsigned int duration;
} Note;

typedef struct Music {
	Note notes[MAX_NOTE_NUMBERS];
	unsigned int note_numbers;
	unsigned int volume;
	uint8_t repeat;
	uint8_t play;
	unsigned int curr_note;
	unsigned int played_dur;
} Music;

Music main_music, special_music;
Music *music = &main_music;



void init_music(TIM_HandleTypeDef *_htim) {
	htim = _htim;

	main_music.repeat = 1;
	main_music.volume = 100;
	main_music.play = 0;
	main_music.note_numbers = 0;

	special_music.repeat = 0;
	special_music.volume = 100;
	special_music.play = 1;
	special_music.note_numbers = 0;
}

int get_freq_note(char note[]) {
	uint8_t note_len = strlen(note);
	uint8_t octave = atoi(&note[note_len - 1]);
	int i;

	note[note_len - 1] = 0;

	for (i = 0; i < NOTE_NAME_NUMBERS; i ++) {
		if (!strcmp(note, note_names[i])) {
			break;
		}
	}

//	uart_print("In {%s} | find: {%s} | octave: {%d}\n", note, note_names[i], octave);

	if (i != NOTE_NAME_NUMBERS && octave >= 0 && octave <= 7) {
		return note_freqs[i][octave];
	} else {
		return 0;
	}
}


void extract_note(char note_str[], unsigned int start, unsigned int end) {
	char note[7], duration[7];
	int freq, i, j;

	for (i = start; i < end && note_str[i] != ':'; i ++) {
		note[i-start] = note_str[i];
	}

	note[i-start] = 0;

	for (j = ++i; j < end; j ++) {
		duration[j-i] = note_str[j];
	}

	duration[j-i] = 0;

//	uart_print("N: {%s} | D: {%s}\n", note, duration);

	if (!strcmp(note_str, "REST")) {
		freq = 0;
	} else {
		freq = get_freq_note(note);

		if (freq == -1) {
			freq = 0;
		}
	}

	music->notes[music->note_numbers].freq = freq;
	music->notes[music->note_numbers].duration = atoi(duration);

	music->note_numbers ++;
}

void set_new_music_str(char notes_str[]) {
	pause_music();

	music->note_numbers = 0;
	music->curr_note = 0;
	music->played_dur = 0;

	for (int i = 0, j = 0; notes_str[i]; i = j + 1) {
		for (j = i; notes_str[j] && notes_str[j] != '/'; j++) {
			// empty for
		}

		extract_note(notes_str, i, j);

		if (!notes_str[j]) {
			break;
		}

	}
}


///////////////////////////////

void mute() {
	__HAL_TIM_SET_COMPARE(htim, tim_channel, 0);
}

void set_volume_on_buzzer() {
	unsigned int arr = htim->Instance->ARR + 1;
	unsigned int volume = (music->volume * arr / 10) / 100;

//	uart_print("ARR: (%d)\n", arr);

	__HAL_TIM_SET_COMPARE(htim, tim_channel, volume);
}


void set_volume_value(unsigned int value) {
	if (value >= 0 && value <= 100) {
		music->volume = value;
	}
}

void pause_music() {
	mute();
	music->play = 0;
}

void play_music() {
	music->play = 1;
}

void reset() {
	music->curr_note = 0;
	music->played_dur = 0;
}

void buzzerChangeTone(uint16_t freq, uint16_t volume) {
	if (freq == 0 || freq > 20000) {
		__HAL_TIM_SET_COMPARE(htim, tim_channel, 0);
	} else {
		const uint32_t internalClockFreq = HAL_RCC_GetSysClockFreq();
		const uint32_t prescaler = 1 + internalClockFreq / freq / 60000;
		const uint32_t timerClock = internalClockFreq / prescaler;
		const uint32_t periodCycles = timerClock / freq;
		const uint32_t pulseWidth = volume * periodCycles / 1000 / 2;

		htim->Instance->PSC = prescaler - 1;
		htim->Instance->ARR = periodCycles - 1;
		htim->Instance->EGR = TIM_EGR_UG;

		__HAL_TIM_SET_COMPARE(htim, tim_channel, pulseWidth);
	}
}

void playing() {
	if (!music->play) {
		return;
	}

	if (music->curr_note >= music->note_numbers) {
		reset();

		if (!music->repeat) {

			if (music == &special_music) {
				pause_music();
				music = &main_music;

			} else {
				pause_music();
			}
		}

		return;
	}

	if (music->played_dur >= music->notes[music->curr_note].duration) {
		music->curr_note++;
		music->played_dur = 0;

		return;
	}

	if (!music->played_dur) {
		buzzerChangeTone(music->notes[music->curr_note].freq, music->volume);

//		uart_print("F: {%d} | D: {%d} | newARR: {%d}\n", music->notes[music->curr_note].freq, music->notes[music->curr_note].duration, arr);
	}

	music->played_dur ++;
}

void set_repeat(uint8_t repeat) {
	if (repeat) {
		music->repeat = 1;
	} else {
		music->repeat = 0;
	}
}


void set_special_music(BlockType bt) {
	music = &special_music;

	switch (bt) {
		case BLOCK_NORMAL:
			set_new_music_str("D5:50");
			break;
		case BLOCK_NEGATIVE:
			set_new_music_str("E5:50");
			break;
		case BLOCK_HEALTH:
			set_new_music_str("F5:50");
			break;
		case BLOCK_BALL:
			set_new_music_str("G5:50");
			break;
		case BLOCK_LUCK:
			set_new_music_str("A6:50");
			break;
	}

	play_music();
}
