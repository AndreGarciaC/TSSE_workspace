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

#define STARTCOM_B1	 0xAA //First byte to initiate communication.
#define STARTCOM_B2	 0xFF //Second byte to initiate communication.

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
 * Functions prototypes
 */
void Mlx90316_Init(mlx90316_t board_fncs); //add structure of function used by the sensor
float Mlx90316_GetAngle();


#endif /* INC_MLX90316_H_ */
