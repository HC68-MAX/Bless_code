#ifndef _ENCODER_H
#define _ENCODER_H
#include "zf_common_typedef.h"
#include "zf_common_headfile.h"
#define ENCODER_QUADDEC3                (TC_CH07_ENCODER)                       // 带方向编码器对应使用的编码器接口  
#define ENCODER_QUADDEC_A3              (TC_CH07_ENCODER_CH1_P07_6)             // A 对应的引脚                 
#define ENCODER_QUADDEC_B3              (TC_CH07_ENCODER_CH2_P07_7)             // B 对应的引脚                       

#define ENCODER_QUADDEC4                (TC_CH20_ENCODER)                       // 带方向编码器对应使用的编码器接口
#define ENCODER_QUADDEC_A4              (TC_CH20_ENCODER_CH1_P08_1)             // A 对应的引脚
#define ENCODER_QUADDEC_B4              (TC_CH20_ENCODER_CH2_P08_2)             // B 对应的引脚
extern int16 encoder_data_dir[2];
void encoder_init(void);
void encoder_quad_get_count(void);

#endif
