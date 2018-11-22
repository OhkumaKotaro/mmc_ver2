#include "global.h"

//flag
volatile flag_t flag;

//adc
sensor_t sen_l;
sensor_t sen_fl;
sensor_t sen_fr;
sensor_t sen_r;
sensor_t sen_front;

//encoder
encoder_t enc_l;
encoder_t enc_r;
encoder_t enc_c;


//gyro
gyro_t gyro;
//
batt_t batt;

//contorol
trapezoid_tim_t straight_tim;
trapezoid_tim_t yawrate_tim;

target_t straight_tgt;
target_t yawrate_tgt;

uint16_t count_ms;