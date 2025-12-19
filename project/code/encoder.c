#include "encoder.h"
int16 encoder_data_dir[2]={0};
void encoder_init(void)
{
   
    encoder_quad_init(ENCODER_QUADDEC3, ENCODER_QUADDEC_A3, ENCODER_QUADDEC_B3);// 初始化编码器模块与引脚 带正交编码器模式
    encoder_quad_init(ENCODER_QUADDEC4, ENCODER_QUADDEC_A4, ENCODER_QUADDEC_B4);// 初始化编码器模块与引脚 带正交编码器模式

}
void encoder_quad_get_count(void)
{
    encoder_data_dir[0] = -encoder_get_count(ENCODER_QUADDEC3);
    encoder_clear_count(ENCODER_QUADDEC3);
    encoder_data_dir[1] = encoder_get_count(ENCODER_QUADDEC4);
    encoder_clear_count(ENCODER_QUADDEC4);
}