/**
 * @file mlx90316.c
 * @author Andrea García
 * @brief mlx90316.c file contains the device driver that controls the MLX90316 sensor.
 * @version 0.1
 * @date 2022-04-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef SRC_MLX90316_C_
#define SRC_MLX90316_C_

#include "mlx90316.h"

static mlx90316_t mlx90316_fncs;

static uint8_t IsError(uint16_t _sample)
{
	_sample = _sample&0x02;//analizo el 2do bit menos significativo
	_sample = _sample>>1;//corro uno para dejar solo segundo bit
	if(_sample==1)
	{
		return 1; //Error
	}
	else if(_sample ==0)
	{
		return 0; //No error
	}
}

static float ComputeAngle( uint16_t _sample)
{
	float ans;
	ans = (((float)_sample)*360.0)/16383.0;
	return ans;
}

void Mlx90316_Init(mlx90316_t board_fncs)
{
	mlx90316_fncs.csMlx = board_fncs.csMlx;
	mlx90316_fncs.delay_msMlx = board_fncs.delay_msMlx;
	mlx90316_fncs.fTimingMlx = board_fncs.fTimingMlx;
	mlx90316_fncs.wrspiMlx = board_fncs.wrspiMlx;
	mlx90316_fncs.wspiMlx = board_fncs.wspiMlx;

	mlx90316_fncs.csMlx(CS_SET); //profe crea estructura
	mlx90316_fncs.delay_msMlx(2);
}

float Mlx90316_GetAngle()
{
	char Rx;
	char spi_buffer[8];
	float angle;
	uint8_t b1 = STARTCOM_B1;
	uint8_t b2 = STARTCOM_B2;
	uint16_t sample;
	mlx90316_fncs.csMlx(CS_RESET);
	mlx90316_fncs.fTimingMlx(1); //t6
	mlx90316_fncs.wspiMlx(&b1);
	mlx90316_fncs.wspiMlx(&b2);
	mlx90316_fncs.fTimingMlx(6);//t7
	for (uint8_t i=0;i<8;i++)
	{
		mlx90316_fncs.wrspiMlx(&b2,&Rx);
		spi_buffer[i]=Rx;
		mlx90316_fncs.fTimingMlx(3);//t2
	}
	mlx90316_fncs.csMlx(CS_SET);
	sample = spi_buffer[1]&0xFF; //por orden de llegada el segundo byte de datos lo trunco a 8 bits contiene el bit menos significativo.
	sample|= (spi_buffer[0]&0xFF) << 8; //tomo el primero y corro a la izquierda contiene el bit más sugnificativo. SOlo uno los dos bytes en uno de 16 bit.
	if(IsError(sample)==0)
	{
		sample = sample>>2;
		angle = (ComputeAngle(sample));
	}
	else
	{
		angle = -1.0;
	}
	return angle;
}




#endif /* SRC_MLX90316_C_ */
