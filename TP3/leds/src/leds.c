/**
 * @file leds.c
 * @author Andrea Garcia (andregarciace@gmail.com)
 * @brief Código de producción para driver de LEDs virtuales.
 * @version 0.1
 * @date 2022-05-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "errores.h"

#define LED_TO_BIT_OFFSET 1
#define BIT_MASK          1
#define LEDS_ALL_OFF      0
#define LEDS_ALL_ON       65535

static uint16_t * p_port;

uint16_t led_to_mask(uint8_t led)
{
    return (BIT_MASK << (led-LED_TO_BIT_OFFSET));
}

void leds_init(uint16_t * p_address)
{
    p_port = p_address;
    *p_port = LEDS_ALL_OFF;
}

void led_turn_on (uint8_t led)
{
    if (led>16) 
    {
        Alerta("Número de led inválido");
    }
        
    else
    {
        *p_port |= led_to_mask(led) ;
    }
        
}

void led_turn_off (uint8_t led)
{
    *p_port &= ~led_to_mask(led) ;
}

void leds_all_on()
{
    *p_port = LEDS_ALL_ON;
}

uint8_t read_led_val(uint8_t led)
{
    return (*p_port >> (led-1)) & 0x1;
}

