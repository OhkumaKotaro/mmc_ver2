#include "other_function.h"
#include "global.h"

void Reset_Flag(void){
    flag.ir_led = FALSE;
    flag.motion_end = TRUE;
    flag.gyro_calc = FALSE;
}

void Reset_Value(void){
    enc_c.distance=0;
    enc_l.distance=0;
    enc_r.distance=0;
    sen_l.before=0;
    sen_front.before=0;
    sen_r.before=0;
}