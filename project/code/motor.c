#include "motor.h"
void motor_init(void)
{
    gpio_init(DIR_L1, GPO, GPIO_HIGH, GPO_PUSH_PULL);                           // GPIO 初始化为输出 默认上拉输出高
    pwm_init(PWM_L1, 17000, 0);                                                 // PWM 通道初始化频率 17KHz 占空比初始为 0

    gpio_init(DIR_L2, GPO, GPIO_HIGH, GPO_PUSH_PULL);                           // GPIO 初始化为输出 默认上拉输出高
    pwm_init(PWM_L2, 17000, 0);                                                 // PWM 通道初始化频率 17KHz 占空比初始为 0
}  
void motor_set_speed(int16 speed1, int16 speed2)
{
    if(speed1 >= 0)                                                             // 电机 1 正转
    {
        gpio_set_level(DIR_L1, GPIO_HIGH);                                  // DIR输出高电平
        pwm_set_duty(PWM_L1, speed1 * (PWM_DUTY_MAX / 100));                  // 计算占空比
    }
    else                                                                        // 电机 1 反转
    {
        gpio_set_level(DIR_L1, GPIO_LOW);                                       // 设置电机方向引脚为低
        pwm_set_duty(PWM_L1, -speed1 * (PWM_DUTY_MAX / 100));                  // 计算占空比
    }

    if(speed2 >= 0)                                                             // 电机 2 正转
    {
        gpio_set_level(DIR_L2, GPIO_HIGH);                                      // 设置电机方向引脚为高
        pwm_set_duty(PWM_L2, speed2 * (PWM_DUTY_MAX / 100));                  // 计算占空比
    }
    else                                                                        // 电机 2 反转
    {
        gpio_set_level(DIR_L2, GPIO_LOW);                                       // 设置电机方向引脚为低
        pwm_set_duty(PWM_L2, -speed2 * (PWM_DUTY_MAX / 100));                  // 计算占空比
    }
}