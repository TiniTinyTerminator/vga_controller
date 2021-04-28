/*
 * fl_api_function_names.h
 *
 *  Created on: Apr 28, 2021
 *      Author: Daniel
 */

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



#endif /* INC_FL_API_FUNCTION_NAMES_H_ */
