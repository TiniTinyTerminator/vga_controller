/****************************************************************************************************/
//file:     fl_interpreter.h
//
//Author:   Daniel Mul
//Date:     16 april 2021
//brief:    Front Layer interpreter, these functions will convert the user scripts (ASCII inputs)
//          to usable functions and send them to Logic Layer
/****************************************************************************************************/

// @NOTE gebruike een @ voor de parameter om er een doxygen parameter van te maken, wordt dan meegenomen in de documentatie generator.

// @NOTE vergeet je header define niet!!

#ifndef INC_FL_INTERPRETER_H_
#define INC_FL_INTERPRETER_H_

#include "stdint.h"

#define SEPERATOR ','

#define QUEUE_LEN 255		//MAX uint8_t

typedef void (*Apifuncp)(void* );

typedef struct Queue_entry
{
	Apifuncp funcp;					//pointer to function
	void* argp;						//pointer to first argument
	int fnc_nr;						//function number
}Qentry;

typedef enum FL_error
{
	E_NO_ERROR,
	E_CHK_FUNC_UNKNOWN,
	E_CHK_INVALID_NUM,
	E_CHK_COLOR_UNKOWN,
	E_TEKST_NO_MEM,
	E_CHK_FONTSTYLE_UNKOWN,
	E_CHK_FONTNAME_UNKOWN,
	E_TO_MANY_ARGUMENTS,
	E_EMPTY_ARGUMENT
}FL_error_t;



//storage for scriptline seperated in function and its arguments
uint8_t test_func(void);





//int8_t fl_parser(char* scriptline, uint32_t size, char sep_scriptline);

#endif	// INC_FL_INTERPRETER_H_
