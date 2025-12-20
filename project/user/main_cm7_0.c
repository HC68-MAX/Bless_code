/*********************************************************************************************************************
* CYT4BB Opensourec Library 即（ CYT4BB 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是 CYT4BB 开源库的一部分
*
* CYT4BB 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          main_cm7_0
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          IAR 9.40.1
* 适用平台          CYT4BB
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者                备注
* 2024-1-4       pudding            first version
********************************************************************************************************************/

#include "zf_common_headfile.h"
#define DATA_LENGTH               (20)                                          // 数组数据长度
#pragma location = 0x28001000                                                   // 将下面这个数组定义到指定的RAM地址，#pragma需要手动分配地址，因此需要计算数据长度后再分配
float m7_1_data[DATA_LENGTH];                                         // 定义M7_1演示数据数组 浮点数类型  由于该数组已经在M7_1核心赋值过初值，因此此处不再初始化

#define PIT_Encoder                 (PIT_CH0 )                                     // 使用的周期中断编号
#define PIT_Motor                   (PIT_CH1 )                                     // 使用的周期中断编号

int main(void)
{
    clock_init(SYSTEM_CLOCK_250M); 	// 时钟配置及系统初始化<务必保留>
    debug_init();                       // 调试串口信息初始化
    // 此处编写用户代码 例如外设初始化代码等 
    pit_ms_init(PIT_Encoder, 10);                                  
    pit_ms_init(PIT_Motor,   10);    
    encoder_init();
    motor_init();
    key_gpio_init();
  while(true)
    {
      printf("%d,%d,%d\n",encoder_data_dir[1],encoder_data_dir[0],goal_speed_l);
        // 此处编写需要循环执行的代码
      system_delay_ms(10);
        // 此处编写需要循环执行的代码
      SCB_CleanInvalidateDCache_by_Addr(&m7_1_data, sizeof(m7_1_data));      // M7_0核心有Dcache 当需要读取RAM地址数据时应该更新Dcache的内容 否则可能只是读取到Dcache而不是读取的RAM
      goal_speed_l=m7_1_data[0];  // 读取M7_1核心传递过来的数据 作为左轮目标速度 单位 mm/s
      goal_speed_r=m7_1_data[0];  // 
      
    }
}
