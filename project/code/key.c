#include "key.h"
void key_init(void)
{
    gpio_init(KEY1, GPI, GPIO_HIGH, GPI_PULL_UP);                                // 按键1 初始化为输入 上拉
    gpio_init(KEY2, GPI, GPIO_HIGH, GPI_PULL_UP);                                // 按键2 初始化为输入 上拉
    gpio_init(KEY3, GPI, GPIO_HIGH, GPI_PULL_UP);                                // 按键3 初始化为输入 上拉
    gpio_init(KEY4, GPI, GPIO_HIGH, GPI_PULL_UP);                                // 按键4 初始化为输入 上拉
}
uint8 key_scan(void)
{
    if(!gpio_get_level(KEY1))                                                    // 按键1 按下
    {
        system_delay_ms(10);                                                     // 消抖
        while(!gpio_get_level(KEY1));                                            // 等待按键松开
        system_delay_ms(10);                                                     // 消抖
        return 1;
    }
    if(!gpio_get_level(KEY2))                                                    // 按键2 按下
    {
        system_delay_ms(10);                                                     // 消抖
        while(!gpio_get_level(KEY2));                                            // 等待按键松开
        system_delay_ms(10);                                                     // 消抖
        return 2;
    }
    if(!gpio_get_level(KEY3))                                                    // 按键3 按下
    {
        system_delay_ms(10);                                                     // 消抖
        while(!gpio_get_level(KEY3));                                            // 等待按键松开
        system_delay_ms(10);                                                     // 消抖
        return 3;
    }
    if(!gpio_get_level(KEY4))                                                    // 按键4 按下
    {
        system_delay_ms(10);                                                     // 消抖
        while(!gpio_get_level(KEY4));                                            // 等待按键松开
        system_delay_ms(10);                                                     // 消抖
        return 4;
    }
    return 0;                                                                    // 无按键按下
}