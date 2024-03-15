#ifndef __NOISES_SUP_H
#define __NOISES_SUP_H

#include <stdint.h>

#define FRAME_SIZE	180		//降噪音频输入大小
													//s16 

void NoiseS_init(void);		//降噪初始化
void NoiseSuppression(int16_t *in,int16_t *out);	//降噪处理,输入和输出buf必须大小为 int16_t[180]


#endif

