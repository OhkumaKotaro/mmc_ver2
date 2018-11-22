#include "motion.h"
#include "calculate.h"
#include "global.h"

void Straight_half_accel(void){
    Straight_Calc_fb(90,0,MAX_VELOCITY,MAX_VELOCITY,ACCEL);
    flag.straight = ON;
}

void Straight_half_stop(void){
    Straight_Calc_fb(90,MAX_VELOCITY,0,MAX_VELOCITY,ACCEL);
    flag.straight = ON;
}