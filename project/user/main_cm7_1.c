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
* 文件名称          main_cm7_1
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
#define DATA_LENGTH               (20)                                           // 数组数据长度
#pragma location = 0x28001000                                                   // 将下面这个数组定义到指定的RAM地址，便于其他核心直接访问(开源库默认在 0x28001000 地址保留了8kb的空间用于数据交互)                                                                               // 此处为0x28001014的原因是前面放了一个M0的数组
float m7_1_data[DATA_LENGTH] = {0};                                             // 定义 M7_1 演示数据数组 浮点数类型
uint8 Key1=0,Key2=0,Key3=0,Key4=0;  //按键变量
uint8 thres=128; //图像处理阈值
uint8 num=0;
int main(void)
{
    clock_init(SYSTEM_CLOCK_250M); 	// 时钟配置及系统初始化<务必保留>
    debug_info_init();                  // 调试串口信息初始化
    
    ips114_init();
    ips114_show_string(0, 0, "mt9v03x init.");
    while(1)
    {
        if(mt9v03x_init())
            ips114_show_string(0, 16, "mt9v03x reinit.");
        else
            break;
        system_delay_ms(500);                                                   
    }
    ips114_show_string(0, 16, "init success.");
    
    while(true)
    {
       if(Key1==1)
       {
        thres+=5;
        Key1=0;
       }
        if(Key2==1)
        {
        thres-=5;
        Key2=0;
        }


        if(mt9v03x_finish_flag)
        {  
            image_process(thres);
        }
            if( Key3==1)
            {
                num=0;
                Key3=0;
            }
            if( Key4==1)
            {
                num=1;
                Key4=0;
            }
            if(num==0)
            ips114_displayimage03x((const uint8 *)mt9v03x_image, MT9V03X_W, MT9V03X_H);
            else 
            ips114_displayimage03x((const uint8 *)black_image, MT9V03X_W, MT9V03X_H); 
            mt9v03x_finish_flag = 0;
            //m7_1_data[0] += 1;  // 演示数据变化
            float sum=0;
            uint8 num=0;
            for(uint8 i=0;i<120;i++)
            {
                if(huanchen[i]!=0){
                    sum+=huanchen[i];
                    num++;
                }
            } 
            if(num!=0)
            m7_1_data[0]=sum/num;  // 演示数据变化
            else m7_1_data[0]=0;
            SCB_CleanInvalidateDCache_by_Addr(&m7_1_data, sizeof(m7_1_data)); 
            Key1=(uint8)m7_1_data[1];
            Key2=(uint8)m7_1_data[2];
            Key3=(uint8)m7_1_data[3];
            Key4=(uint8)m7_1_data[4];
        }
    }

