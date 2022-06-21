#include "unity.h"
#include "mlx90316.h"
#define UNITY_INCLUDE_FLOAT

#define INVALID_FR      65532 //0b1111111111111100
#define ERROR_FR        642   //0b0000001010000010
#define ANGLE_FR        8037  //0b0001111101100101
#define MG_ERROR_FR     34    //0b0000000000100010
#define PWR_ERROR_FR    1426  //0b0000010110010010

/**
 * @brief Test que evalúa la identificación del buffer de datos 
 *        como un valor válido para procesar.
 * 
 */
void test_invalid_frame(void)
{
    int16_t sample = INVALID_FR;
    TEST_ASSERT_EQUAL_INT16(false, Mlx90316_IsValidFrame(sample));
    TEST_PASS_MESSAGE("Identificacion de frame invalido de datos: exitosa.");
}
/**
 * @brief Test que evalúa el correcto cálculo del ángulo.
 * 
 */
void test_angulo_correcto(void)
{
    int16_t sample = ANGLE_FR;
    TEST_ASSERT_EQUAL_FLOAT(44.145760, Mlx90316_GetAngle(sample));
    TEST_PASS_MESSAGE("Calculo correcto de angulo: exitoso.");
}
/**
 * @brief Test que evalúa la identificación del buffer de datos 
 *        como frame de error.
 * 
 */
void test_detect_error_frame(void)
{
    int16_t sample = ERROR_FR;
    TEST_ASSERT_EQUAL_FLOAT(-1.0, Mlx90316_GetAngle(sample));
    TEST_PASS_MESSAGE("Identificacion de frame de error: exitosa.");
}
/**
 * @brief Test que evalúa la detección del buffer de datos 
 *        como frame de error por campo magnético débil.
 * 
 */
void test_detect_magnet_error(void)
{
     int16_t sample = MG_ERROR_FR;
    TEST_ASSERT_TRUE(Mlx90316_NoMagnetErr(sample));
    TEST_PASS_MESSAGE("Identificacion de error por ausencia de iman: exitosa.");
}
/**
 * @brief Test que evalúa la detección del buffer de datos como
 *        frame de error por voltaje de alimentación >7v.
 * 
 */
void test_detect_over_power_error(void)
{
     int16_t sample = PWR_ERROR_FR;
    TEST_ASSERT_TRUE(Mlx90316_OverPowerErr(sample));
    TEST_PASS_MESSAGE("Identificacion de error por alimentacion > 7v: exitosa.");
}
/**
 * @brief Test que evalúa la incorrecta detección del buffer de datos como
 *        frame de error por voltaje de alimentación >7v.
 * 
 */
void test_no_magnet_error(void)
{
     int16_t sample = ERROR_FR;
    TEST_ASSERT_FALSE(Mlx90316_NoMagnetErr(sample));
    TEST_PASS_MESSAGE("Identificacion de inexistencia de error por ausencia de iman: exitosa.");
}
/**
 * @brief Test que evalúa la incorrecta detección del buffer de datos como
 *        frame de error por voltaje de alimentación >7v.
 * 
 */
void test_no_over_power_error(void)
{
     int16_t sample = ERROR_FR;
    TEST_ASSERT_FALSE(Mlx90316_OverPowerErr(sample));
    TEST_PASS_MESSAGE("Identificacion de inexistencia de error por alimentacion > 7v: exitosa.");
}   

