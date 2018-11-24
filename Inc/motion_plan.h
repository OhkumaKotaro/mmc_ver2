#ifndef __MAZE_PLAN_H
#define __MAZE_PLAN_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stdint.h"


void Update_Position(int8_t next_motion);
int8_t Maze_Next_Motion(void);
void Plan_Adachi(void);



#ifdef __cplusplus
}
#endif
#endif /*__MAZE_PLAN_H */