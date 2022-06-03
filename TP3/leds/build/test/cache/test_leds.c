#include "build/test/mocks/mock_errores.h"
#include "src/leds.h"
#include "/var/lib/gems/2.7.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"








static uint16_t virtual_leds;



void setUp(void)

{

    leds_init(&virtual_leds);

}



void tearDown(void)

{



}











void test_leds_off_after_create(void)

{

    uint16_t virtual_leds = 0xFFFF;

    leds_init(&virtual_leds);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((virtual_leds)), (

   ((void *)0)

   ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_HEX16);

}











void test_turn_on_one_led(void)

{

    led_turn_on(5);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((1 << 4)), (UNITY_INT)(UNITY_INT16)((virtual_leds)), (

   ((void *)0)

   ), (UNITY_UINT)(48), UNITY_DISPLAY_STYLE_HEX16);

}











void test_turn_off_one_led(void)

{

    led_turn_on(5);

    led_turn_off(5);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((virtual_leds)), (

   ((void *)0)

   ), (UNITY_UINT)(59), UNITY_DISPLAY_STYLE_HEX16);

}











void test_turn_on_off_many_leds(void)

{

    led_turn_on(5);

    led_turn_on(11);

    led_turn_off(3);

    led_turn_off(11);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((1 << 4)), (UNITY_INT)(UNITY_INT16)((virtual_leds)), (

   ((void *)0)

   ), (UNITY_UINT)(72), UNITY_DISPLAY_STYLE_HEX16);

}











void test_turn_on_all_leds(void)

{

    leds_all_on();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xFFFF)), (UNITY_INT)(UNITY_INT16)((virtual_leds)), (

   ((void *)0)

   ), (UNITY_UINT)(82), UNITY_DISPLAY_STYLE_HEX16);

}











void test_turn_off_all_leds(void)

{

    leds_all_on();

    leds_init(&virtual_leds);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((virtual_leds)), (

   ((void *)0)

   ), (UNITY_UINT)(93), UNITY_DISPLAY_STYLE_HEX16);

}











void test_read_led_val(void)

{

    led_turn_on(14);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((1)), (UNITY_INT)(UNITY_INT16)((read_led_val(14))), (

   ((void *)0)

   ), (UNITY_UINT)(103), UNITY_DISPLAY_STYLE_HEX16);

}











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

    UnityAssertEqualIntArray(( const void*)((limit_leds_expected)), ( const void*)((limit_leds)), (UNITY_UINT32)((4)), (

   ((void *)0)

   ), (UNITY_UINT)(122), UNITY_DISPLAY_STYLE_UINT8, UNITY_ARRAY_TO_ARRAY);

}











void test_invalid_upperlimit_on_led(void)

{

    RegistrarMensaje_CMockExpect(131, ALERTA, "led_turn_on", 0, "Nmero de led invlido");

    RegistrarMensaje_CMockIgnoreArg_linea(132);

    led_turn_on(17);

}
