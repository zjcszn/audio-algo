/* ================================================================== */
/*                                                                    */ 
/*    Microsoft Speech coder     ANSI-C Source Code                   */
/*    SC1200 1200 bps speech coder                                    */
/*    Fixed Point Implementation      Version 7.0                     */
/*    Copyright (C) 2000, Microsoft Corp.                             */
/*    All rights reserved.                                            */
/*                                                                    */ 
/* ================================================================== */

/* ========================================= */
/* melp.c: Mixed Excitation LPC speech coder */
/* ========================================= */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

#if NPP
#include "npp.h"
#endif

#define X05_Q7				64         /* 0.5 * (1 << 7) */
#define THREE_Q7			384        /* 3 * (1 << 7) */

/* ====== External memory ====== */

int16_t	mode;
int16_t   chwordsize;

/* ========== Static definations ========== */

#define PROGRAM_NAME			"SC1200 1200 bps speech coder"
#define PROGRAM_VERSION			"Version 7 / 42 Bits"
#define PROGRAM_DATE			"10/25/2000"

/* ========== Static Variables ========== */

char in_name[256], out_name[256];

/* ========== Local Private Prototypes ========== */

static void		parseCommandLine(int argc, char *argv[]);
static void		printHelpMessage(char *argv[]);

static char *cmd_line[] = {"melpe", "-i", "test_in.raw", "-o", "test_out.raw", 0};

extern int main_cmd(int argc, char *argv[]);
int main()
{
	main_cmd(5, cmd_line);
}


/****************************************************************************
**
** Function:        main
**
** Description:     The main function of the speech coder
**
** Arguments:
**
**  int     argc    ---- number of command line parameters
**  char    *argv[] ---- command line parameters
**
** Return value:    None
**
*****************************************************************************/
int main_cmd(int argc, char *argv[])
{
	int32_t	length;
	int16_t	speech_in[BLOCK], speech_out[BLOCK];
	int16_t	bitBufSize, bitBufSize12, bitBufSize24;
                                          /* size of the bitstream buffer */
	BOOLEAN		eof_reached = FALSE;
	FILE	*fp_in, *fp_out;

	/* ====== Get input parameters from command line ====== */
	parseCommandLine(argc, argv);

	/* ====== Open input, output, and parameter files ====== */
	if ((fp_in = fopen(in_name,"rb")) == NULL){
		printf("  ERROR: cannot read file %s.\n", in_name);
		exit(1);
	}
	if ((fp_out = fopen(out_name,"wb")) == NULL){
		printf("  ERROR: cannot write file %s.\n", out_name);
		exit(1);
	}

	/* ====== Initialize MELP analysis and synthesis ====== */
	if (rate == RATE2400)
		frameSize = (int16_t) FRAME;
	else
		frameSize = (int16_t) BLOCK;
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
    }else{
        printf("Channel word size is wrong!\n");
        exit(-1);
    }

    if (rate == RATE2400){
		frameSize = FRAME;
		bitBufSize = bitBufSize24;
	} else {
		frameSize = BLOCK;
		bitBufSize = bitBufSize12;
	}

	if (mode != SYNTHESIS)
		melp_ana_init();
	if (mode != ANALYSIS)
		melp_syn_init();


	/* ====== Run MELP coder on input signal ====== */

	frame_count = 0;
	eof_reached = FALSE;
	while (!eof_reached){
		printf("Frame = %ld\r", frame_count);

		if (mode == DOWN_TRANS){
			/* --- Read 2.4 channel input --- */
            if( chwordsize == 8 ){
			    length = fread(chbuf, sizeof(unsigned char),
						   (bitBufSize24*NF), fp_in);
            }else{
    			int i, readNum;
				unsigned int bitData;
				for(i = 0; i < bitBufSize24*NF; i++){
					readNum = fread(&bitData,sizeof(unsigned int),1,fp_in);
					if( readNum != 1 )	break;
					chbuf[i] = (unsigned char)bitData;
				}	
				length = i;		
            }

			if (length < (bitBufSize24*NF)){
				eof_reached = TRUE;
				break;
			}
			transcode_down();
			/* --- Write 1.2 channel output --- */
            if( chwordsize == 8 ){
			    fwrite(chbuf, sizeof(unsigned char), bitBufSize12, fp_out);
            }else{
				int i;
				unsigned int bitData;
				for(i = 0; i < bitBufSize12; i++){
					bitData = (unsigned int)(chbuf[i]);
					fwrite(&bitData, sizeof(unsigned int), 1, fp_out);
				}
			}
		} else if (mode == UP_TRANS){
			/* --- Read 1.2 channel input --- */
            if( chwordsize == 8 ){
			    length = fread(chbuf, sizeof(unsigned char), bitBufSize12, fp_in);
            }else{
    			int i, readNum;
				unsigned int bitData;
				for(i = 0; i < bitBufSize12; i++){
					readNum = fread(&bitData,sizeof(unsigned int),1,fp_in);
					if( readNum != 1 )	break;
					chbuf[i] = (unsigned char)bitData;
				}	
				length = i;		
            }

			if (length < bitBufSize12){
				eof_reached = TRUE;
				break;
			}
			transcode_up();
			/* --- Write 2.4 channel output --- */
            if( chwordsize == 8 ){
			    fwrite(chbuf, sizeof(unsigned char), (bitBufSize24*NF), fp_out);
            }else{
				int i;
				unsigned int bitData;
				for(i = 0; i < bitBufSize24*NF; i++){
					bitData = (unsigned int)(chbuf[i]);
					fwrite(&bitData, sizeof(unsigned int), 1, fp_out);
				}
			}

		} else {
			/* Perform MELP analysis */
			if (mode != SYNTHESIS){
				/* read input speech */
				length = readbl(speech_in, fp_in, frameSize);
				if (length < frameSize){
					v_zap(&speech_in[length], (int16_t) (FRAME - length));
					eof_reached = TRUE;
				}

				/* ---- Noise Pre-Processor ---- */
#if NPP
				if (rate == RATE1200){
					npp(speech_in, speech_in);
					npp(&(speech_in[FRAME]), &(speech_in[FRAME]));
					npp(&(speech_in[2*FRAME]), &(speech_in[2*FRAME]));
				} else
					npp(speech_in, speech_in);
#endif
				analysis(speech_in, melp_par);

				/* ---- Write channel output if needed ---- */
                if (mode == ANALYSIS){
                    if( chwordsize == 8 ){
					    fwrite(chbuf, sizeof(unsigned char), bitBufSize, fp_out);
                    }else{
        				int i;
		        		unsigned int bitData;
				        for(i = 0; i < bitBufSize; i++){
					        bitData = (unsigned int)(chbuf[i]);
					        fwrite(&bitData, sizeof(unsigned int), 1, fp_out);
				        }
			        }
                }
			}

			/* ====== Perform MELP synthesis (skip first frame) ====== */
			if (mode != ANALYSIS){

				/* Read channel input if needed */
				if (mode == SYNTHESIS){
                    if( chwordsize == 8 ){
					    length = fread(chbuf, sizeof(unsigned char), bitBufSize,
						    		   fp_in);
                    }else{
    		        	int i, readNum;
        				unsigned int bitData;
		        		for(i = 0; i < bitBufSize; i++){
				        	readNum = fread(&bitData,sizeof(unsigned int),1,fp_in);
        					if( readNum != 1 )	break;
		        			chbuf[i] = (unsigned char)bitData;
				        }	
        				length = i;		
                    }
					if (length < bitBufSize){
						eof_reached = TRUE;
						break;
					}
				}
				synthesis(melp_par, speech_out);
				writebl(speech_out, fp_out, frameSize);
			}
		}
		frame_count ++;
	}

	fclose(fp_in);
	fclose(fp_out);
	printf("\n\n");

	return(0);
}


/****************************************************************************
**
** Function:        parseCommandLine
**
** Description:     Translate command line parameters
**
** Arguments:
**
**  int     argc    ---- number of command line parameters
**  char    *argv[] ---- command line parameters
**
** Return value:    None
**
*****************************************************************************/
static void		parseCommandLine(int argc, char *argv[])
{
	register int16_t	i;
	BOOLEAN		error_flag = FALSE;

	if (argc < 2)
		error_flag = TRUE;

	/* Setting default values. */
	mode = ANA_SYN;
	rate = RATE2400;
  chwordsize = 8;         // this is for packed bitstream
	in_name[0] = '\0';
	out_name[0] = '\0';

	for (i = 1; i < argc; i++){
		if ((strncmp(argv[i], "-h", 2 ) == 0) ||
			(strncmp(argv[i], "-help", 5) == 0)){
			printHelpMessage(argv);
			exit(0);
		} else if ((strncmp(argv[i], "-a", 2)) == 0)
			mode = ANALYSIS;
		else if ((strncmp(argv[i], "-s", 2)) == 0)
			mode = SYNTHESIS;
		else if ((strncmp(argv[i], "-l", 2)) == 0)
			rate = RATE1200;
		else if ((strncmp(argv[i], "-u", 2)) == 0)
			mode = UP_TRANS;
		else if ((strncmp(argv[i], "-d", 2)) == 0)
			mode = DOWN_TRANS;
		else if ((strncmp(argv[i], "-i", 2)) == 0){
			i++;
			if (i < argc)
				strcpy(in_name, argv[i]);
			else
				error_flag = TRUE;
		} else if ((strncmp(argv[i], "-o", 2)) == 0){
			i++;
			if (i < argc)
				strcpy(out_name, argv[i]);
			else
				error_flag = TRUE;
		} else if ((strncmp(argv[i], "-p", 2)) == 0){
            // for backword compatibility with 2.4 kbps MELP ref. coder
			chwordsize = 6;
		} else
			error_flag = TRUE;
	}

	if ((in_name[0] == '\0') || (out_name[0] == '\0'))
		error_flag = TRUE;

	if (error_flag){
		printHelpMessage(argv);
		exit(1);
	}

	printf("\n\n\t%s %s, %s\n\n", PROGRAM_NAME, PROGRAM_VERSION,
			PROGRAM_DATE);
	switch (mode){
	case ANA_SYN:
	case ANALYSIS:
	case SYNTHESIS:
		if (rate == RATE2400)
			printf(" ---- 2.4kbps mode.\n");
		else
			printf(" ---- 1.2kbps mode.\n");
		break;
	}
	switch (mode){
	case ANA_SYN:
		printf(" ---- Analysis and Synthesis.\n"); break;
	case ANALYSIS:
		printf(" ---- Analysis only.\n"); break;
	case SYNTHESIS:
		printf(" ---- Synthesis only.\n"); break;
	case UP_TRANS:
		printf(" ---- Transcoding from 1.2kbps to 2.4kbps.\n"); break;
	case DOWN_TRANS:
		printf(" ---- Transcoding from 2.4kbps to 1.2kbps.\n"); break;
	}

	printf( " ---- input from %s.\n", in_name);
	printf( " ---- output to %s.\n", out_name);
}


/****************************************************************************
**
** Function:        printHelpMessage
**
** Description:     Print Command Line Usage
**
** Arguments:
**
** Return value:    None
**
*****************************************************************************/
static void		printHelpMessage(char *argv[])
{
	printf("\n\n\t%s %s, %s\n\n", PROGRAM_NAME, PROGRAM_VERSION,
			PROGRAM_DATE);
	printf("Usage:\n");
	printf("\t%s [-l] [-asudp] -i infile -o outfile\n", argv[0]);
	printf("\t\tdefault: Analysis/Synthesis at 2.4kbps\n");
	printf("\t\t-a --analysis\tAnalysis only\n");
	printf("\t\t-s --synthesis\tSynthesis only\n");
	printf("\t\t-l --low rate\t1.2kbps coding\n\n");
	printf("\t\t-u --transcoder from 1.2kbps to 2.4kpbs\n");
	printf("\t\t-d --transcoder from 2.4kbps to 1.2kbps\n");
  printf("\t\t-p --using unpacked bitstream for backward compatibility\n\n");
}
