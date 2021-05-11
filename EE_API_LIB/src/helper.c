/**
 * @file	interpreter.c
 * @author	daniel.mul@student.hu.nl
 * @brief	De interpreter vertaald een scriptcommando naar een uitvoerbarefunctie, de argumenten uit de functies worden gecontroleerd op
 * correctheid, vervolgends wordt het vertaalde commando in de queue gezet.
 * Om te weten hoe een commando eruit ziet moet de syntax gedefinieerd worden in de "functions_list"
 * Tenslotte worden errors terug gestuurd mbv printf()
 * @version 0.4
 * @date 2021-05-11
 *
 * @copyright Copyright (c) 2021
*/

#include "interpreter.h"
#include "api_function_names.h"

#include "graphics.h"

#include <stddef.h>

#include "stm32f4xx_hal.h"

#include "imgs/angry_smiley.h"
#include "imgs/happy_smiley.h"
#include "imgs/me.h"


extern Qentry cmd_queue[QUEUE_LEN]; //[QUEUE_LEN];
extern int last_inQ;

Command_t function_list[15]=
{
		{"lijn", 		6,	{T_GETAL, T_GETAL, T_GETAL, T_GETAL, T_KLEUR, T_GETAL}},
		{"rechthoek", 	6,	{T_GETAL, T_GETAL, T_GETAL, T_GETAL, T_KLEUR, T_GETAL}},
		{"tekst", 		7,	{T_GETAL, T_GETAL, T_KLEUR, T_TEKST, T_FONTNAAM, T_GETAL, T_FONTSTIJL}},
		{"bitmap", 		3,	{T_GETAL, T_GETAL, T_GETAL}},
		{"clearscherm",	1,	{T_KLEUR}},
		{"wacht",		1,	{T_GETAL}},
		//herhaal, 			aantal (cmd), hoevaak (herhalen)
		{"herhaal",		2,	{T_GETAL, T_GETAL}},
		//cirkel, x, y, radius, kleur
		{"cirkel",		4,	{T_GETAL, T_GETAL, T_GETAL, T_KLEUR}},
		//figuur, x1,y1, x2,y2, x3,y3, x4,y4, x5,y5, kleur
		{"figuur",		11,	{T_GETAL, T_GETAL, T_GETAL, T_GETAL, T_GETAL, T_GETAL, T_GETAL, T_GETAL, T_GETAL, T_GETAL, T_KLEUR}},
		//toren,
		{END_OF_LIST}
};


int last_outQ = 0; //last executed command;

int repeat_line = 0; //line at which will be repeated

extern uint32_t wait_time;
extern uint32_t start_time;

void API_Helper_draw_line(void *argp)
{
	int *p = (int *)argp;
	API_Draw_line((int32_t)p[0], (int32_t)p[1], (int32_t)p[2], (int32_t)p[3], (uint32_t)p[4], (uint8_t)p[5], DOT);
}

void API_Helper_draw_square(void *argp)
{
	int *p = (int *)argp;
	if((uint32_t)p[5] == 0)
		API_Draw_square((int32_t)p[0], (int32_t)p[1], (uint32_t)p[2], (uint32_t)p[3], (uint8_t)p[4], 1);
	else
		API_Fill_square((int32_t)p[0], (int32_t)p[1], (uint32_t)p[2], (uint32_t)p[3], (uint8_t)p[4]);
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
	switch (p[0])
	{
	case 0:
		API_Load_bitmap((uint8_t) p[1], (int32_t) p[2], ME_WIDTH, ME_HEIGHT, me_map);
		break;
	case 1:
		API_Load_bitmap((uint8_t) p[1], (int32_t) p[2], HAPPY_SMILEY_WIDTH, HAPPY_SMILEY_HEIGHT, happy_smiley_map);
		break;
	case 2:
		API_Load_bitmap((uint8_t) p[1], (int32_t) p[2], HAPPY_SMILEY_WIDTH, HAPPY_SMILEY_HEIGHT, angry_smiley_map);
		break;
	default:
		break;
	}
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

	wait_time = waittime;
	start_time = HAL_GetTick();

	if (wait_time < HAL_MAX_DELAY)
	{
		wait_time += (uint32_t)(uwTickFreq);
	}
}

//TODO add safeguard when repeat is longer then queue;
void API_Helper_repeat(void *argp)
{
	int *p = (int *)argp;
	int nCommands = p[0];
	int times = p[1];

	if (times == 0)
		return;
	p[1] = p[1] - 1;

	last_outQ = last_outQ - (nCommands + 1);
	if (last_outQ < 0)
	{
		last_outQ = QUEUE_LEN - last_outQ;
	}
}

void API_Helper_draw_circle(void *argp)
{
	int *p = (int *)argp;
	API_Draw_circle((int32_t)p[0], (int32_t)p[1], (int32_t)p[2], (uint8_t)p[3], 1);
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
