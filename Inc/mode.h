#ifndef __MODE_H
#define __MODE_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stdint.h"

void Mode_mouse(int8_t mode);
int8_t Mode_select(void);
void Mode_Sensor_Check(void);

#ifdef __cplusplus
}
#endif
#endif /*__MODE_H */