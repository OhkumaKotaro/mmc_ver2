#ifndef __GLOBAL_H
#define __GLOBAL_H
#ifdef __cplusplus
 extern "C" {
#endif


#include "stdint.h"


//define
//define
#define TRUE 1
#define FALSE 0
//calc
#define dt 0.001f


//flag
typedef struct{
    uint8_t ir_led;
    uint8_t gyro_calc;
}flag_t;

extern volatile flag_t flag;

//adc
typedef struct{
    uint16_t adc_on;
    uint16_t adc_off;
    uint16_t adc;
    uint16_t before;
    int16_t dif;

    uint8_t is_wall;

    uint16_t thresh;
    uint16_t reference;
}sensor_t;

extern sensor_t sen_l;
extern sensor_t sen_fl;
extern sensor_t sen_fr;
extern sensor_t sen_r;
extern sensor_t sen_front;


typedef struct{
    uint16_t adc;
    float voltage;
}batt_t;

extern batt_t batt;



//encoder
typedef struct{
    int cnt;
    float velocity;
    float distance;
    float rpm;
}encoder_t;

extern encoder_t enc_l;
extern encoder_t enc_r;
extern encoder_t enc_c;


//gyro
typedef struct{
    float velocity;
    float degree;
    uint16_t offset_cnt;
    int32_t offset;
}gyro_t;
extern gyro_t gyro;

#ifdef __cplusplus
}
#endif
#endif /*__GLOBAL_H */