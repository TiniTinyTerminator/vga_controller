/****************************************************************************************************/
//file:     fl_interpreter.h
//
//Author:   Daniel Mul
//Date:     16 april 2021
//brief:    Front Layer interpreter, these functions will convert the user scripts (ASCII inputs)
//          to usable functions and send them to Logic Layer
/****************************************************************************************************/

#include "stdint.h"

#define SCRIPT_MAX_ARG 10
#define SCRIPT_MAX_ARG_LEN 25	//max ascii length of single paramater
#define SEPERATOR ','

#define CMD_BUF_LEN 255

uint8_t cmd_in_buf = 0;			//total of script commando's in buffer
uint8_t last_cmd_in_buf = 0;	//Place of last script commando in buffer

//storage for scriptline seperated in function and its arguments
short cmd_buf [CMD_BUF_LEN][SCRIPT_MAX_ARG];





//int8_t fl_parser(char* scriptline, uint32_t size, char sep_scriptline);

