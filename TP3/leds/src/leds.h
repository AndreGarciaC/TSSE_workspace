/**
 * @file leds.h
 * @author Andrea Garcia (andregarciace@gmail.com)
 * @brief Código de producción para driver de LEDs virtuales.
 * @version 0.1
 * @date 2022-05-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#define _LEDS_H

#include <stdint.h>

/**
 * @brief Configura la biblioteca y apaga todos los LEDs.
 * 
 * @param direccion Dircción del puerto GPIO que controla los LEDs.
 */
void leds_init(uint16_t * direccion);

/**
 * @brief Prende un LED.
 * 
 * @param led Número de LED a prender (1 al 16).
 */
void led_turn_on(uint8_t led);

/**
 * @brief Apaga un LED.
 * 
 * @param led Número de LED a apagar (1 al 16).
 */
void led_turn_off(uint8_t led);

/**
 * @brief Prende todos los LEDs.
 * 
 */
void leds_all_on();

/**
 * @brief Lee el estado de un LED.
 * 
 * @param led Número de LED a leer.
 * @return uint8_t Estado del LED leído (1 o 0).
 */
uint8_t read_led_val(uint8_t led);
#endif