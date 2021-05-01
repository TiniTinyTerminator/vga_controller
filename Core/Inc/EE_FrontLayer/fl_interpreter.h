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

#define SCRIPT_MAX_ARG 10
#define SCRIPT_MAX_ARG_LEN 25	//max ascii length of single paramater
#define SEPERATOR ','

#define CMD_BUF_LEN 255

uint8_t cmd_in_buf = 0;			//total of script commando's in buffer
uint8_t last_cmd_in_buf = 0;	//Place of last script commando in buffer

/**
* @NOTE waarom een short?
* zorg er trouwens voor dat variabelen zon min mogelijk globaal geplaatst worden
* zet ze zo nodig locaal in een .c bestand en gebruik dan extern om er vanaf een ander .c bestand bij te komen.
* zo hou je de variabelen prive zodra je ze compileert
*/

//storage for scriptline seperated in function and its arguments
short cmd_buf [CMD_BUF_LEN][SCRIPT_MAX_ARG];





//int8_t fl_parser(char* scriptline, uint32_t size, char sep_scriptline);

