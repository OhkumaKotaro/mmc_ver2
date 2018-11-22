/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CONTROL_H
#define __CONTROL_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stdint.h"


float PID_value(float target,float measured,float *sum,float *old,float Kp,float Ki,float Kd);
void Straight_SysTic_fb(void);
void Control_pwm(void);


#ifdef __cplusplus
}
#endif
#endif /*__CONTROL_H */