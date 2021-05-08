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
#define MAX_Q_ID	4294967295;

typedef void (*Apifuncp)(void* );

/**
 * @brief 
 * 
 */
typedef struct Queue_entry
{
	Apifuncp funcp;					//pointer to function
	void* argp;						//pointer to first argument
	int fnc_nr;						//function number
}Qentry;

/**
 * @brief 
 * 
 */
typedef enum FL_error
{
	///@brief brief description
	E_NO_ERROR,
	///@brief brief description
	E_CHK_FUNC_UNKNOWN,
	///@brief brief description
	E_CHK_INVALID_NUM,
	///@brief brief description
	E_CHK_COLOR_UNKOWN,
	///@brief brief description
	E_TEKST_NO_MEM,
	///@brief brief description
	E_CHK_FONTSTYLE_UNKOWN,
	///@brief brief description
	E_CHK_FONTNAME_UNKOWN,
	///@brief brief description
	E_TO_MANY_ARGUMENTS,
	///@brief brief description
	E_EMPTY_ARGUMENT
}FL_error_t;

/**
 * @brief storage for scriptline seperated in function and its arguments
 * 
 * @return uint8_t 
 */
uint8_t test_func(void);

/**
 * @brief interpret the variables given from the input
 * 
 * @param scriptline 
 * @param len 
 * @return FL_error_t 
 */
FL_error_t fl_parser(char* scriptline, uint32_t len);

/**
 * @brief delete an entry
 * 
 * @param entry_nr the position of the entry
 */
void deleteQ_entry(uint8_t entry_nr);

#endif	// INC_FL_INTERPRETER_H_
