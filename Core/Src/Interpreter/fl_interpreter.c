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

//globals for managing the queue
Qentry cmd_queue[QUEUE_LEN];
uint8_t last_inQ = 0;

//TODO ADD check if Q_entry is currently not in use
//creates an entry in the queue at the oldest position
//also allocates memory according to function argument count
uint8_t createQ_entry(uint8_t fnc_nr)
{
	if (last_inQ++ == QUEUE_LEN)
		{
			last_inQ = 0;
		}
	cmd_queue[last_inQ].entry_nr = 0;
	cmd_queue[last_inQ].argp = malloc((function_list[fnc_nr].argc *4));
	cmd_queue[last_inQ].fnc_nr = fnc_nr;

	return last_inQ;
}

//creates an entry in the queue at the <VARIABLE INT> position
//also deallocates memory that was in use
void deleteQ_entry(uint8_t entry_nr)
{
	cmd_queue[entry_nr].entry_nr =0;
	free (cmd_queue[entry_nr].argp);
	cmd_queue[entry_nr].argp = 0;
	cmd_queue[entry_nr].fnc_nr = 0;
}

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

//TODO add errorcode
uint8_t check_function(char* string, uint8_t str_len)
{
	int i = 0;
	while (strncmp(string, function_list[i].name, str_len) != 0)					//check Function_list for colour
	{
		if (strcmp("END_OF_LIST\0", colour_list[i].name) == 0)
			{
				return 0xff;											//error unknown function
			}
		i++;
	}

	return i; 		//position of function in functionlist
}

//TODO add error code
uint8_t check_number(char* string, uint8_t str_len)
{
	int number;

	if (str_len == 1)
	{
		number = string[0] - 48;
		if ((number < 0) || (number > 9))	return -1;	//error invalid number
	}
	else
	{
		number = atoi(string);
		if (number == 0)	return -1;		//error invalid number
	}

	return number;
}

//TODO add errorcode
uint32_t check_colour(char* string, uint8_t str_len)
{
	int i = 0;
	while (strncmp(string, colour_list[i].name, str_len) != 0)					//check Colour_list for colour
	{
		if (strcmp("END_OF_LIST\0", colour_list[i].name) == 0)
			{
				return 0x1000000;											//error unknown colour
			}
		i++;
	}

	return colour_list[i].hexdef;
}

//TODO add functionality
uint8_t check_text(char* string, uint8_t str_len)
{


	return 0;
}

//TODO add errorcode
uint8_t check_fontstyle(char* string, uint8_t str_len)
{
	int i = 0;
	while (strncmp(string, fontstyle_list[i].name, str_len) != 0)					//check Colour_list for colour
	{
		if (strcmp("END_OF_LIST\0", fontstyle_list[i].name) == 0)
			{
				return 100;											//error unknown colour
			}
		i++;
	}

	return fontstyle_list[i].id;
}

//TODO add errorcode
uint8_t check_fontname(char* string, uint8_t str_len)
{
	int i = 0;
	while (strncmp(string, fontname_list[i].name, str_len) != 0)					//check Colour_list for colour
	{
		if (strcmp("END_OF_LIST\0", fontname_list[i].name) == 0)
			{
				return 100;											//error unknown colour
			}
		i++;
	}

	return fontname_list[i].id;
}

/****************************************************************************************************/
//function:     fl_interpreter
//arguments:    scriptline
//
//
//
/****************************************************************************************************/
int8_t fl_parser(char* scriptline, uint32_t len)
{
    int i = 0;		//position counter
    int j = 0;		//argument counter

    int arg_len = 0;	//length of current argument
    int fnc_nr = 0;

    int* pdata;
    uint8_t q_pos;

    arg_len = atillsep(scriptline, len, SEPERATOR);
    fnc_nr = check_function(&scriptline[0], arg_len);
    i += arg_len + 1;										//go to start of first argument
    if (fnc_nr == 0xff) return -1;							//ERROR no valid function

    q_pos = createQ_entry(fnc_nr);
    pdata = (int*) cmd_queue[q_pos].argp;

    while (i < len)                  //as long as the end of scriptline is not reached, continue
    {
    		if (j == (function_list[fnc_nr].argc)) return -2;		//ERROR to many arguments for function

			arg_len = atillsep(&scriptline[i], (len - i), SEPERATOR);

			if (arg_len == 0) return -3;					//ERROR empty argument

			switch (function_list[fnc_nr].argt[j])
			{
			case T_GETAL:
				pdata[j] = check_number(&scriptline[i], arg_len);
				break;
			case T_TEKST:
				break;
			case T_KLEUR:
				pdata[j] = check_colour(&scriptline[i], arg_len);
				break;
			case T_FONTNAAM:
				pdata[j] = check_fontname(&scriptline[i], arg_len);
				break;
			case T_FONTSTIJL:
				pdata[j] = check_fontstyle(&scriptline[i], arg_len);
				break;
			case T_COORDINAAT:
				break;

			}
			j++;
			i += arg_len + 1;		//go to start of next argument
    	}

    return 0;
}

void test_func(void)
{
	char testline[] = "cirkel, is dit,500,mogelijk ,500";
	fl_parser(testline, sizeof(testline));
}
