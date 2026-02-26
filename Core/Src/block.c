// In the name of ALLAH!
// Mahdi Salehi

#include "block.h"
#include "custom_chars.h"
#include "LiquidCrystal.h"

#include <stdlib.h>

// آرایهٔ ثابت نگاشت نوع به نماد و امتیاز
const BlockInfo blockInfo[BLOCK_TYPE_COUNT] = {
	[BLOCK_NORMAL]   = { BLOCK_NORMAL_SIGN		,  +1  },
	[BLOCK_NEGATIVE] = { BLOCK_NEGATIVE_SIGN	,  -1  },
	[BLOCK_HEALTH]   = { BLOCK_HEALTH_SIGN		,   1  },
	[BLOCK_BALL]     = { BALL_SIGN						,   1  },
	[BLOCK_LUCK]     = { BLOCK_LUCK_SIGN			,   0  }
};

// مقداردهی اولیهٔ بلوک
void block_init(Block *b, uint8_t x, uint8_t y, BlockType t) {
	b->x      = x;
	b->y      = y;
	b->type   = t;
	b->active = true;
}

// return score
int16_t get_block_score(Block *b) {
	return blockInfo[b->type].score;
}

// رسم بلوک (در صورت فعال بودن)
void block_draw(const Block *b) {
	if (!b->active) return;

	setCursor(b->y, b->x);
	write(blockInfo[b->type].symbol);
}

// شکستن بلوک و پاک‌سازی نمایشگر
void block_destroy(Block *b) {
	setCursor(b->y, b->x);

	if (b->type == BLOCK_LUCK) {
		b->type = random_luck_block_type();
		write(blockInfo[b->type].symbol);

	} else {
		b->active = false;
		write(' ');
	}
}

BlockType random_block_type(void) {
	int tmp = rand() % 12;

	switch (tmp) {
		case 0:;
		case 1:;
		case 2:;
		case 3:;
		case 4:;
		case 5:;
		case 6:;
		case 7:
			return BLOCK_NORMAL;
		case 8:
			return BLOCK_NEGATIVE;
		case 9:
			return BLOCK_HEALTH;
		case 10:
			return BLOCK_BALL;
		case 11:
			return BLOCK_LUCK;
	}
}

BlockType random_luck_block_type(void) {
	int tmp = rand() % 10;

	switch (tmp) {
		case 0:;
		case 1:;
		case 2:;
		case 3:;
		case 4:;
		case 5:;
		case 6:
			return BLOCK_NORMAL;
		case 7:
			return BLOCK_NEGATIVE;
		case 8:
			return BLOCK_HEALTH;
		case 9:
			return BLOCK_BALL;
	}
}
