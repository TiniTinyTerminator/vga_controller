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

/****************************************************************************************************/
//function:     fl_interpreter
//arguments:    scriptline
//
//
//
/****************************************************************************************************/
int8_t fl_parser(char* scriptline, uint32_t size, char sep_scriptline[][SCRIPT_MAX_ARG_LEN])
{
    int i = 0;		//pos_counter
    int j = 0;		//char_counter
    int k = 0;		//arg_counter

    for (i = 0; i < size; i++)                  //as long as the end of scriptline is not reached, continue
    {
    	if (scriptline[i] == SEPERATOR)			//check for seperator
    	{

    		sep_scriptline[k][j] = '\0'; //add terminator at the end
			j = 0;
			k++;
			if (k > SCRIPT_MAX_ARG)	return -1;	//error max argument reached
			continue;
    	}

    	if (k > SCRIPT_MAX_ARG_LEN)	return -2;		//error too long argument;
    	sep_scriptline[k][j] = scriptline[i];
    	char temp = sep_scriptline[k][j];
    	j++;
    }
    return 0;
}

//int8_t separgtofunc(char sep_scriptline[][SCRIPT_MAX_ARG_LEN])
//{
//	uint8_t i = 0;			//function_number
//	uint8_t j = 0;
//	uint8_t temp[10];
//	for(i = 0 ; strcmp(sep_scriptline[0], NAMES_FUNCTION[i]); i++)
//	{
//		if (i == ID_FUNCTION_MAX)	return -1;		//error unknown function
//	}
//	temp[0] = i;
//
//	return 0;
//}

void test_func(void)
{
	char tmp_ascii_cmd[SCRIPT_MAX_ARG][SCRIPT_MAX_ARG_LEN];
	char testline[] = "cirkel, is dit,500,mogelijk ,500";
	fl_parser(testline, sizeof(testline), tmp_ascii_cmd);
	separgtofunc(tmp_ascii_cmd);
}
