/**
 * @file mlx90316.h
 * @author Andrea García
 * @brief Header for mlx90316.c file.
 *        This file contains the common defines of the application.
 * @version 0.1
 * @date 2022-04-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef INC_MLX90316_H_
#define INC_MLX90316_H_

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define STARTCOM_B1	 0xAA //First byte to initiate communication.
#define STARTCOM_B2	 0xFF //Second byte to initiate communication.
#define F_MAGTOOLOW	 6    //Magnetic Field Too Weak.
#define F_MT7V 		 11  //Device Supply VDD Greater than 7V.
#define EMPTY_INPUT  65532 //Frame asignado cuando no hay respuesta.
#define NO_INIT      65528 //Frame asignado cuando no existe inicialización.

enum _csLevels {
	CS_RESET=0,
	CS_SET};
typedef enum _csLevels cs_t;

typedef void (*CsBoard_t)(cs_t); //funcion con argumento tipo cs_t
typedef void (*W_spiBoard_t)(uint8_t*); //funcion con argumento tipo cs_t
typedef void (*WR_spiBoard_t)(uint8_t*, char*); //funcion con argumento tipo cs_t
typedef void (*Frame_Timing_t)(uint32_t); //funcion de delay en microsegundo
typedef void (*Delay_ms_t)(uint32_t); //funcion de delay en milisegundos

struct _mlx90316  {
	CsBoard_t csMlx;
	W_spiBoard_t wspiMlx;
	WR_spiBoard_t wrspiMlx;
	Frame_Timing_t fTimingMlx;
	Delay_ms_t delay_msMlx;
};
typedef struct _mlx90316 mlx90316_t; //

/**
 * @brief Inicialización de rutina de comunicación SPI con sensor Mlx90316.
 * 
 * @param board_fncs Estructura que contiene las funciones de la tarjeta 
 * NUCLEO-144 F49ZI.
 */

void Mlx90316_Init(mlx90316_t board_fncs); 
/**
 * @brief Obtención de buffer de 16 bits producto de la lectura SPI. 
 * 
 * @return uint16_t buffer leído.
 */
uint16_t Mlx90316_GetRawData();

/**
 * @brief Evalúa si el buffer obtenido es válido para ser procesado.
 * 
 * @param sample buffer de 16 bits con información leída.
 * @return true si el buffer es válido.
 * @return false si el buffer no es válido.
 */
bool Mlx90316_IsValidFrame(uint16_t sample);

/**
 * @brief Cálculo del ángulo obtenido en el buffer.
 * 
 * @param sample buffer de 16 bits con información leída.
 * @return float transformación de los datos en grados.
 */
float Mlx90316_GetAngle(uint16_t sample);

/**
 * @brief Identifica si el buffer contiene un bit de error por campo
 * 		  magnético débil.
 * 
 * @param sample buffer de 16 bits con información leída.
 * @return true existe error de campo magnético débil.
 * @return false no existe error de campo magnético débil.
 */
bool Mlx90316_NoMagnetErr(uint16_t sample);

/**
 * @brief Identifica si el buffer contiene un bit de error por fuente
 * 		  de alimentación mayor a 7v.
 * 
 * @param sample buffer de 16 bits con información leída.
 * @return true existe error de sobre alimentación (7v).
 * @return false no existe error de sobre alimentación (7v).
 */
bool Mlx90316_OverPowerErr(uint16_t sample);


#endif /* INC_MLX90316_H_ */
