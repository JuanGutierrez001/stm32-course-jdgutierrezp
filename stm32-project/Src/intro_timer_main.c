/*
 * intro_timer_main.c
 *
 *  Created on: May 29, 2026
 *      Author: juand
 */
#include <stdint.h>
#include <stm32f4xx.h>

int main (void){


	/* activacion d ela señal de reloj
	 *
	 */
	RCC->AHB1ENR |=RCC_AHB1ENR_GPIOAEN;

	/* configurando el pin A5 como salida*/

	GPIOA->MODER |= (0b01 << GPIO_MODER_MODE5_Pos);

	/*cpnfigurando el pin A5 como salida pull-push*/

	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT5);
	/*Configuracion de velocidad como fast*/

	GPIOA->OSPEEDR |= (0b10 << GPIO_OSPEEDR_OSPEED5_Pos);

	GPIOA->ODR &= -(1<<5);



	RCC->APB1ENR &= ~(RCC_APB1ENR_TIM3EN);	/*limpiamos posicion TIM3EN*/
	RCC->APB1ENR |=RCC_APB1ENR_TIM3EN;	/*activamos la señal de reloj*/
	/*configuramos prescaler para que el CNT se incremente cada 0.1ms*/
	TIM3->PSC = (1600 -1);
	/* cargamos le valor en el ARR pra que  se generen interrupciones casa 325ms*/
	TIM3->ARR = (3250 -1);
	/* Reiniciamos el contado*/
	TIM3->CNT = 0;
	/* limpiamos la bandera de la interruppcion debida a una actualizacion*/
	TIM3->SR &= ~(TIM_SR_UIF);
	/*Activamos la interrupcion tipo update-event */
	/*limpiamos la posici*/
	TIM3->DIER &= ~(TIM_DIER_UIE);
	/* Activamos el interrupto*/
	TIM3->DIER |= TIM_DIER_UIE;

	/*Matriculando la interrupcio TIM3 en el NVIC,para */

	__NVIC_EnableIRQ (TIM3_IRQn);
	 /*configuramos la direccion en la que el contador cuenta*/
	/*limpiamos la posicion - cuenta de forma ascendente*/

	TIM3->CR1 &= ~(TIM_CR1_DIR);

	/*activamos la precarga del ARR*/
	/*Limpiamos la posicion ARPE*/
	TIM3->CR1 &= ~(TIM_CR1_ARPE);
	/*Activamos la precarga*/
	TIM3->CR1 |= (TIM_CR1_ARPE);

	/*Activamos el contador, para que la señal de reloj se comienza a propagar*/
	TIM3->CR1 |= TIM_CR1_CEN;




	while(1){

	}

}
/* funcion ISR par ael TIM3
 * en general toda funcion ISR no retorna para nada (void) y no recibe parametros*/
void TIM3_IRQHandler (void){
	/* verificar que generó la interrupción*/
	if(TIM3->SR && TIM_SR_UIF){
		/* Realizamos una accion en respuesta
		 * en este caso un toogle
		 */

		GPIOA->ODR ^= GPIO_ODR_OD5; // =//

		/*bajamos la bander adel inyerruptor
		 * */
		TIM3->SR &= ~(TIM_SR_UIF);


	}

}











