/*
 * PID.h
 *
 *  Created on: 2024年5月5日
 *      Author: Kurumi
 */
#include "zf_common_headfile.h"

#ifndef _PID_H_
#define _PID_H_

// 通用范围限幅宏（限制x在[min_val, max_val]之间）
#define LimitRange(x, min_val, max_val)  (x < min_val ? min_val : (x > max_val ? max_val : x))

#define DUTY_MAX          3000  // 电机最大占空比
#define DUTY_MIN          -3000     // 电机最小占空比

typedef struct
{
    float target_val;        // 目标值（如目标速度）
    float actual_val;        // 实际输出值（如实际占空比）
    float integral;          // 积分累计值

    float err;               // 当前误差（e(k) = 目标值 - 实际值）
    float err_last;          // 上一时刻误差（e(k-1)）
    float err_previous;      // 上两时刻误差（e(k-2)）

    float Kp;                // 比例系数
    float Ki;                // 积分系数
    float Kd;                // 微分系数
    float integral_limit;    // 积分限幅（防止积分饱和）
    float p_result;          // 比例项输出
    float i_result;          // 积分项输出
    float d_result;          // 微分项输出
} _pid;  // 移除未使用的inte_exce字段

extern _pid pid_Speed_r, pid_Speed_l;
extern void PID_Motor(_pid *p, float NowPlace);  // 电机PID控制函数

#endif