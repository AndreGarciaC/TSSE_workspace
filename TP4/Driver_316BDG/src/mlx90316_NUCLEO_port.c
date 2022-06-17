/**
 * @file mlx90316_NUCLEO_port.c
 * @author Andrea García
 * @brief mlx90316_NUCLEO_port.c file in charge of interacting with the NUCLEO F429ZI board and the MLX90316 driver.
 * @version 0.1
 * @date 2022-04-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "mlx90316_NUCLEO_port.h"

// Punteros a handlers requeridos para la gestión de comunicación SPI y TIMER.
static SPI_HandleTypeDef* hspi1;
static TIM_HandleTypeDef* htim1;

/**
 * @brief Init_Handler: Define los handlers necesarios para trabajar en otras funciones del presente fichero.
 * 
 * @param hspi Puntero al handler de la comunicación SPI.
 * @param htim Puntero al handler del TIMER.
 */
void Init_Handler(SPI_HandleTypeDef * hspi, TIM_HandleTypeDef * htim)
{
	hspi1=hspi;
	htim1=htim;
}

/**
 * @brief Cs_Nucleo: Cambia el nivel del pin GPIO 15 entre alto o bajo.
 * 
 * @param cs_val Estado en el cuál el pin será configurado.
 */
void Cs_Nucleo(cs_t cs_val)
{
	switch(cs_val)
	{

	case CS_RESET:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, cs_val);
		break;
	case CS_SET:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, cs_val);
		break;

	default:
		;
	}
}

/**
 * @brief W_Spi_Nucleo: Envía un byte de datos al sensor.
 * 
 * @param spi_byte byte que contiene la información a enviar al sensor.
 */
void W_Spi_Nucleo(uint8_t *spi_byte)
{
	HAL_SPI_Transmit(hspi1,spi_byte,1,100);
}

/**
 * @brief WR_Spi_Nucleo: Envía un byte de datos al sensor y almacena su respuesta en un vhar.
 * 
 * @param spi_byte byte que contiene la información a enviar al sensor.
 * @param rx puntero al char donde será almacenada la respuesta del sensor.
 */
void WR_Spi_Nucleo(uint8_t* spi_byte, char *rx)
{
	HAL_SPI_TransmitReceive(hspi1,spi_byte,rx,1,100);
}

/**
 * @brief FrameTiming_Nucleo: Demora en tiempo menor a ms requerida para definir los tiempos en la trama de datos.
 * 
 * @param timing tiempo (1 unidad = 6 us).
 */
void FrameTiming_Nucleo(uint32_t timing)
{
	__HAL_TIM_SET_COUNTER(htim1,0);  // set the counter value a 0
	while (__HAL_TIM_GET_COUNTER(htim1) < timing);  // wait for the counter to reach the us input in the parameter
}

/**
 * @brief Delay_ms_Nucleo: Demora en milisegundos para definir los tiempos requeridos en la trama de datos.
 * 
 * @param ms tiempo en milisegundos.
 */
void Delay_ms_Nucleo(uint32_t ms)
{
	HAL_Delay(ms);
}
