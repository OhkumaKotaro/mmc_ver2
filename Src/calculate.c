#include "calculate.h"
#include "global.h"


/****************************************************************************************
 * outline  : calcurate accele distance
 * argument : distance[mm],v_start[mm/s],v_end[mm/s]
 * return   : void
********************************************************************************************/
void Straight_Calc_fb(int16_t distant,int16_t v_start,int16_t v_end,uint16_t v_max,uint16_t accel){
    float t1,t2,t3;
    float constant_L;

    straight_tgt.velocity = v_start;
    straight_tgt.accel = accel;

    if(distant<0){
        distant = -1*distant;
        straight_tgt.dir=-1;
    }else{
        straight_tgt.dir=1;
    }

    t1 = (float)(v_max - v_start) / accel;
    t3 = (float)(v_max - v_end) / accel;

    constant_L = (float)distant - (v_max + v_start) * t1 / 2 - (v_max + v_end) * t3 / 2;

    t2 = constant_L / v_max;

    t1 *= 1000;
    t2 *= 1000;
    t3 *= 1000;

    straight_tim.up = t1;
    straight_tim.cons = t2;
    straight_tim.down = t3;

    //printf("%d %d %d\r\n",accel_T,constant_T,decrease_T);
}
