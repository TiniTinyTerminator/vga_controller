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

#include "stdint.h"

#define SEPERATOR ','

#define QUEUE_LEN 255		//MAX uint8_t

typedef struct Queue_entry
{
	int entry_nr;			//position in queue
	void* argp;				//pointer to first argument
	int fnc_nr;				//function number				--> could also be pointer to the function
}Qentry;






//int8_t fl_parser(char* scriptline, uint32_t size, char sep_scriptline);

