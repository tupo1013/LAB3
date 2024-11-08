/*
 * fsm_auto.c
 *
 *  Created on: Oct 24, 2024
 *      Author: Tupo_1310
 */

#include "fsm_auto.h"

int red_main, red_cross=0;
int yellow_main, yellow_cross=0;
int green_main, green_cross=0;
int ind=0;
int num_buf=0;

void fsm_auto_mode1_run(){
	switch(status){
	case INIT:
		HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(YEL1_GPIO_Port, YEL1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GRE1_GPIO_Port, GRE1_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(YEL2_GPIO_Port, YEL2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GRE2_GPIO_Port, GRE2_Pin, GPIO_PIN_SET);

		red_main = red_dur/100;
		red_cross = red_dur/100;
		yellow_main = yellow_dur/100;
		yellow_cross = yellow_dur/100;
		green_main = green_dur/100;
		green_cross = green_dur/100;

		status = RED_GREEN;
		ind=0;
		setTimer1(green_dur);
		setTimer3(25);
		setTimer4(100);

		break;

	case RED_GREEN:
		HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(YEL1_GPIO_Port, YEL1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GRE1_GPIO_Port, GRE1_Pin, GPIO_PIN_RESET);

		HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(YEL2_GPIO_Port, YEL2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GRE2_GPIO_Port, GRE2_Pin, GPIO_PIN_SET);

		if(timer1_flag ==1){
			status = RED_YELLOW;
			setTimer1(yellow_dur);
			/*setTimer3(25);
			setTimer4(100);*/
			ind = 0;
		}
		if(timer3_flag==1){
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin,  SET);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin,  SET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin,  SET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin,  SET);

			switch(ind){
			case 0:
				num_buf = red_main/10;
				displayDigit(num_buf);
				HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin,  RESET);
				break;
			case 1:
				num_buf = red_main%10;
				displayDigit(num_buf);
				HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin,  RESET);
				break;
			case 2:
				num_buf = green_cross/10;
				displayDigit(num_buf);
				HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin,  RESET);
				break;
			case 3:
				num_buf = green_cross%10;
				displayDigit(num_buf);
				HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin,  RESET);
				break;
			}
			ind = (ind + 1) % 4;
			setTimer3(25);
		}
		if(timer4_flag==1){
			red_main--;
			green_cross--;
			setTimer4(100);
		}
		if(isButton1Press() == 1) status = MODE2_BUFF;
		break;
	case RED_YELLOW:
		HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(YEL1_GPIO_Port, YEL1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GRE1_GPIO_Port, GRE1_Pin, GPIO_PIN_RESET);

		HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(YEL2_GPIO_Port, YEL2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GRE2_GPIO_Port, GRE2_Pin, GPIO_PIN_RESET);

		if(timer1_flag ==1){
			status = GREEN_RED;
			ind = 0;
			setTimer1(green_dur);
			/*setTimer3(25);
			setTimer4(100);*/
		}
		if(timer3_flag==1){
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin,  SET);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin,  SET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin,  SET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin,  SET);

			switch(ind){
			case 0:
				num_buf = red_main/10;
				displayDigit(num_buf);
				HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin,  RESET);
				break;
			case 1:
				num_buf = red_main%10;
				displayDigit(num_buf);
				HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin,  RESET);
				break;
			case 2:
				num_buf = yellow_cross/10;
				displayDigit(num_buf);
				HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin,  RESET);
				break;
			case 3:
				num_buf = yellow_cross%10;
				displayDigit(num_buf);
				HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin,  RESET);
				break;
			}
			ind = (ind + 1) % 4;
			setTimer3(25);
		}
		if(timer4_flag==1){
			red_main--;
			yellow_cross--;
			setTimer4(100);
		}
		if(isButton1Press() == 1) status = MODE2_BUFF;
		break;

	case GREEN_RED:
		HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(YEL1_GPIO_Port, YEL1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GRE1_GPIO_Port, GRE1_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(YEL2_GPIO_Port, YEL2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GRE2_GPIO_Port, GRE2_Pin, GPIO_PIN_RESET);

		if(timer1_flag ==1){
			status = YELLOW_RED;
			ind = 0;
			setTimer1(yellow_dur);
			/*setTimer3(25);
			setTimer4(100);*/
		}
		if(timer3_flag==1){
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin,  SET);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin,  SET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin,  SET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin,  SET);

			switch(ind){
			case 0:
				num_buf = green_main/10;
				displayDigit(num_buf);
				HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin,  RESET);
				break;
			case 1:
				num_buf = green_main%10;
				displayDigit(num_buf);
				HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin,  RESET);
				break;
			case 2:
				num_buf = red_cross/10;
				displayDigit(num_buf);
				HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin,  RESET);
				break;
			case 3:
				num_buf = red_cross%10;
				displayDigit(num_buf);
				HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin,  RESET);
				break;
			}
			ind = (ind + 1) % 4;
			setTimer3(25);
		}
		if(timer4_flag==1){
			green_main--;
			red_cross--;
			setTimer4(100);
		}
		if(isButton1Press() == 1) status = MODE2_BUFF;
		break;
	case YELLOW_RED:
		HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(YEL1_GPIO_Port, YEL1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GRE1_GPIO_Port, GRE1_Pin, GPIO_PIN_RESET);

		HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(YEL2_GPIO_Port, YEL2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GRE2_GPIO_Port, GRE2_Pin, GPIO_PIN_RESET);

		if(timer1_flag ==1){
			status = RED_GREEN;
			red_main = red_dur/100;
			red_cross = red_dur/100 +1;
			yellow_main = yellow_dur/100 +1;
			yellow_cross = yellow_dur/100;
			green_main = green_dur/100;
			green_cross = green_dur/100;
			setTimer1(green_dur);
			ind = 0;
		}
		if(timer3_flag==1){
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin,  SET);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin,  SET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin,  SET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin,  SET);

			switch(ind){
			case 0:
				num_buf = yellow_main/10;
				displayDigit(num_buf);
				HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin,  RESET);
				break;
			case 1:
				num_buf = yellow_main%10;
				displayDigit(num_buf);
				HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin,  RESET);
				break;
			case 2:
				num_buf = red_cross/10;
				displayDigit(num_buf);
				HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin,  RESET);
				break;
			case 3:
				num_buf = red_cross%10;
				displayDigit(num_buf);
				HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin,  RESET);
				break;
			}
			ind = (ind + 1) % 4;
			setTimer3(25);
		}
		if(timer4_flag==1){
			yellow_main--;
			red_cross--;
			setTimer4(100);
		}
		if(isButton1Press() == 1) status = MODE2_BUFF;
	default:
		break;
	}
}
