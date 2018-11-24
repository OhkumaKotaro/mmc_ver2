#include "control.h"
#include "global.h"
#include "tim.h"

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
    float target = 0;
    float encoder_l = 0;
    float encoder_r = 0;
    if(straight_tgt.dir == 0){
        encoder_l = enc_c.velocity;
        encoder_r = enc_c.velocity;
    }else{
        if(straight_tim.up > 0){
            straight_tgt.velocity += straight_tgt.accel * dt;
            straight_tim.up --;
        }else if(straight_tim.cons > 0){
            straight_tim.cons --;
        }else if(straight_tim.down > 0){
            straight_tgt.velocity -= straight_tgt.accel * dt;
            straight_tim.down --;
        }else{
            flag.motion_end = TRUE;
        }
        encoder_l = enc_l.velocity;
        encoder_r = enc_r.velocity;
    }

    target = (float)straight_tgt.dir * straight_tgt.velocity;
    
    straight_pid_l = (int16_t)PID_value(target,encoder_l,&s_sum_l,&s_before_l,4.0f,10.0f,0);
    straight_pid_r = (int16_t)PID_value(target,encoder_r,&s_sum_r,&s_before_r,4.0f,10.0f,0);
}


/****************************************************************************************
 * outline  : call 1ms (control yawrate by feadbuck)
 * argument : void
 * return   : void
********************************************************************************************/
void Yawrate_SysTic_fb(void){
    float target=0;

    if(yawrate_tgt.dir==0){
        yawrate_tgt.velocity = 0;
    }else if(yawrate_tim.up > 0){
        yawrate_tgt.velocity += yawrate_tgt.accel * dt;
        yawrate_tim.up --;
    }else if(yawrate_tim.cons > 0){
        yawrate_tim.cons --;
    }else if(yawrate_tim.down > 0){
        yawrate_tgt.velocity -= yawrate_tgt.accel * dt;
        yawrate_tim.down --;
    }else{
        yawrate_tgt.velocity = 0;
        flag.motion_end = TRUE;
    }

    target = (float)yawrate_tgt.dir * yawrate_tgt.velocity;

    yawrate_pid = (int16_t)PID_value(target,gyro.velocity,&y_sum,&y_before,0.92f,9.0f,4.0f);
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
    if(flag.motion_end == FALSE){
        pwm_l += straight_pid_l;
        pwm_r += straight_pid_r;
    }
    
    if(flag.motion_end == FALSE){
        pwm_l -= yawrate_pid;
        pwm_r += yawrate_pid;
    }
    
    Motor_pwm(pwm_l,pwm_r);
}

void Control_val_reset(void){
    s_sum_l = 0;
    s_before_l = 0;

    s_sum_r = 0;
    s_before_r = 0;

    y_sum = 0;
    y_before = 0;
}