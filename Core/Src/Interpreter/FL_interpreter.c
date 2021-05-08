/****************************************************************************************************/
//file:     fl_interpreter.c
//
//Author:   Daniel Mul
//Date:     16 april 2021
//brief:    Front Layer interpreter, these functions will convert the user scripts (ASCII inputs)
//          to usable functions and send them to Logic Layer
/****************************************************************************************************/

#include <FL_interpreter.h>
#include <FL_api_function_names.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//globals for managing the queue
Qentry cmd_queue[QUEUE_LEN];
//TODO move functionlist
Command_t function_list[15]=
{
		{"lijn", 		6,	{T_GETAL, T_GETAL, T_GETAL, T_GETAL, T_KLEUR, T_GETAL}},
		{"rechthoek", 	6,	{T_GETAL, T_GETAL, T_GETAL, T_GETAL, T_KLEUR, T_GETAL}},
		{"tekst", 		7,	{T_GETAL, T_GETAL, T_KLEUR, T_TEKST, T_FONTNAAM, T_GETAL, T_FONTSTIJL}},
		{"bitmap", 		3,	{T_GETAL, T_GETAL, T_GETAL}},
		{"clearscherm",	1,	{T_KLEUR}},
		// wacht,
		//herhaal,
		//cirkel,
		//figuur,
		//toren,
		{"END_OF_LIST"}
};

uint8_t last_inQ 	= 0;

//TODO ADD check if Q_entry is currently not in use
//creates an entry in the queue at the oldest position
//also allocates memory according to function argument count
uint8_t createQ_entry(uint8_t fnc_nr)
{
	if (last_inQ++ == QUEUE_LEN)
	{
		last_inQ = 0;
	}

	cmd_queue[last_inQ].funcp	= function_list[fnc_nr].funcp;
	cmd_queue[last_inQ].argp	= malloc((function_list[fnc_nr].argc *4));
	cmd_queue[last_inQ].fnc_nr	= fnc_nr;

	return last_inQ;
}

//creates an entry in the queue at the <VARIABLE INT> position
//also deallocates memory that was in use
void deleteQ_entry(uint8_t entry_nr)
{
	if (cmd_queue[entry_nr].fnc_nr == 2)
	{
		uint32_t* p = (uint32_t*) cmd_queue[entry_nr].argp;
		free((uint32_t *)p[3]);
	}
	cmd_queue[entry_nr].funcp = NULL;
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

//! is het niet handiger om door de lengte van de array te lopen met een for loop, zo zorg je ervoor dat er nooit verder dan de list gekeken wordt.

Parser_err_t check_function(char* string, uint8_t str_len, int* retv)
{
	int i = 0;
	while (strncmp(string, function_list[i].name, str_len) != 0)					//check Function_list for colour
	{
		if (strcmp("END_OF_LIST", function_list[i].name) == 0)
			{
				return E_CHK_FUNC_UNKNOWN;											//error unknown function
			}
		i++;
	}
	*retv = i;			//position of function in functionlist
	return E_NO_ERROR;
}

Parser_err_t check_number(char* string, uint8_t str_len, int* retv)
{
	int number;

	if (str_len == 1)
	{
		number = string[0] - 48;
		if ((number < 0) || (number > 9))	return E_CHK_INVALID_NUM;	//error invalid number
	}
	else
	{
		number = atoi(string);
		if (number == 0)	return E_CHK_INVALID_NUM;		//error invalid number
	}

	retv[0] = number;
	return E_NO_ERROR;
}

Parser_err_t check_colour(char* string, uint8_t str_len, int* retv)
{
	int i = 0;
	while (strncmp(string, colour_list[i].name, str_len) != 0)					//check Colour_list for colour
	{
		if (strcmp("END_OF_LIST\0", colour_list[i].name) == 0)
			{
				return E_CHK_COLOR_UNKOWN;											//error unknown colour
			}
		i++;
	}

	retv[0] = (uint8_t) colour_list[i].hexdef;
	return E_NO_ERROR;

}

//TODO add mem free
Parser_err_t check_text(char* string, uint8_t str_len, int* retv)
{
	char* p;
	p = calloc(str_len, sizeof(char));
	if (p == NULL)
	{
		return E_TEKST_NO_MEM;
	}
	memcpy(p, string, str_len);

	retv[0] = (int)p;
	return E_NO_ERROR;
}

Parser_err_t check_fontstyle(char* string, uint8_t str_len, int* retv)
{
	int i = 0;
	while (strncmp(string, fontstyle_list[i].name, str_len) != 0)					//check Colour_list for colour
	{
		if (strcmp("END_OF_LIST\0", fontstyle_list[i].name) == 0)
			{
				return E_CHK_FONTSTYLE_UNKOWN;											//error unknown colour
			}
		i++;
	}

	*retv = fontstyle_list[i].id;
	return E_NO_ERROR;
}

Parser_err_t check_fontname(char* string, uint8_t str_len, int* retv)
{
	int i = 0;
	while (strncmp(string, fontname_list[i].name, str_len) != 0)					//check Colour_list for colour
	{
		if (strcmp("END_OF_LIST\0", fontname_list[i].name) == 0)
			{
				return E_CHK_FONTNAME_UNKOWN;											//error unknown colour
			}
		i++;
	}

	*retv = fontname_list[i].id;
	return E_NO_ERROR;
}

void Parser_err_handler(Parser_err_t error, int arg_cnt, char* arg_string, int arg_len, char* string, int str_len)
{
	printf("Error detected in input:\r\n");
	printf("In scriptline: %.*s\r\n", str_len, string);

	switch (error)
	{

	case E_NO_ERROR:
		printf("this should not happen, consult Daniël\r\n");
		break;
	case E_CHK_FUNC_UNKNOWN:
		printf("In the %i argument--> Function unknown: %.*s\r\n", arg_cnt, arg_len, arg_string);
		break;
	case E_CHK_INVALID_NUM:
		printf("In the %i argument--> Invalid number: %.*s\r\n",arg_cnt+1, arg_len, arg_string);
		break;
	case E_CHK_COLOR_UNKOWN:
		printf("In the %i argument--> Colour unknown: %.*s\r\n",arg_cnt+1, arg_len, arg_string);
		break;
	case E_TEKST_NO_MEM:
		printf("In the %i argument--> No memory available for string: %.*s\r\n",arg_cnt+1, arg_len, arg_string);
		break;
	case E_CHK_FONTSTYLE_UNKOWN:
		printf("In the %i argument--> Fontstyle unknown: %.*s\r\n",arg_cnt+1, arg_len, arg_string);
		break;
	case E_CHK_FONTNAME_UNKOWN:
		printf("In the %i argument--> Fontname unknown: %.*s\r\n",arg_cnt+1, arg_len, arg_string);
		break;
	case E_TO_MANY_ARGUMENTS:
		printf("Too many arguments for this function\r\n");
		break;
	case E_EMPTY_ARGUMENT:
		printf("Too few arguments for this function\r\n");
		break;
	}
}

/****************************************************************************************************/
//function:     fl_interpreter
//arguments:    scriptline
//
//
//
/****************************************************************************************************/
Parser_err_t fl_parser(char* scriptline, uint32_t len)
{
    int i = 0;		//position counter
    int j = 0;		//argument counter

    int arg_len = 0;	//length of current argument
    int fnc_nr = 0;

    int* pdata;
    uint8_t q_pos;
    Parser_err_t error = E_NO_ERROR;

    arg_len = atillsep(scriptline, len, SEPERATOR);
    
	error = check_function(&scriptline[0], arg_len, &fnc_nr);

    if (error != E_NO_ERROR) {
	//TODO errorhandler Wrong function
		Parser_err_handler(error, j, &scriptline[i], arg_len, scriptline, len);

		return error;
	}

    q_pos = createQ_entry(fnc_nr);
    pdata = (int*) cmd_queue[q_pos].argp;
    i += arg_len + 1;						//go to start of first argument

    while (i < len)                  //as long as the end of scriptline is not reached, continue
    {
    		error = E_NO_ERROR;		//reset error
    		if (j == (function_list[fnc_nr].argc))
			{
				error = E_TO_MANY_ARGUMENTS;					//ERROR to many arguments for function
				break;
			}

			arg_len = atillsep(&scriptline[i], (len - i), SEPERATOR);

			switch (function_list[fnc_nr].argt[j])
			{
			case T_GETAL:
				error = check_number(&scriptline[i], arg_len, &pdata[j] );
				break;
			case T_TEKST:
				error = check_text(&scriptline[i], arg_len, &pdata[j] );
				break;
			case T_KLEUR:
				error = check_colour(&scriptline[i], arg_len, &pdata[j] );
				break;
			case T_FONTNAAM:
				error = check_fontname(&scriptline[i], arg_len, &pdata[j] );
				break;
			case T_FONTSTIJL:
				error = check_fontstyle(&scriptline[i], arg_len, &pdata[j] );
				break;
			case T_COORDINAAT:
				break;
			}

			if (error != E_NO_ERROR)
			{
				Parser_err_handler(error, j, &scriptline[i], arg_len, scriptline, len);
			}

			j++;
			i += arg_len + 1;		//go to start of next argument
    	}

    return error;
}
    // if (error != E_NO_ERROR) {


//TODO remove test_func
//uint8_t test_func(void)
//{
//	API_Init_function_list();
//	char testline[] = "clearscherm,rood";
////	char testline[] = "tekst,50,50,paars,dit is mokermooie tekst,consolas, 1, normaal";
//	int x =fl_parser(testline, sizeof(testline));
//
//	int* point;
//	point = (int*) cmd_queue[1].argp;
//
////	deleteQ_entry(1);
//	int x1 = point[0];
//	int x2 = point[1];
//	int x3 = point[2];
//	API_Next_Q();
//	API_Next_Q();
//	int x4 = point[3];
//	char* x0 = x4;
//	int x5 = point[4];
//	int x6 = point[5];
//	char testline2[] = "rechthoek,90,70,10,20,blauw,5";
//
//	x =fl_parser(testline2, sizeof(testline2));
//
//
//	char testline3[] = "bitmap,9,777,797";
//	x =fl_parser(testline3, sizeof(testline3));
//	return x;
//}
