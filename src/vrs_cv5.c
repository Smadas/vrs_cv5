/*
 * vrs_cv5.c
 *
 *  Created on: 18. 10. 2016
 *      Author: Adam Ado
 */

#include <stddef.h>
#include "stm32l1xx.h"
#include "vrs_cv5.h"

void PutcUART2(char ch)
{
	USART_SendData(USART2, (uint8_t) ch);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
	USART_ClearFlag(USART2, USART_FLAG_TC);
}


void ADC1_IRQHandler(void)
{
	if (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))//ADC1->SR & ADC_SR_EOC)
	{
		valueADC = ADC_GetConversionValue(ADC1);
	}
	if(ADC_GetFlagStatus(ADC1, ADC_FLAG_OVR))//ADC1->SR & ADC_SR_OVR)
	{
		//pretecenie
	}
}


void inicializaciaPrerusenieADC(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = ADC1_IRQn; //zoznam prerušení nájdete v súbore stm32l1xx.h
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}
void inicializaciaPrerusenieUSART(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; //zoznam prerušení nájdete v súbore stm32l1xx.h
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}
void inicializaciaUSART2(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);


	/* Configure USART Tx and Rx pins */
	GPIO_InitTypeDef GPIO_InitStructure;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	  GPIO_Init(GPIOA, &GPIO_InitStructure);

	  //usart configuration
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	  USART_InitTypeDef USART_InitStructure;
	  USART_InitStructure.USART_BaudRate = 9600;
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;
	  USART_InitStructure.USART_Parity = USART_Parity_No;
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	  USART_Init(USART2, &USART_InitStructure);
	  USART_Cmd(USART2, ENABLE);
	  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);




}
void inicializaciaLED(void)
{
	//vytvorenie struktury GPIO
	GPIO_InitTypeDef gpioInitStruc;
	gpioInitStruc.GPIO_Mode = GPIO_Mode_OUT;
	gpioInitStruc.GPIO_OType = GPIO_OType_PP;
	gpioInitStruc.GPIO_Pin = GPIO_Pin_5;
	gpioInitStruc.GPIO_Speed = GPIO_Speed_400KHz;
	//zapisanie inicializacnej struktury
	GPIO_Init(GPIOA, &gpioInitStruc);
}

void inicializaciaADCpin(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* Configure ADCx Channel 4 as analog input */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void inicializaciaADC(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	/* Enable the HSI oscillator */
	RCC_HSICmd(ENABLE);
	/* Check that HSI oscillator is ready */
	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
	/* Enable ADC clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	/* Initialize ADC structure */
	ADC_StructInit(&ADC_InitStructure);
	/* ADC1 configuration */
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	/* ADCx regular channel8 configuration */
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_384Cycles);
	/* Enable the ADC */
	ADC_Cmd(ADC1, ENABLE);
	/* Wait until the ADC1 is ready */
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET)
	{
	}
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
	ADC_ITConfig(ADC1, ADC_IT_OVR, ENABLE);
	ADC_SoftwareStartConv(ADC1);//spustenie prevodu ADC
}

int blikanieLED(int blikac, int blikacRychlost){
	blikac++;
	if (blikac > blikacRychlost)
	{
	  blikac = 0;
	  GPIO_ToggleBits(GPIOA, GPIO_Pin_5);
	}
	return blikac;
}

uint16_t citanieHodnotyADC(void)
{
	ADC_SoftwareStartConv(ADC1);
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)){}
	return ADC_GetConversionValue(ADC1);
}

int rychlostBlikaniaLED(int blikacRychlost,uint16_t value)
{
	if(value >= 3550 && value <= 3800)
	{
	  return 200000;
	}
	else if(value > 3200 && value < 3550)
	{
	  return 50000;

	}
	else if(value >= 2600 && value <= 3200)
	{
	  return 20000;

	}
	else if(value >= 0 && value < 2600)
	{
	  return 5000;
	}
	else
	{
		return blikacRychlost;
	}
}
