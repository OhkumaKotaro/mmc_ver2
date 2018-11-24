/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CALCULATE_H
#define __CALCULATE_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stdint.h"


void Straight_Calc_fb(int16_t distant,int16_t v_start,int16_t v_end,uint16_t v_max,uint16_t accel);
void Yawrate_Calc_fb(int16_t degree,int16_t v_start,int16_t v_end,int16_t v_max,int16_t accel);



#ifdef __cplusplus
}
#endif
#endif /*__CALCULATE_H */