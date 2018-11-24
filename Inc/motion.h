/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MOTION_H
#define __MOTION_H
#ifdef __cplusplus
 extern "C" {
#endif

//straight
#define ACCEL 4000 //[mm/s^2]
#define MAX_VELOCITY 400 //[mm/s]

//yawrate
#define Y_ACCEL 2000 //[degree/s^2]//2000
#define Y_MAX_VELOCITY 380//[degree/s]


void Straight_half_accel(void);
void Straight_half_stop(void);
void Straight_const(void);
void LeftTurn(void);
void RightTurn(void);
void U_Turn(void);
void Motion_Start(void);
void Motion_Straight(void);
void Motion_Left(void);
void Motion_Right(void);
void Motion_Uturn(void);
void Motion_Kabe(void);
void Motion_Goal(void);


#ifdef __cplusplus
}
#endif
#endif /*__MOTION_H */