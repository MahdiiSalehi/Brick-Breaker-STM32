// In the name of ALLAH!
// Mahdi Salehi

#ifndef BALL_H
#define BALL_H

#include <stdint.h>

typedef struct {
    int8_t   x;       // مختصات ستون گوشهٔ بالایی-چپی
    int8_t   y;       // مختصات سطر گوشهٔ بالایی-چپی
    int8_t   dx;      // سرعت و جهت حرکت در محور X
    int8_t   dy;      // سرعت و جهت حرکت در محور Y
    uint8_t  minX;    // حداقل ستون مجاز (معمولاً 0)
    uint8_t  maxX;    // حداکثر ستون مجاز (lcdRows - 1)
    uint8_t  minY;    // حداقل سطر مجاز (معمولاً 0)
    uint8_t  maxY;    // حداکثر سطر مجاز (lcdCols - 1)
} Ball;

// مقداردهی اولیه توپ با ابعاد دلخواه
void ball_init(Ball   *b,
							 int8_t  x,
							 int8_t  y,
               uint8_t maxX,
               uint8_t maxY);

// رسم توپ مستطیلی
void ball_draw(const Ball *b);

// پاک‌سازی منطقهٔ توپ
void ball_clear(const Ball *b);

// به‌روزرسانی موقعیت با در نظر گرفتن ابعاد توپ
// بازگشت false اگر از پایین عبور کرده باشد
void ball_update(Ball *b);

// update the direction of the ball
void ball_update_direction_random_up(Ball *b);
void ball_update_direction_random_down(Ball *b);

// get next position of the ball
void ball_next_position(Ball *b, int8_t *x, int8_t *y);

// set random start position
void ball_set_random_start_position(Ball *ball);

#endif // BALL_H
