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
}Function;

const Function function_lists[10]=
{
		{"lijn", 		6,	{T_GETAL, T_GETAL, T_GETAL, T_GETAL, T_KLEUR, T_GETAL}},
		{"rechthoek", 	6,	{T_GETAL, T_GETAL, T_GETAL, T_GETAL, T_KLEUR, T_GETAL}},
		{"tekst", 		6,	{T_GETAL, T_KLEUR, T_TEKST, T_FONTNAAM, T_GETAL, T_FONTSTIJL}},
		{"bitmap", 		3,	{T_GETAL, T_GETAL, T_GETAL}},
		{"clearscherm",	1,	{T_KLEUR}},
		//wacht,
		//herhaal,
		//cirkel,
		//figuur,
		//toren,
		{"END_OF_LIST\0",	0}
};

typedef struct Colours
{
	char name[15];
	int32_t hexdef;
}Colour_t;

//according to: https://flaviocopes.com/rgb-color-codes/
const Colour_t colour_lists[19] = {
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
		{"END_OF_LIST\0", 0x000000}
};



#endif /* INC_FL_API_FUNCTION_NAMES_H_ */
