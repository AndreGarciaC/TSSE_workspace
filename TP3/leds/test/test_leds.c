/**
 * @file test_leds.c
 * @author Andrea García (andregarciace@gmail.com)
 * @brief TDD (Test-Driven Development) para controlador de LEDs virtuales.
 * @version 0.1
 * @date 2022-05-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "unity.h"
#include "leds.h"
#include "mock_errores.h"

#define LEDS_ALL_ON_HEX      0xFFFF
#define LEDS_ALL_OFF_HEX     0x0000

static uint16_t virtual_leds;

void setUp(void)
{
    leds_init(&virtual_leds);
}

void tearDown(void)
{

}

/**
 * @brief Test que apaga todos los LEDs después de la inicialización.
 * 
 */
void test_leds_off_after_create(void)
{
    uint16_t virtual_leds =  LEDS_ALL_ON_HEX;
    leds_init(&virtual_leds);
    TEST_ASSERT_EQUAL_HEX16(LEDS_ALL_OFF_HEX, virtual_leds);
}

/**
 * @brief Test para prender un LED individual.
 * 
 */
void test_turn_on_one_led(void)
{
    led_turn_on(5);
    TEST_ASSERT_EQUAL_HEX16(1 << 4, virtual_leds);
}

/**
 * @brief Test para apagar un LED individual.
 * 
 */
void test_turn_off_one_led(void)
{
    led_turn_on(5);
    led_turn_off(5);
    TEST_ASSERT_EQUAL_HEX16(0x0000, virtual_leds);
}

/**
 * @brief Test para prender y apagar múltiples LEDs.
 * 
 */
void test_turn_on_off_many_leds(void)
{
    led_turn_on(5);
    led_turn_on(11);
    led_turn_off(3);
    led_turn_off(11);
    TEST_ASSERT_EQUAL_HEX16(1 << 4, virtual_leds);
}

/**
 * @brief Test para prender todos los LEDs.
 * 
 */
void test_turn_on_all_leds(void)
{
    leds_all_on();
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, virtual_leds);
}

/**
 * @brief Test para apagar todos los LEDs.
 * 
 */
void test_turn_off_all_leds(void)
{
    leds_all_on();
    leds_init(&virtual_leds);
    TEST_ASSERT_EQUAL_HEX16(0x0000, virtual_leds);
}

/**
 * @brief Test para leer el valor de un LED.
 * 
 */
void test_read_led_val(void)
{
    led_turn_on(14);
    TEST_ASSERT_EQUAL_HEX16(1, read_led_val(14));
}

/**
 * @brief Test para evaluar los LEDs de los extremos o límites.
 * 
 */
void test_limit_leds(void)
{
    uint8_t limit_leds[4] = {0};
    uint8_t limit_leds_expected[] = {1,1,0,0};
    led_turn_on(1);
    led_turn_on(16);
    limit_leds[0] = read_led_val(1);
    limit_leds[1] = read_led_val(16);
    led_turn_off(1);
    led_turn_off(16);
    limit_leds[2] = read_led_val(1);
    limit_leds[3] = read_led_val(16);
    TEST_ASSERT_EQUAL_UINT8_ARRAY (limit_leds_expected, limit_leds, 4);
}

/**
 * @brief Test para registrar alerta en caso de led inválido.
 * 
 */
void test_invalid_upperlimit_on_led(void)
{
    RegistrarMensaje_Expect(ALERTA,"led_turn_on",0,"Número de led inválido");
    RegistrarMensaje_IgnoreArg_linea();
    led_turn_on(17);
}