

#include "npp.h"
#include "global.h"
#include "sc1200.h"
#include "mat_lib.h"
#include "global.h"
#include "macro.h"
#include "mathhalf.h"
#include "dsp_sub.h"
#include "melp_sub.h"
#include "constant.h"
#include "math_lib.h"
#include "math.h"
#include "transcode.h"
#include "npp.h"
#include "MelpeC.h"


int16_t bitBufSize, bitBufSize12, bitBufSize24;
	
	
void NoiseS_init(void)
{
	rate = RATE2400;
	/* ====== Initialize MELP analysis and synthesis ====== */
	if (rate == RATE2400)
		frameSize = FRAME;
	else
		frameSize = BLOCK;
	/* Computing bit=Num = rate * frameSize / FSAMP.  Note that bitNum        */
	/* computes the number of bytes written to the channel and it has to be   */
	/* exact.  We first carry out the division and then have the multiplica-  */
	/* tion with rounding.                                                    */
    bitNum12 = 81;
    bitNum24 = 54;
    if( chwordsize == 8 ){
        // packing the bitstream
        bitBufSize12 = 11;
        bitBufSize24 = 7;
    }else if( chwordsize == 6 ){
        bitBufSize12 = 14;
        bitBufSize24 = 9;
    }

    if (rate == RATE2400){
		frameSize = FRAME;
		bitBufSize = bitBufSize24;
	} else {
		frameSize = BLOCK;
		bitBufSize = bitBufSize12;
	}
	
	melp_ana_init();
	npp_init();	
}


void NoiseSuppression(int16_t *in,int16_t *out)
{
	npp(in,out);
}
