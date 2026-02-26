// In the name of ALLAH!
// Mahdi Salehi

#include "paddle.h"
#include "LiquidCrystal.h"
#include "custom_chars.h"

// مقداردهی اولیه
void paddle_init(Paddle *p,
                 int8_t startX,
                 int8_t startY,
                 uint8_t maxX)
{
    p->x      = startX;
    p->y      = startY;
    p->minX   = 0;
    p->maxX   = maxX;
}

// رسم به صورت مستطیل
void paddle_draw(const Paddle *p)
{
	setCursor(p->y, p->x);
	write(PADDLE_SIGN);
}

// پاک‌سازی مستطیل قبلی
void paddle_clear(const Paddle *p)
{
	setCursor(p->y, p->x);
	write(' ');
}

// به‌روزرسانی بر اساس ورودی آنالوگ
void paddle_update(Paddle *p,
                   uint16_t vol,
                   uint16_t minVol,
                   uint16_t maxVol)
{
    // نگاشت vol به بازه [minX…maxX]
    int32_t rangeVol = maxVol - minVol;
    int32_t rangePos = p->maxX - p->minX;
    int8_t newX = p->minX +
        (int32_t)(vol - minVol) * rangePos / rangeVol;

    // محدود کردن
    if (newX < p->minX) newX = p->minX;
    if (newX > p->maxX) newX = p->maxX;

    // اگر تغییر کرده باشد، پاک و رسم مجدد
    if (newX != p->x) {
        paddle_clear(p);
        p->x = newX;
        paddle_draw(p);
    }
}
