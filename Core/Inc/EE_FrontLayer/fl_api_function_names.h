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
	Arg_t argt[7];
	Apifuncp funcp;
}Command_t;

typedef struct Colours
{
	char name[15];
	int8_t hexdef;
}Colour_t;

//according to: https://flaviocopes.com/rgb-color-codes/
static const Colour_t colour_list[] =
{
		{"zwart",		0b00000000},
		{"blauw",		0b11000000},
		{"lichtblauw",	0b10010000},
		{"groen",		0b00111000},
		{"lichtgroen",	0b01100000},
		{"cyaan",		0b11111000},
		{"lichtcyaan",	0b11110010},
		{"rood",		0b00000111},
		{"lichtrood",	0b00000100},
		{"magenta",		0b00111111},
		{"lichtmagenta",0x01101101},
		{"bruin",		0b01010011},
		{"geel",		0b00111111},
		{"grijs",		0b10100100},
		{"wit",			0b11111111},
		{"rose",		0b01011111},
		{"paars",		0b10000100},
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
	{"normaal",	T_NORMAAL},
	{"vet", 	T_VET},
	{"cursief",	T_CURSIEF},
	{"END_OF_LIST\0"}
};

#endif /* INC_FL_API_FUNCTION_NAMES_H_ */
