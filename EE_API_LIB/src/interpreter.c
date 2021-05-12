/**
 * @file interpreter.c
 * @author Daniel Mul (you@domain.com)
 * @brief Front Layer interpreter, these functions will convert the user scripts (ASCII inputs) to usable functions and send them to Logic Layer
 * @date 16 april 2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <interpreter.h>
#include <api_function_names.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

//globals for managing the queue
Qentry cmd_queue[QUEUE_LEN];

uint8_t last_inQ 	= 0;

extern Command_t function_list[];

//creates an entry in the queue at the oldest position
//also allocates memory according to function argument count
uint8_t createQ_entry(uint8_t fnc_nr)
{
	if (last_inQ++ == QUEUE_LEN)
	{
		last_inQ = 0;
	}

	deleteQ_entry(last_inQ);

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
		if (p != 0)
		{
			free((uint32_t *)p[3]);
		}
	}
	cmd_queue[entry_nr].funcp = NULL;
	if (cmd_queue[entry_nr].argp != NULL)
	{
		free(cmd_queue[entry_nr].argp);
		cmd_queue[entry_nr].argp = NULL;
	}

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

int16_t cnttillsep(char* script, uint32_t len, char seperator)
{
	uint8_t i = 0;
	uint8_t j = 0;

	while (i < len)
	{
		if(script[i] == seperator) j++;
		i++;
	}
	return j;
}


Parser_err_t check_function(char* string, uint8_t str_len, int* retv)
{
	int i = 0;
	while (strncmp(string, function_list[i].name, str_len) != 0)					//check Function_list for colour
	{
		if (strcmp(END_OF_LIST, function_list[i].name) == 0)
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
		number = string[0] - '0';
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

Parser_err_t check_float(char* string, uint8_t str_len, int* retv)
{
	float number = 0;

	if (str_len < 3)
	{
		int whole = string[0] - '0';
		int komma = string[1] - '.';
		int decimal = string[2] -'0';
		int x = whole + komma + decimal;
		if (x != 0)	return E_CHK_INVALID_FLOAT;		//error invalid number
	}
	else
	{
		number = (float)atof(string);
		if (number == 0)	return E_CHK_INVALID_FLOAT;		//error invalid number
	}

	retv[0] = (float)number;
	return E_NO_ERROR;
}
Parser_err_t check_colour(char* string, uint8_t str_len, int* retv)
{
	int i = 0;
	while (strncmp(string, colour_list[i].name, str_len) != 0)					//check Colour_list for colour
	{
		if (strcmp(END_OF_LIST, colour_list[i].name) == 0)
			{
				return E_CHK_COLOR_UNKOWN;											//error unknown colour
			}
		i++;
	}

	retv[0] = (uint8_t) colour_list[i].hexdef;
	return E_NO_ERROR;
}

Parser_err_t check_text(char* string, uint8_t str_len, int* retv)
{
	char* p;
	p = calloc((str_len + 1), sizeof(char));
	if (p == NULL)
	{
		return E_TEKST_NO_MEM;
	}
	memcpy(p, string, str_len);
	p[str_len + 1] = '\0';

	retv[0] = (int)p;
	return E_NO_ERROR;
}

Parser_err_t check_fontstyle(char* string, uint8_t str_len, int* retv)
{
	int i = 0;
	while (strncmp(string, fontstyle_list[i].name, str_len) != 0)					//check Colour_list for colour
	{
		if (strcmp(END_OF_LIST, fontstyle_list[i].name) == 0)
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
		if (strcmp(END_OF_LIST, fontname_list[i].name) == 0)
			{
				return E_CHK_FONTNAME_UNKOWN;											//error unknown colour
			}
		i++;
	}

	*retv = fontname_list[i].id;
	return E_NO_ERROR;
}

void Parser_err_handler(Parser_err_t error, int arg_cnt, char* arg_string, int arg_len, char* string, int str_len, uint8_t first_error)
{
	if ( first_error == 1)
	{
		printf("Error detected in input:\r\n");
		printf("In scriptline: \"%.*s\"\r\n", str_len, string);
	}

	switch (error)
	{
	case E_NO_ERROR:
		printf("this should not happen, consult Daniël\r\n");
		break;
	case E_CHK_FUNC_UNKNOWN:
		printf("In argument %i--> Function unknown: \"%.*s\"\r\n", arg_cnt, arg_len, arg_string);
		break;
	case E_CHK_INVALID_NUM:
		printf("In argument %i--> Invalid number: \"%.*s\"\r\n",arg_cnt+1, arg_len, arg_string);
		break;
	case E_CHK_INVALID_FLOAT:
		printf("In argument %i--> Invalid float: \"%.*s\"\r\n",arg_cnt+1, arg_len, arg_string);
		break;
	case E_CHK_COLOR_UNKOWN:
		printf("In argument %i--> Colour unknown: \"%.*s\"\r\n",arg_cnt+1, arg_len, arg_string);
		break;
	case E_TEKST_NO_MEM:
		printf("In argument %i--> No memory available for string: \"%.*s\"\r\n",arg_cnt+1, arg_len, arg_string);
		break;
	case E_CHK_FONTSTYLE_UNKOWN:
		printf("In argument %i --> Fontstyle unknown: \"%.*s\"\r\n",arg_cnt+1, arg_len, arg_string);
		break;
	case E_CHK_FONTNAME_UNKOWN:
		printf("In argument %i --> Fontname unknown: \"%.*s\"\r\n",arg_cnt+1, arg_len, arg_string);
		break;
	case E_TO_MANY_ARGUMENTS:
		printf("Too many arguments for this function\r\n");
		break;
	case E_TO_FEW_ARGUMENTS:
		printf("Too few arguments for this function\r\n");
		break;
	case E_EMPTY_ARGUMENT:
		printf("Argument % is empty\r\n", arg_cnt+1);
		break;
	}
}

Parser_err_t API_Parser(char* scriptline, uint32_t len)
{
	if (len == 0) return E_NO_ERROR;
    int i = 0;		//position counter
    int j = 0;		//argument counter

    int arg_len = 0;	//length of current argument
    int arg_cnt = 0;	//count of entered arguments
    int fnc_nr = 0;

    int* pdata;
    uint8_t q_pos;
    Parser_err_t error = E_NO_ERROR;
    uint8_t first_arg_error = 1;		//First error or not

    arg_len = atillsep(scriptline, len, SEPERATOR);
	error = check_function(&scriptline[0], arg_len, &fnc_nr);

    arg_cnt = cnttillsep(scriptline, len, SEPERATOR);
    if (error == E_NO_ERROR)							//if function is ok check for argument count
    {
        if (arg_cnt < function_list[fnc_nr].argc)
        {
        	error = E_TO_FEW_ARGUMENTS;
        }
        else if (arg_cnt > function_list[fnc_nr].argc)
        {
        	error = E_TO_MANY_ARGUMENTS;
        }
    }

    if (error != E_NO_ERROR)
    {
		Parser_err_handler(error, j, &scriptline[i], arg_len, scriptline, len, first_arg_error);
		return error;
    }

    q_pos = createQ_entry(fnc_nr);
    pdata = (int*) cmd_queue[q_pos].argp;
    i += arg_len + 1;						//go to start of first argument

    while (i <= len)                  //as long as the end of scriptline is not reached, continue
    {
		arg_len = atillsep(&scriptline[i], (len - i), SEPERATOR);
		while( isspace((unsigned char)scriptline[i]) )					//removes whitespaces
		{
			i++;
			arg_len--;
		}
		if (arg_len == 0)
		{
			error = E_EMPTY_ARGUMENT;					//ERROR to many arguments for function
		}
		else
		{
			switch (function_list[fnc_nr].argt[j])
			{
			case T_GETAL:
				error = check_number(&scriptline[i], arg_len, &pdata[j] );
				break;
			case T_KOMMA:
				error = check_float(&scriptline[i], arg_len, &pdata[j] );
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
			}
		}
	if(error != E_NO_ERROR)
	{
		deleteQ_entry(last_inQ);
		if (last_inQ-- == 0)
		{
			last_inQ = QUEUE_LEN;
		}
	Parser_err_handler(error, j, &scriptline[i], arg_len, scriptline, len, first_arg_error);
	}

		j++;
		i += arg_len + 1;		//go to start of next argument
    }

    return error;
}



