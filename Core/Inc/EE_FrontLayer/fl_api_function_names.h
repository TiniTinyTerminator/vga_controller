/*
 * fl_api_function_names.h
 *
 *  Created on: Apr 28, 2021
 *      Author: Daniel
 */
//@NOTE geef een korte beschrijving van wat er in deze header file gezet wordt en vergeet niet de doxygen variabelen te declareren (@author, @file, @date, @)
//@NOTE dubbele underscores aan beide kanten van een C header definitie

#ifndef INC_FL_API_FUNCTION_NAMES_H_
#define INC_FL_API_FUNCTION_NAMES_H_

#include <stdint.h>

typedef enum ID_ARGUMENT_TYPE
{
	T_GETAL,
	T_TEKST,
	T_KLEUR,
	T_FONTNAAM,		//nog niet aangemaakt
	T_FONTSTIJL,	//nog niet aangemaakt
	T_COORDINAAT,		//nog niet in gebruik
}Arg_t;

typedef struct Functions
{
	char name[20];
	uint8_t argc;
	Arg_t argt[6];
	Apifuncp funcp;
}Command_t;

typedef struct Colours
{
	char name[15];
	int32_t hexdef;
}Colour_t;

//according to: https://flaviocopes.com/rgb-color-codes/
static const Colour_t colour_list[] =
{
		{"zwart",		0x000000},
		{"blauw",		0x0000FF},
		{"lichtblauw",	0xADD8E6},
		{"groen",		0x008000},
		{"lichtgroen",	0x90EE90},
		{"cyaan",		0x00FFFF},
		{"lichtcyaan",	0xE0FFFF},
		{"rood",		0xFF0000},
		{"lichtrood",	0x800000},
		{"magenta",		0xFF00FF},
		{"lichtmagenta",0xEE82EE},
		{"bruin",		0xA52A2A},
		{"geel",		0xFF00FF},
		{"grijs",		0x808080},
		{"wit",			0xFFFFFF},
		{"rose",		0xFFC0CB},			//Bonus
		{"paars",		0x800080},
		{"END_OF_LIST\0"}
};

typedef struct Fontnames
{
	char name[15];
	uint8_t id;
}Fontname_t;

static const Fontname_t fontname_list[] =
{
	{"arial",		0},
	{"consolas",	1},
	{"END_OF_LIST\0"}
};

typedef enum ID_FONTSYLE
{
	T_NORMAAL,
	T_VET,
	T_CURSIEF,
}Fontstyles;

typedef struct Fontstyles
{
	char name[15];
	Fontstyles id;
}Fontstyle_t;

static const Fontstyle_t fontstyle_list[] =
{
	{"normaal" , T_NORMAAL},
	{"vet", T_VET},
	{"cursief", T_CURSIEF},
	{"END_OF_LIST\0"}
};

#endif /* INC_FL_API_FUNCTION_NAMES_H_ */
