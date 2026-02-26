// In the name of ALLAH!
// Mahdi Salehi

#ifndef BLOCK_H
#define BLOCK_H

#include <stdint.h>
#include <stdbool.h>

// شمارندهٔ انواع بلوک
typedef enum {
    BLOCK_NORMAL,   // معمولی
    BLOCK_NEGATIVE, // منفی
    BLOCK_HEALTH,   // سلامتی
    BLOCK_BALL,     // توپ اضافی
    BLOCK_LUCK,     // شانس
    BLOCK_TYPE_COUNT
} BlockType;

// اطلاعات ثابت هر نوع بلوک (بدون نام)
typedef struct {
    uint8_t symbol; 	// کاراکتر برای LCD
    int16_t score;    // امتیاز
} BlockInfo;

// آرایهٔ ثابت نگاشت نوع به نماد و امتیاز
extern const BlockInfo blockInfo[BLOCK_TYPE_COUNT];

// هر نمونهٔ بلوک روی صفحه
typedef struct {
    uint8_t   x, y;    // مختصات روی LCD
    BlockType type;    // نوع بلوک
    bool      active;  // وضعیت فعال/شکسته
} Block;

// پروتوتایپ توابع
void block_init(Block *b, uint8_t x, uint8_t y, BlockType t);
void block_draw(const Block *b);
void block_destroy(Block *b);
int16_t get_block_score(Block *b);

BlockType random_block_type(void);
BlockType random_luck_block_type(void);

#endif // BLOCK_H
