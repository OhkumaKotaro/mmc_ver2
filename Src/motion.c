#include "motion.h"
#include "calculate.h"
#include "global.h"

void Straight_half_accel(void){
    Straight_Calc_fb(90,0,MAX_VELOCITY,MAX_VELOCITY,ACCEL);
    Yawrate_Calc_fb(0,0,0,0,0);
}

void Straight_half_stop(void){
    Straight_Calc_fb(90,MAX_VELOCITY,0,MAX_VELOCITY,ACCEL);
    Yawrate_Calc_fb(0,0,0,0,0);
}

void Straight_const(void){
    Straight_Calc_fb(180,MAX_VELOCITY,MAX_VELOCITY,MAX_VELOCITY,ACCEL);
    Yawrate_Calc_fb(0,0,0,0,0);
}

void LeftTurn(void){
    Straight_Calc_fb(0,0,0,0,0);
    Yawrate_Calc_fb(90,0,0,Y_MAX_VELOCITY,Y_ACCEL);
}

void RightTurn(void){
    Straight_Calc_fb(0,0,0,0,0);
    Yawrate_Calc_fb(-90,0,0,Y_MAX_VELOCITY,Y_ACCEL);
}

void U_Turn(void){
    Straight_Calc_fb(0,0,0,0,0);
    Yawrate_Calc_fb(180,0,0,Y_MAX_VELOCITY,Y_ACCEL);
}

void Motion_Start(void){
    Straight_Calc_fb(-55,0,0,200,2000);
    Yawrate_Calc_fb(0,0,0,0,0);
    while(flag.motion_end==FALSE){}
    Straight_Calc_fb(137,0,MAX_VELOCITY,MAX_VELOCITY,ACCEL);
    Yawrate_Calc_fb(0,0,0,0,0);
    while(flag.motion_end==FALSE){}
}


void Motion_Straight(void){
    Straight_const();
    while(flag.motion_end==FALSE){}
}

void Motion_Left(void){
    Straight_half_stop();
    while(flag.motion_end==FALSE){}
    LeftTurn();
    while(flag.motion_end==FALSE){}
    Straight_half_accel();
    while(flag.motion_end==FALSE){}
}

void Motion_Right(void){
    Straight_half_stop();
    while(flag.motion_end==FALSE){}
    RightTurn();
    while(flag.motion_end==FALSE){}
    Straight_half_accel();
    while(flag.motion_end==FALSE){}
}

void Motion_Uturn(void){
    Straight_half_stop();
    while(flag.motion_end==FALSE){}
    U_Turn();
    while(flag.motion_end==FALSE){}
    Straight_half_accel();
    while(flag.motion_end==FALSE){}
}

void Motion_Kabe(void){
    //U turn 
    Straight_half_stop();
    while(flag.motion_end==FALSE){}
    U_Turn();
    while(flag.motion_end==FALSE){}
    Straight_half_accel();
    while(flag.motion_end==FALSE){}
    //kabeate
    Straight_Calc_fb(-55,0,0,200,2000);
    Yawrate_Calc_fb(0,0,0,0,0);
    while(flag.motion_end==FALSE){}
    Straight_Calc_fb(137,0,MAX_VELOCITY,MAX_VELOCITY,ACCEL);
    Yawrate_Calc_fb(0,0,0,0,0);
    while(flag.motion_end==FALSE){}
}

void Motion_Goal(void){
    Straight_half_stop();
    while(flag.motion_end==FALSE){}
}