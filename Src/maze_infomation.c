#include "maze_infomation.h"
#include "global.h"
#include "maze.h"



/****************************************************************************************************
 * outline : input maze size , goal point
 * argument : void
 * return : void
******************************************************************************************************/
void Maze_Set(void){
    mazeDef.maze_goal_x = 1;
    mazeDef.maze_goal_y = 0;
}


/****************************************************************************************************
 * outline : initialize maze date
 * argument : void
 * return : void
******************************************************************************************************/
void Init_maze(void){
	//init wall and is_search
	for (int i = 0; i < MAZE_SIZE; i++)
	{
		for (int j = 0; j < MAZE_SIZE; j++)
		{
			maze.wall_east[i][j] = 0;
			maze.wall_north[i][j] = 0;
			maze.wall_south[i][j] = 0;
			maze.wall_west[i][j] = 0;
			maze.is_search[i][j] = 0;
			maze.goal[i][j] = 0;
		}
	}
	//input start wall
	maze.wall_east[0][0] = 1;
	maze.wall_west[1][0] = 1;
	//input outer
	for (int i = 0; i < MAZE_SIZE; i++)
	{
		maze.wall_east[MAZE_SIZE-1][i] = 1;
		maze.wall_west[0][i] = 1;
        maze.wall_south[i][0] = 1;
		maze.wall_north[i][MAZE_SIZE-1] = 1;
	}
}


void Maze_Get_Wall( int8_t x, int8_t y){
	int n_wall=0, e_wall=0, s_wall=0, w_wall=0;

	// 探索済みに設定
	maze.is_search[x][y] = TRUE;
	// 方向別に壁の状態を取得
	switch( position.dir ){
	case NORTH:
		n_wall = sen_front.is_wall;
		e_wall = sen_r.is_wall;
		w_wall = sen_l.is_wall;
		s_wall = 0;
		break;
	case EAST:
		e_wall = sen_front.is_wall;
		s_wall = sen_r.is_wall;
		n_wall = sen_l.is_wall;
		w_wall = 0;
		break;
	case SOUTH:
		s_wall = sen_front.is_wall;
		w_wall = sen_r.is_wall;
		e_wall = sen_l.is_wall;
		n_wall = 0;
		break;
	case WEST:
		w_wall = sen_front.is_wall;
		n_wall = sen_r.is_wall;
		s_wall = sen_l.is_wall;
		e_wall = 0;
		break;
	default:
		break;
	}
	// 方向別に保存
	maze.wall_north[x][y] = n_wall;
	maze.wall_east[x][y] = e_wall;
	maze.wall_south[x][y] = s_wall;
	maze.wall_west[x][y] = w_wall;
	// 隣り合う壁の情報を保存
	if( y < MAZE_SIZE-1 ){
		maze.wall_south[x][y+1] = n_wall;
	}
	if( x < MAZE_SIZE-1){
		maze.wall_west[x+1][y] = e_wall;
	}
	if(y > 0){
		maze.wall_north[x][y-1] = s_wall;
	}
	if(x > 0){
		maze.wall_east[x-1][y] = w_wall;
	}
}


/****************************************************************************************************
 * outline : output step
 * argument : void
 * return : void
******************************************************************************************************/
void MAZE_Printf_Step(void){
	int i=0;
	for (i = 0; i < MAZE_SIZE; i++)
	{
		int j;
		for (j = 0; j < MAZE_SIZE; j++)
		{
			printf("+");
			if (maze.wall_west[i][j] == 1)
			{
				printf("---");
			}
			else if(maze.wall_west[i][j] == 0)
			{
				printf("   ");
			}
		}
		printf("+\r\n");
		for (j = 0; j < MAZE_SIZE; j++)
		{
			if (maze.wall_south[i][j] == 1)
			{
				printf("|");
			}
			else
			{
				printf(" ");
			}
			printf("%3d", maze.step[i][j]);
		}
		printf("|\r\n");
	}
	for (i = 0; i < MAZE_SIZE; i++)
	{
		printf("+");
		printf("---");
	}
	printf("+\r\n\n");
}



void Maze_GoalCheck(uint8_t flag_goal_is){
	if(position.x==mazeDef.maze_goal_x && position.y==mazeDef.maze_goal_y){
		flag_goal_is = TRUE;
	}
}