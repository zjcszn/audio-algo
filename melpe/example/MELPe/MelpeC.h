#ifndef __NOISES_SUP_H
#define __NOISES_SUP_H

#include <stdint.h>

#define FRAME_SIZE	180		//������Ƶ�����С
													//s16 

void NoiseS_init(void);		//�����ʼ��
void NoiseSuppression(int16_t *in,int16_t *out);	//���봦��,��������buf�����СΪ int16_t[180]


#endif

