#include "control.h"
#include "global.h"
#include "tim.h"
//#include "stdint.h"

int16_t straight_pid_l = 0;
float s_sum_l = 0;
float s_before_l = 0;

int16_t straight_pid_r = 0;
float s_sum_r = 0;
float s_before_r = 0;

int16_t yawrate_pid = 0;
float y_sum = 0;
float y_before = 0;




/****************************************************************************************
 * outline  : PID control
 * argument : 
 * return   : control value
********************************************************************************************/
float PID_value(float target,float measured,float *sum,float *old,float Kp,float Ki,float Kd){
    float error;
    float p,i,d;

    error = target - measured;
    p = Kp*error;

    *sum += error * dt;
    i = *sum * Ki;

    d = Kd * (error - *old);
    *old = error;

    return (p+i+d);
}

/****************************************************************************************
 * outline  : output pwm for trapezoid accele straight by feadbuck control
 * argument : void
 * return   : void
********************************************************************************************/
void Straight_SysTic_fb(void){
    float target = 1;
    if(straight_tim.up > 0){
        straight_tgt.velocity += straight_tgt.accel * dt;
        straight_tim.up --;
    }
    else if(straight_tim.cons > 0){
        straight_tim.cons --;
    }
    else if(straight_tim.down > 0){
        straight_tgt.velocity -= straight_tgt.accel * dt;
        straight_tim.down --;
    }else{
        flag.straight = OFF;
    }

    target = straight_tgt.dir * straight_tgt.velocity;
    
    straight_pid_l = (int16_t)PID_value(target,enc_l.velocity,&s_sum_l,&s_before_l,4.0f,10.0f,0);
    straight_pid_r = (int16_t)PID_value(target,enc_r.velocity,&s_sum_r,&s_before_r,4.0f,10.0f,0);
}


void Control_pwm(void){
    int16_t pwm_l=0,pwm_r=0;
    /*
    if(flag.wall==ON){
        pwm_l += wall_pid;
        pwm_r -= wall_pid;
    }

    if(flag.fr_wall==ON){
        pwm_l += fr_wall_pid_l;
        pwm_r += fr_wall_pid_r;
    }
    */
    if(flag.straight==ON){
        pwm_l += straight_pid_l;
        pwm_r += straight_pid_r;
    }
    /*
    if(flag.yawrate==ON){
        pwm_l -= yawrate_pid;
        pwm_r += yawrate_pid;
    }
    */
    Motor_pwm(pwm_l,pwm_r);
}