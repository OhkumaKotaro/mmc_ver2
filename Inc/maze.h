#ifndef __MAZE_H
#define __MAZE_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stdint.h"

//maze info
#define MAX_STEP 254
#define MAZE_SIZE 16

//direction
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

//motion 
#define LEFT 0
#define FRONT 1
#define RIGHT 2
#define UTURN 3
#define KABEATE 4


//mouse position
typedef struct{
  uint8_t x;
  uint8_t y;
  uint8_t dir;
}position_t;
extern position_t position;


typedef struct {							
	uint8_t maze_goal_x;							// ゴールマス( X )
	uint8_t maze_goal_y;							// ゴールマス( Y )
}mazeDef_t;

typedef struct {								// 迷路情報
	uint8_t step[MAZE_SIZE][MAZE_SIZE];							// 歩数マップ
	uint8_t goal[MAZE_SIZE][MAZE_SIZE];
	uint8_t wall_north[MAZE_SIZE][MAZE_SIZE];						// 壁情報
	uint8_t wall_east[MAZE_SIZE][MAZE_SIZE];						// 壁情報
	uint8_t wall_south[MAZE_SIZE][MAZE_SIZE];						// 壁情報
	uint8_t wall_west[MAZE_SIZE][MAZE_SIZE];						// 壁情報
	uint8_t is_search[MAZE_SIZE][MAZE_SIZE];						// 探索済みフラグ
	uint8_t step_mode;						// 歩数マップ作成時の状態(探索用 最短走行用)
}maze_t;

extern maze_t maze;
extern mazeDef_t mazeDef;


#ifdef __cplusplus
}
#endif
#endif /*__MAZE_H */