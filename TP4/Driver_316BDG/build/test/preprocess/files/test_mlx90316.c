#include "inc/mlx90316.h"
#include "/var/lib/gems/2.7.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"
void test_invalid_frame(void)

{

    int16_t sample = 65532;

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((

   0

   )), (UNITY_INT)(UNITY_INT16)((Mlx90316_IsValidFrame(sample))), (

   ((void *)0)

   ), (UNITY_UINT)(15), UNITY_DISPLAY_STYLE_INT16);

    do { UnityMessage(("Identificacion de frame invalido de datos: exitosa."), 16); longjmp(Unity.AbortFrame, 1); } while(0);

}



void test_angulo_correcto(void)

{

    int16_t sample = 8037;

    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((44.145760)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((44.145760))), (UNITY_FLOAT)((UNITY_FLOAT)((Mlx90316_GetAngle(sample)))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(22)));

    do { UnityMessage(("Calculo correcto de angulo: exitoso."), 23); longjmp(Unity.AbortFrame, 1); } while(0);

}



void test_detect_error_frame(void)

{

    int16_t sample = 642;

    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((-1.0)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((-1.0))), (UNITY_FLOAT)((UNITY_FLOAT)((Mlx90316_GetAngle(sample)))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(29)));

    do { UnityMessage(("Identificacion de frame de error: exitosa."), 30); longjmp(Unity.AbortFrame, 1); } while(0);

}



void test_detect_magnet_error(void)

{

     int16_t sample = 34;

    do {if ((Mlx90316_NoMagnetErr(sample))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(36)));}} while(0);

    do { UnityMessage(("Identificacion de error por ausencia de iman: exitosa."), 37); longjmp(Unity.AbortFrame, 1); } while(0);

}



void test_detect_over_power_error(void)

{

     int16_t sample = 1426;

    do {if ((Mlx90316_OverPowerErr(sample))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(43)));}} while(0);

    do { UnityMessage(("Identificacion de error por alimentacion > 7v: exitosa."), 44); longjmp(Unity.AbortFrame, 1); } while(0);

}



void test_no_magnet_error(void)

{

     int16_t sample = 642;

    do {if (!(Mlx90316_NoMagnetErr(sample))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(50)));}} while(0);

    do { UnityMessage(("Identificacion de inexistencia de error por ausencia de iman: exitosa."), 51); longjmp(Unity.AbortFrame, 1); } while(0);

}



void test_no_over_power_error(void)

{

     int16_t sample = 642;

    do {if (!(Mlx90316_OverPowerErr(sample))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(57)));}} while(0);

    do { UnityMessage(("Identificacion de inexistencia de error por alimentacion > 7v: exitosa."), 58); longjmp(Unity.AbortFrame, 1); } while(0);

}
