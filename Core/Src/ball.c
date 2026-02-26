// In the name of ALLAH!
// Mahdi Salehi

#include "ball.h"
#include "LiquidCrystal.h"
#include "custom_chars.h"

#include <stdlib.h>

// مقداردهی اولیه
void ball_init(Ball   *b,
							 int8_t  x,
							 int8_t  y,
							 uint8_t maxX,
							 uint8_t maxY)
{
    b->minX   = 0;
    b->maxX   = maxX;
    b->minY   = 0;
    b->maxY   = maxY;

    ball_update_direction_random_up(b);

    if (x == -1 || y == -1) {
    	ball_set_random_start_position(b);
    } else {
    	b->x = x;
    	b->y = y;
    }

}

// رسم توپ به‌عنوان مستطیل
void ball_draw(const Ball *b)
{
	setCursor(b->y, b->x);
	write(BALL_SIGN);
}

// پاک کردن تمام خانه‌های زیر توپ
void ball_clear(const Ball *b)
{
	setCursor(b->y, b->x);
	write(' ');
}

// به‌روزرسانی موقعیت با برخورد به دیواره‌ها و سقف/کف
void ball_update(Ball *b)
{
    int8_t nextX, nextY;

    ball_next_position(b, &nextX, &nextY);

    // رسم حرکت
    ball_clear(b);
    b->x = nextX;
    b->y = nextY;
    ball_draw(b);
}


void ball_update_direction_random_up(Ball *b) {
	int tmp = rand() % 3;

	switch (tmp) {
		case 0: // left-bottom -> right-up
			b->dx = 1;
			b->dy = 1;
			break;
		case 1: // bottom -> up
			b->dx = 0;
			b->dy = 1;
			break;
		case 2: // right-bottom -> left-up
			b->dx = -1;
			b->dy = 1;
			break;
	}
}

void ball_update_direction_random_down(Ball *b) {
	int tmp = rand() % 3;

	switch (tmp) {
		case 0: // left-up -> right-bottom
			b->dx = 1;
			b->dy = -1;
			break;
		case 1: // up -> bottom
			b->dx = 0;
			b->dy = -1;
			break;
		case 2: // right-up -> left-bottom
			b->dx = -1;
			b->dy = -1;
			break;
	}
}

void ball_next_position(Ball *b, int8_t *x, int8_t *y) {
	int8_t nextX = b->x + b->dx;
	int8_t nextY = b->y + b->dy;

	// برخورد با دیواره‌های افقی
	if (nextX < b->minX || nextX > b->maxX) {
			b->dx = -b->dx;
			nextX = b->x + b->dx;
	}

	// برخورد با سقف
	if (nextY > b->maxY || nextY < b->minY) {
			b->dy = -b->dy;
			nextY = b->y + b->dy;
	}

	*x = nextX;
	*y = nextY;
}

void ball_set_random_start_position(Ball *ball) {
	int8_t minX = 1, maxX = 2, minY = 6, maxY = 12;
	int8_t x, y;

	x = (rand() % (maxX - minX)) + minX;
	y = (rand() % (maxY - minY)) + minY;

	ball->x = x;
	ball->y = y;
}
