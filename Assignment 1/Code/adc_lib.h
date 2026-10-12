/*
 * adc_lib.h
 *
 *  Created on: 1 Oct 2026
 *      Author: DAVIDROBERTOTAPIACAI
 */

#ifndef ADC_LIB_H_
#define ADC_LIB_H_

int conversion(int channel_selected);
int air_duct_actuator();
void init_LCD();
void send_Command_LCD(char letter);
void send_Data_LCD(char letter);
void send_LCD_char(char letter, int is_text);
#endif /* ADC_LIB_H_ */
