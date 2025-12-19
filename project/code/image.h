#ifndef _IMAGE_H
#define _IMAGE_H
#include "zf_common_typedef.h"
#include "zf_common_headfile.h"

#define image_w			188		//图像宽度
#define image_h			120		//图像高度

#define uesr_RED     0XF800    //红色
#define uesr_GREEN   0X07E0    //绿色
#define uesr_BLUE    0X001F    //蓝色

#define white_pixel	255
#define black_pixel	0
extern uint8 black_image[image_h][image_w];
extern int huanchen[image_h];
extern uint8 original_image[image_h][image_w];
extern uint8 bin_image[image_h][image_w];//图像数组
uint8 otsuThreshold(uint8 *image, uint16 col, uint16 row);
void turn_to_bin(void);
void image_process(uint8 Threshold);
uint8 check(uint8 numl,uint8 num2,uint8 thres);

#endif
