#ifndef _KEY_H
#define _KEY_H
#include "zf_common_typedef.h"
#include "zf_common_headfile.h"
#define KEY1                    (P20_3)
#define KEY2                    (P20_2)
#define KEY3                    (P20_1)
#define KEY4                    (P20_0)

void key_gpio_init(void);
uint8 key_scan(void);


#endif
