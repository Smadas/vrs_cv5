/*
 * vrs_cv5.h
 *
 *  Created on: 18. 10. 2016
 *      Author: Adam
 */

#ifndef VRS_CV5_H_
#define VRS_CV5_H_

extern uint16_t valueADC;
uint16_t pom;
int bufferPripraveny;
char USARTbuffer[100]; //buffer, kde su ulozene znaky na odoslanie
int bufferInkr;

//void ADC1_IRQHandler(void);
void inicializaciaPrerusenieADC(void);
void inicializaciaPrerusenieUSART(void);
void inicializaciaUSART2(void);
void inicializaciaLED(void);
void inicializaciaADCpin(void);
void inicializaciaADC(void);
int blikanieLED(int blikac, int blikacRychlost);
uint16_t citanieHodnotyADC(void);
int rychlostBlikaniaLED(int blikacRychlost,uint16_t value);
void PutcUART2(char *ch);
void USART2_IRQHandler(void);
int vypisDatADC(int i);
int odoslanieRetazca(int tvarVypisu);

#endif /* VRS_CV5_H_ */

