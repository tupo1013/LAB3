/*
 * sevenseg.h
 *
 *  Created on: Oct 26, 2024
 *      Author: Tupo_1310
 */

#ifndef INC_SEVENSEG_H_
#define INC_SEVENSEG_H_

#include "main.h"

void displayDigit(int num);
void updateLed(); // Each 1s will change the data to display
void showDigit(); //Each 0.25s will display a digit
void roundData(); // After finish 1 round, the data will be recover

#endif /* INC_SEVENSEG_H_ */
