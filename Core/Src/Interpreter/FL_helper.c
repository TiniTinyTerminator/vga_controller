/*
 * tests.c
 *
 *  Created on: 4 mei 2021
 *      Author: Daniel
 */


#include "fl_interpreter.h"
#include "fl_api_function_names.h"
#include "graphics.h"

extern Qentry cmd_queue[QUEUE_LEN];//[QUEUE_LEN];
extern Command_t function_list[];
extern int last_inQ;

int last_outQ = 0;		//last executed command;

void API_Helper_draw_line (void* argp)
{
//	API_Draw_line((int32_t) argp[0], (int32_t) argp[1], (int32_t) argp[2], (int32_t) argp[3], (uint8_t) argp[4]);
}

void API_Helper_draw_square (void* argp)
{
	int* p = (int*) argp;
	API_Draw_square((int32_t) p[0], (int32_t) p[1], (uint32_t) p[2], (uint32_t) p[3], (uint8_t) p[4]);
}

void API_Helper_draw_tekst (void* argp)
{
//	API_Draw_tekst((int32_t) argp[0], (int32_t) argp[1], (uint8_t) argp[2], (char*) argp[3], (uint8_t) argp[4], (uint8_t) argp[5],
}

void API_Helper_draw_bitmap (void* argp)
{
//	API_Draw_bitmap((uint8_t) argp[0], (int32_t) argp[1], (int32_t) argp[2]);
}

void API_Helper_fillscreen (void* argp)
{
//	API_Fill_screen((uint8_t) argp[0]);
}

void API_Next_Q(int n)
{
	Apifuncp fp;
	fp  = cmd_queue[n].funcp;
	fp(cmd_queue[n].argp);

	if (last_outQ++ == QUEUE_LEN)
		{
			last_outQ = 0;
		}
//	fp = cmd_queue;
}

void API_Init_function_list(void)
{
	function_list[0].funcp = API_Helper_draw_line;
	function_list[1].funcp = API_Helper_draw_square;
	function_list[2].funcp = API_Helper_draw_tekst;
	function_list[3].funcp = API_Helper_draw_bitmap;
	function_list[4].funcp = API_Helper_fillscreen;
}
