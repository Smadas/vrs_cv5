/*
 * vrs_cv5.h
 *
 *  Created on: 18. 10. 2016
 *      Author: Adam
 */

#ifndef VRS_CV5_H_
#define VRS_CV5_H_

extern uint16_t valueADC;

//void ADC1_IRQHandler(void);
void inicializaciaPrerusenieADC(void);
void inicializaciaPrerusenieUSART(void);
void inicializaciaLED(void);
void inicializaciaADCpin(void);
void inicializaciaADC(void);
int blikanieLED(int blikac, int blikacRychlost);
uint16_t citanieHodnotyADC(void);
int rychlostBlikaniaLED(int blikacRychlost,uint16_t value);

#endif /* VRS_CV5_H_ */

