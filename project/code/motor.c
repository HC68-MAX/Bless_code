#include "motor.h"
int16 goal_speed_l = 0;          //左电机目标速度
int16 goal_speed_r = 0;          //右电机目标速度
int16 goal_speed = 80;            //整体目标速度
float pid_out = 0;               //pid计算后的速度
float error = 0;                 //差速误差
void pwm_calculate(void)
{
    pid_diff_speed(error);
    pid_Speed_l.target_val = goal_speed+pid_out;                               // 设置左电机目标速度
    pid_Speed_r.target_val = goal_speed-pid_out;                               // 设置右电机目标速度 
    PID_Motor(&pid_Speed_r, (float)encoder_data_dir[0]);                 // 调用左电机PID控制函数
    PID_Motor(&pid_Speed_l, (float)encoder_data_dir[1]);                 // 调用右电机PID控制函数

    motor_set_speed((int16)pid_Speed_l.actual_val, (int16)pid_Speed_r.actual_val);      // 设置电机速度
}
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
        gpio_set_level(DIR_L1, GPIO_HIGH);                                     // DIR输出高电平
        pwm_set_duty(PWM_L1, speed1 * (PWM_DUTY_MAX / 1000));                  // 计算占空比
    }
    else                                                                        // 电机 1 反转
    {
        gpio_set_level(DIR_L1, GPIO_LOW);                                       // 设置电机方向引脚为低
        pwm_set_duty(PWM_L1, -speed1 * (PWM_DUTY_MAX / 1000));                  // 计算占空比
    }

    if(speed2 >= 0)                                                             // 电机 2 正转
    {
        gpio_set_level(DIR_L2, GPIO_HIGH);                                      // 设置电机方向引脚为高
        pwm_set_duty(PWM_L2, speed2 * (PWM_DUTY_MAX / 1000));                   // 计算占空比
    }
    else                                                                        // 电机 2 反转
    {
        gpio_set_level(DIR_L2, GPIO_LOW);                                       // 设置电机方向引脚为低
        pwm_set_duty(PWM_L2, -speed2 * (PWM_DUTY_MAX / 1000));                  // 计算占空比
    }
}