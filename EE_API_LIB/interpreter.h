/**
 * @file	interpreter.h
 * @author	daniel.mul@student.hu.nl
 * @brief	Definities voor de functionaliteit van de interpreter en de vooruitstromende Queue
 * @version 0.3
 * @date 2021-05-11
 *
 * @copyright Copyright (c) 2021
*/

#ifndef _INC_FL_INTERPRETER_H_
#define _INC_FL_INTERPRETER_H_

#include "stdint.h"

#define SEPERATOR ','

#define QUEUE_LEN 255		//MAX uint8_t

#define END_OF_LIST "END_OF_LIST"

typedef void (*Apifuncp)(void* );

/**
 * @brief datatype for the queue,
 * @attention pointer is (void) but data can be anything, good prototyping is required
 * 
 */
typedef struct Queue_entry
{
	Apifuncp funcp;					//pointer to function
	void* argp;						//pointer to first argument
	int fnc_nr;						//function number
}Qentry;

/**
 * @brief enum for errors
 * 
 */
typedef enum Parser_err_t
{
	///@brief Niks aan de hand
	E_NO_ERROR,
	///@brief onbekende functie
	E_CHK_FUNC_UNKNOWN,
	///@brief argument is geen getal
	E_CHK_INVALID_NUM,
	///@brief argument is geen float
	E_CHK_INVALID_FLOAT,
	///@brief onbekende kleur
	E_CHK_COLOR_UNKOWN,
	///@brief Te weinig ruimte voor opslaan van string
	E_TEKST_NO_MEM,
	///@brief onbekende fontstijl
	E_CHK_FONTSTYLE_UNKOWN,
	///@brief onbekende fontname
	E_CHK_FONTNAME_UNKOWN,
	///@brief te veel argumenten (of ',') ingevoerd
	E_TO_MANY_ARGUMENTS,
	///@brief te weinig argumenten ingevoerd
	E_TO_FEW_ARGUMENTS,
	///@brief argument bevat geen inhoud
	E_EMPTY_ARGUMENT
}Parser_err_t;


/**
 * @brief interpret the variables given from the input
 * 
 * @param scriptline 
 * @param len 
 * @return FL_error_t 
 */
Parser_err_t API_Parser(char* scriptline, uint32_t len);

/**
 * @brief delete an entry
 * 
 * @param entry_nr the position of the entry
 */
void deleteQ_entry(uint8_t entry_nr);

#endif	// INC_FL_INTERPRETER_H_