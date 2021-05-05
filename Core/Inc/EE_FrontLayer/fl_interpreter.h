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



//storage for scriptline seperated in function and its arguments
uint8_t test_func(void);





//int8_t fl_parser(char* scriptline, uint32_t size, char sep_scriptline);

#endif	// INC_FL_INTERPRETER_H_
