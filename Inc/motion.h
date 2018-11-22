/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MOTION_H
#define __MOTION_H
#ifdef __cplusplus
 extern "C" {
#endif

//straight
#define ACCEL 4000 //[mm/s^2]
#define MAX_VELOCITY 400 //[mm/s]


void Straight_half_accel(void);
void Straight_half_stop(void);


#ifdef __cplusplus
}
#endif
#endif /*__MOTION_H */