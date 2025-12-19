#ifndef _MOTOR_H
#define _MOTOR_H
#include "zf_common_typedef.h"
#include "zf_common_headfile.h"
#define DIR_L1              (P05_3)
#define PWM_L1              (TCPWM_CH11_P05_2)
#define DIR_L2              (P05_1)
#define PWM_L2              (TCPWM_CH09_P05_0)
void pwm_calculate(void);
void motor_init(void);
void motor_set_speed(int16 speed1, int16 speed2);

extern int16 goal_speed_l;
extern int16 goal_speed_r;

#endif
