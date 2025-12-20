/*
 * PID.c
 *
 *  Created on: 2024年5月5日
 *      Author: Kurumi
 */
#include "pid.h"
#include "zf_common_typedef.h"

// 初始化左右电机PID参数（根据实际调试调整）
_pid pid_Speed_l = {
    .target_val = 0,    // 初始目标值
    .actual_val = 0,       // 初始输出值
    .integral = 0,         // 初始积分值
    .err = 0, .err_last = 0, .err_previous = 0,
    .Kp = 0.02, .Ki = 0.05, .Kd = 0.1,  // PID参数
    .integral_limit = 4000.0        // 积分限幅
};

_pid pid_Speed_r = {
    .target_val = 0,
    .actual_val = 0,
    .integral = 0,
    .err = 0, .err_last = 0, .err_previous = 0,
    .Kp = 0.02, .Ki = 0.05, .Kd = 0.1,
    .integral_limit = 4000.0
};

/**
 * 电机PID控制函数（增量式PID改进版）
 * @param p: PID结构体指针
 * @param NowPlace: 当前测量值（如当前速度）
 */
void PID_Motor(_pid *p, float NowPlace)
{
    // 1. 计算当前误差
    p->err = p->target_val - NowPlace;

    // 2. 积分项处理（积分分离策略：输出未饱和时才累加积分，避免积分饱和）
    // 条件：当输出未达到上限且误差为正（需要增大输出），或未达到下限且误差为负（需要减小输出）
    if (!((p->actual_val >= DUTY_MAX && p->err > 0) || (p->actual_val <= DUTY_MIN && p->err < 0))) {
        p->integral += p->err;  // 仅在输出未饱和时累加积分
        p->integral = LimitRange(p->integral, -p->integral_limit, p->integral_limit);  // 积分限幅
    }

    // 3. 计算PID各环节输出（增量式公式优化）
    p->p_result = p->Kp * (p->err - p->err_last);  // 比例项（基于误差变化量）
    p->i_result = p->Ki * p->err;                  // 积分项（基于当前误差）
    p->d_result = p->Kd * (p->err - 2 * p->err_last + p->err_previous);  // 微分项（若需降低噪声可改为一阶差分）

    // 4. 计算总输出增量并更新实际输出
    p->actual_val += p->p_result + p->i_result + p->d_result;

    // 5. 输出限幅（限制在[DUTY_MIN, DUTY_MAX]）
    p->actual_val = LimitRange(p->actual_val, DUTY_MIN, DUTY_MAX);

    // 6. 更新误差历史（供下一周期使用）
    p->err_previous = p->err_last;  // e(k-2) = e(k-1)
    p->err_last = p->err;           // e(k-1) = e(k)
}