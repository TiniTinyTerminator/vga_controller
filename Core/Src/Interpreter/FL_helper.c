/**
 * tests.c
 *
 *  Created on: 4 mei 2021
 *      Author: Daniel
 */

#include "FL_interpreter.h"
#include "FL_api_function_names.h"
#include "graphics.h"
#include "stddef.h"
#include "stm32f4xx_hal.h"

extern Qentry cmd_queue[QUEUE_LEN]; //[QUEUE_LEN];
extern Command_t function_list[];
extern int last_inQ;

int last_outQ = 0; //last executed command;

int repeat_line = 0; //line at which will be repeated

void API_Helper_draw_line(void *argp)
{
	int *p = (int *)argp;
	API_Draw_line((int32_t)p[0], (int32_t)p[1], (int32_t)p[2], (int32_t)p[3], (uint32_t)p[4], (uint8_t)p[5], DOT);
}

void API_Helper_draw_square(void *argp)
{
	int *p = (int *)argp;
	API_Draw_square((int32_t)p[0], (int32_t)p[1], (uint32_t)p[2], (uint32_t)p[3], (uint8_t)p[4], (uint32_t)p[5]);
}

//TODO implement API function
void API_Helper_draw_tekst(void *argp)
{
	int *p = (int *)argp;
	//API_Draw_tekst((int32_t) argp[0], (int32_t) argp[1], (uint8_t) argp[2], (char*) argp[3], (uint8_t) argp[4], (uint8_t) argp[5], (uint8_t) argp[6]);
}

//TODO add switch case for bit maps
void API_Helper_draw_bitmap(void *argp)
{
	int *p = (int *)argp;
	//	API_Load_bitmap((uint8_t) p[0], (int32_t) p[1], (int32_t) p[2]);
}

void API_Helper_fillscreen(void *argp)
{
	int *p = (int *)argp;
	API_Fill_screen((uint8_t)p[0]);
}

//TODO add timer
void API_Helper_wait(void *argp)
{
	int *p = (int *)argp;
	uint32_t waittime = (uint32_t)p[0];

	HAL_Delay(waittime);
}

//TODO add safeguard when repeat is longer then queue;
void API_Helper_repeat(void *argp)
{
	int *p = (int *)argp;
	int count = p[0];
	int times = p[1];

	if (times == 0)
		return;
	p[1] = p[1] - 1;

	last_outQ = last_outQ - (count + 1);
	if (last_outQ < 0)
	{
		last_outQ = QUEUE_LEN - last_outQ;
	}
}

void API_Helper_draw_circle(void *argp)
{
	int *p = (int *)argp;
	API_Draw_circle((int32_t)p[0], (int32_t)p[1], (int32_t)p[2], (uint8_t)p[3], (uint32_t)p[4]);
}

void API_Helper_draw_figure(void *argp)
{
	int *p = (int *)argp;

	const int32_t list_X[] = {(int32_t)p[0], (int32_t)p[2], (int32_t)p[4], (int32_t)p[6], (int32_t)p[8]};
	const int32_t list_Y[] = {(int32_t)p[1], (int32_t)p[3], (int32_t)p[5], (int32_t)p[7], (int32_t)p[9]};

	API_Draw_polygon(list_X, list_Y, (uint32_t)5, (uint8_t)p[10], 1, DOT);
}

void API_Next_Q(void)
{
	Apifuncp fp;
	if (last_outQ <= last_inQ)
	{
		fp  = cmd_queue[last_outQ].funcp;
		if (fp != NULL)
		{
			fp(cmd_queue[last_outQ].argp);
		}

		if (last_outQ++ == QUEUE_LEN)
		{
			last_outQ = 0;
		}
	}
}

void API_Init_function_list(void)
{
	int i = 0;
	function_list[i++].funcp = API_Helper_draw_line;
	function_list[i++].funcp = API_Helper_draw_square;
	function_list[i++].funcp = API_Helper_draw_tekst;
	function_list[i++].funcp = API_Helper_draw_bitmap;
	function_list[i++].funcp = API_Helper_fillscreen;
	function_list[i++].funcp = API_Helper_wait;
	function_list[i++].funcp = API_Helper_repeat;
	function_list[i++].funcp = API_Helper_draw_circle;
	function_list[i++].funcp = API_Helper_draw_figure;
}
