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


const char NAMES_FUNCTION[][15] =
{
	"lijn",
	"rechthoek",
	"tekst",
	"bitmap",
	"clearscherm",

	"wacht",			//Bonus
	"herhaal",			//Bonus
	"cirkel",			//Bonus
	"figuur",			//Bonus
	"toren"
};			//Bonus

//@NOTE enumerations moeten vgm met hoofletters zijn

enum ID_FUNCTION
{
	lijn,
	rechthoek,
	tekst,
	bitmap,
	clearscherm,
	wacht,
	herhaal,
	cirkel,
	figuur,
	toren,
	ID_FUNCTION_MAX
};

enum ID_ARGUMENT_TYPE
{
	t_getal,
	t_tekst,
	t_kleur,
	t_fontnaam,		//nog niet aangemaakt
	t_fontstijl,	//nog niet aangemaakt
	coordinaat,		//nog niet in gebruik
};

/**
* @NOTE voor overzicht en gemak van gebruik is het handig om een typedef te gebruiken en daar weer van een array te maken
* Hierdoor kan ik en anderen beter zien wat je probeert te bereiken met deze array
**/

const uint8_t FUNCTION_ARG_TYPE[][10]=
{
		{lijn, 			6 ,t_getal, t_getal, t_getal, t_getal, t_kleur, t_getal},
		{rechthoek, 	6, t_getal, t_getal, t_getal, t_getal, t_kleur, t_getal},
		{tekst, 		6, t_getal, t_kleur, t_tekst, t_fontnaam, t_getal, t_fontstijl},
		{bitmap, 		3, t_getal, t_getal, t_getal},
		{clearscherm,	1, t_kleur}
};

const char NAMES_COLOUR[][20] =
{
	"zwart"			,
	"blauw"			,
	"lichtblauw"	,
	"groen"			,
	"lichtgroen"	,
	"cyaan"			,
	"lichtcyaan"	,
	"rood"			,
	"lichtrood"		,
	"magenta"		,
	"lichtmagenta"	,
	"bruin"			,
	"geel"			,
	"grijs"			,
	"wit"			,
	"rose"			,			//Bonus
	"paars"			};			//Bonus

// @NOTE als het kan is het mischien handig om hier alvast de kleurcodes te koppelen aan de enum
enum ID_COLOUR
{
	zwart,
	blauw,
	lichtblauw,
	groen,
	lichtgroen,
	cyaan,
	lichtcyaan,
	rood,
	lichtrood,
	magenta,
	lichtmagenta,
	bruin,
	geel,
	grijs,
	wit,
	rose,			//Bonus
	paars,			//Bonus
	ID_COLOUR_MAX
};


//@NOTE comment aangeven voor waarvoor de endif is doe je goed
#endif /* INC_FL_API_FUNCTION_NAMES_H_ */
