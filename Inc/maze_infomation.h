#ifndef __MAZE_INFOMATION_H
#define __MAZE_INFOMATION_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stdint.h"


//maze info
#define MAX_STEP 254
#define MAZE_SIZE 16



void Maze_Set(void);
void Init_maze(void);
void Maze_Get_Wall( int8_t x, int8_t y);
void MAZE_Printf_Step(void);






#ifdef __cplusplus
}
#endif
#endif /*__MAZE_INFOMATION_H */