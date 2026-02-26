// In the name of ALLAH!
// Mahdi Salehi

#ifndef PADDLE_H
#define PADDLE_H

#include <stdint.h>
#include <stdbool.h>


typedef struct {
    int8_t   x;       // مختصات ستون گوشهٔ بالایی-چپی
    int8_t   y;       // مختصات سطر گوشهٔ بالایی-چپی
    uint8_t  minX;    // حداقل ستون مجاز
    uint8_t  maxX;    // حداکثر ستون مجاز (lcdRows)
} Paddle;

// مقداردهی اولیه‌ی Paddle
void paddle_init(Paddle *p,
                 int8_t startX,
                 int8_t startY,
                 uint8_t maxX);

// رسم Paddle به‌صورت مستطیل
void paddle_draw(const Paddle *p);

// پاک‌سازی منطقه‌ی قبلی Paddle
void paddle_clear(const Paddle *p);

// به‌روزرسانی موقعیت افقی Paddle بر پایه ورودی آنالوگ
// vol : مقدار آنالوگ [minVol…maxVol]
void paddle_update(Paddle *p,
                   uint16_t vol,
                   uint16_t minVol,
                   uint16_t maxVol);

#endif // PADDLE_H
