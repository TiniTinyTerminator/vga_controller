/**
 * @file	api_function_names.h
 * @author	daniel.mul@student.hu.nl
 * @brief	Definities en types zodat de interpreter de commands kan begrijpen
 * @version 0.6
 * @date 2021-05-12
 *
 * @copyright Copyright (c) 2021
*/

#ifndef _INC_FL_API_FUNCTION_NAMES_H_
#define _INC_FL_API_FUNCTION_NAMES_H_

#include "interpreter.h"

#include <stdint.h>
/**
 * @brief ennum for argumenttypes
 */
typedef enum ID_ARGUMENT_TYPE
{
	T_GETAL,
	T_TEKST,
	T_KLEUR,
	T_FONTNAAM,
	T_FONTSTIJL,
	T_KOMMA,
}Arg_t;

/**
 * @brief container for functions
 */
typedef struct Functions
{
	char name[20];
	uint8_t argc;
	Arg_t argt[11];
	Apifuncp funcp;
}Command_t;

/**
 * @brief container for colours
 */
typedef struct Colours
{
	char name[15];
	int8_t hexdef;
}Colour_t;

/**
 * @brief list of colours with corresponding 8bit code
 */
static const Colour_t colour_list[] =
{
		{"zwart",		0b00000000},
		{"blauw",		0b00000011},
		{"lichtblauw",	0b00000110},
		{"groen",		0b00011100},
		{"lichtgroen",	0b01010000},
		{"cyaan",		0b00011111},
		{"lichtcyaan",	0b00001101},
		{"rood",		0b11100000},
		{"lichtrood",	0b01000000},
		{"magenta",		0b11100011},
		{"lichtmagenta",0b01000101},
		{"bruin",		0b01100100},
		{"geel",		0b11111100},
		{"grijs",		0b01001001},
		{"wit",			0b11111111},
		{"rose",		0b11101001},
		{"paars",		0b01000001},
		{END_OF_LIST}
};

/**
 * @brief container for fontnames
 */
typedef struct Fontnames
{
	char name[15];
	uint8_t id;
}Fontname_t;

/**
 * @brief list of fontnames with id
 */
static const Fontname_t fontname_list[] =
{
	{"arial",		0},
	{"consolas",	1},
	{END_OF_LIST}
};

/**
 * @brief enum for fontstyles
 */
typedef enum ID_FONTSYLE
{
	T_NORMAAL,
	T_VET,
	T_CURSIEF,
}Fontstyles;

/**
 * @brief container for fontstyles
 */
typedef struct Fontstyles
{
	char name[15];
	Fontstyles id;
}Fontstyle_t;

/**
 * @brief list of fontstyles and corresponding ID.
 */
static const Fontstyle_t fontstyle_list[] =
{
	{"normaal",	T_NORMAAL},
	{"vet", 	T_VET},
	{"cursief",	T_CURSIEF},
	{END_OF_LIST}
};

#endif /* _INC_FL_API_FUNCTION_NAMES_H_ */
