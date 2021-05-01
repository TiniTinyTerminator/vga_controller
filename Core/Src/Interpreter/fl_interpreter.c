/****************************************************************************************************/
//file:     fl_interpreter.c
//
//Author:   Daniel Mul
//Date:     16 april 2021
//brief:    Front Layer interpreter, these functions will convert the user scripts (ASCII inputs)
//          to usable functions and send them to Logic Layer
/****************************************************************************************************/

#include <fl_interpreter.h>
#include <fl_api_function_names.h>
#include <string.h>
#include <stdlib.h>

//counts characters in string till separator
int16_t atillsep(char* script, uint32_t len, char seperator)
{
	uint8_t i = 0;
	while (i < len)
	{
		if(script[i] == seperator) break;
		i++;
	}
	return i;
}

uint8_t check_function(char* string, uint8_t str_len)
{
	int i = 0;
	while (strncmp(string, function_lists[i].name, str_len) != 0)					//check Function_list for colour
	{
		if (strcmp("END_OF_LIST\0", colour_lists[i].name) == 0)
			{
				return 0xff;											//error unknown function
			}
		i++;
	}

	return i; 		//position of function in functionlist
}
//TO DO add error when string is no number, empty
uint8_t check_number(char* string, uint8_t str_len)
{
	uint8_t number = 0;

	number = atoi(string);

	return number;
}

uint32_t check_colour(char* string, uint8_t str_len)
{
	int i = 0;
	while (strcmp(string, colour_lists[i].name))					//check Colour_list for colour
	{
		if (strcmp("END_OF_LIST\0", colour_lists[i].name))
			{
				return 0x1000000;											//error unknown colour
			}
		i++;
	}

	return colour_lists[i].hexdef;
}

//TO DO add functionality
uint8_t check_text(char* string, uint8_t str_len)
{


	return 0;
}

//TO DO add functionality
uint8_t check_fontstyle(char* string, uint8_t str_len)
{
	return 0;
}

//TO DO add functionality
uint8_t check_fontname(char* string, uint8_t str_len)
{
	return 0;
}

//@NOTE voor het commentaar is het misschien handig om naar deze uitleg te kijken: https://www.doxygen.nl/manual/docblocks.html.
// hier kan je zien hoe je de arguementen enzo kan opzetten voor doxygen

/****************************************************************************************************/
//function:     fl_interpreter
//arguments:    scriptline
//
//
//
/****************************************************************************************************/
int8_t fl_parser(char* scriptline, uint32_t len, char sep_scriptline[][SCRIPT_MAX_ARG_LEN])
{
    int i = 0;		//position counter
    int j = 0;		//argument counter

    int arg_len = 0;	//length of current argument
    int fnc_nr = 0;

    arg_len = atillsep(scriptline, len, SEPERATOR);
    fnc_nr = check_function(&scriptline[0], arg_len);
    if (fnc_nr == 0xff) return -1;							//ERROR no valid function


    while (i < len)                  //as long as the end of scriptline is not reached, continue
    {
    		if (j == (function_lists[fnc_nr].argc - 1)) return -2;		//ERROR to many arguments for function

			i += arg_len + 1;		//go to start of next argument
			arg_len = atillsep(&scriptline[i], (len - i), SEPERATOR);

			if (arg_len == 0) return -3;					//ERROR empty argument

			switch (function_lists[fnc_nr].argt[j])
			{
			case T_GETAL:
				break;
			case T_TEKST:
				break;
			case T_KLEUR:
				break;
			case T_FONTNAAM:
				break;
			case T_FONTSTIJL:
				break;
			case T_COORDINAAT:
				break;
			}
    	}

    return 0;
}


void test_func(void)
{
	char tmp_ascii_cmd[SCRIPT_MAX_ARG][SCRIPT_MAX_ARG_LEN];
	char testline[] = "cirkel, is dit,500,mogelijk ,500";
	fl_parser(testline, sizeof(testline), tmp_ascii_cmd);
	separgtofunc(tmp_ascii_cmd);
}
