/**
 * @file helper.h
 * @author Daniel Mul (you@domain.com)
 * @brief prototype for Queue handeling
 * @attention	API_Init_function_list must be called once before API_Next_Q
 * @date 2021-05-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef CORE_INC_EE_FRONTLAYER_FL_HELPER_H_
#define CORE_INC_EE_FRONTLAYER_FL_HELPER_H_


/**
 * @brief checks if there is a new entry in the queue and executes it
 *
 * @arg	none
 */
void API_Next_Q(void);

/**
 * @brief connects the API_Helper_functions with the function_list
 *
 * @arg	none
 */
void API_Init_function_list(void);
#endif /* CORE_INC_EE_FRONTLAYER_FL_HELPER_H_ */
