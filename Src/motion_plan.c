#include "motion_plan.h"
#include "global.h"
#include "maze.h"
#include "motion.h"
#include "interface.h"
#include "maze_infomation.h"
#include "maze_analysis.h"


void Update_Position(int8_t next_motion){
	switch(next_motion){
		case LEFT:
			switch(position.dir){
				case NORTH:
					position.x --;
					position.dir = WEST;
					break;
				case EAST:
					position.y ++;
					position.dir = NORTH;
					break;
				case SOUTH:
					position.x ++;
					position.dir = EAST;
					break;
				case WEST:
					position.y --;
					position.dir = SOUTH;
					break;
			}
			break;
		case FRONT:
			switch(position.dir){
				case NORTH:
					position.y ++;
					break;
				case EAST:
					position.x ++;
					break;
				case SOUTH:
					position.y --;
					break;
				case WEST:
					position.x --;
					break;
			}
			break;
		case RIGHT:
			switch(position.dir){
				case NORTH:
					position.x ++;
					position.dir = EAST;
					break;
				case EAST:
					position.y --;
					position.dir = SOUTH;
					break;
				case SOUTH:
					position.x --;
					position.dir = WEST;
					break;
				case WEST:
					position.y ++;
					position.dir = NORTH;
					break;
			}
			break;
		case UTURN:
			switch(position.dir){
				case NORTH:
					position.y --;
					position.dir = SOUTH;
					break;
				case EAST:
					position.x --;
					position.dir = WEST;
					break;
				case SOUTH:
					position.y ++;
					position.dir = NORTH;
					break;
				case WEST:
					position.x ++;
					position.dir = EAST;
					break;
			}
			break;
		case KABEATE:
			switch(position.dir){
				case NORTH:
					position.y --;
					position.dir = SOUTH;
					break;
				case EAST:
					position.x --;
					position.dir = WEST;
					break;
				case SOUTH:
					position.y ++;
					position.dir = NORTH;
					break;
				case WEST:
					position.x ++;
					position.dir = EAST;
					break;
			}
			break;
	}
}



int8_t Maze_Next_Motion(void){
	/* <概要>   : 次の動作を決定
	 * <引数>   : なし
	 * <戻り値> : 次の動作
	 */
	uint8_t tmp_step = MAX_STEP;		// 歩数
	int8_t tmp_dir = UTURN;				// 方向
	// 現在の向きに応じて場合分けし、 歩数が少ない方向を判断
	// 迷路外に進むのとゴールがスタートマス以外の場合(0,0)に進むのを阻止
	switch( position.dir ){
		case NORTH:
			if( maze.step[position.x][position.y+1] < tmp_step ){
				if( position.y < MAZE_SIZE-1 ){
					if( maze.wall_north[position.x][position.y] == FALSE ){
						tmp_step = maze.step[position.x][position.y+1];
						tmp_dir = FRONT;
					}
				}
			}
			if( maze.step[position.x-1][position.y] < tmp_step ){
				if( position.x > 0 ){
					if( maze.wall_west[position.x][position.y] == FALSE ){
						tmp_step = maze.step[position.x-1][position.y];
						tmp_dir = LEFT;
					}
				}
			}
			if( maze.step[position.x+1][position.y] < tmp_step ){
				if( position.x < MAZE_SIZE-1 ){
					if( maze.wall_east[position.x][position.y] == FALSE){
						tmp_step = maze.step[position.x+1][position.y];
						tmp_dir = RIGHT;
					}
				}
			}
			if( tmp_step == MAX_STEP){
				if(maze.wall_north[position.x][position.y] == FALSE){
					tmp_dir = UTURN;
				}else if(maze.wall_north[position.x][position.y] == TRUE){
					tmp_dir = KABEATE;
				}
				
			}
			break;
		case EAST:
			if( maze.step[position.x+1][position.y] < tmp_step ){
				if( position.x < MAZE_SIZE-1 ){
					if( maze.wall_east[position.x][position.y] == FALSE){
						tmp_step = maze.step[position.x+1][position.y];
						tmp_dir = FRONT;
					}
				}
			}
			if( maze.step[position.x][position.y+1] < tmp_step ){
				if( position.y < MAZE_SIZE-1 ){
					if( maze.wall_north[position.x][position.y] == FALSE ){
						tmp_step = maze.step[position.x][position.y+1];
						tmp_dir = LEFT;
					}
				}
			}
			if( maze.step[position.x][position.y-1] < tmp_step ){
				if( position.y > 0 ){
					if( maze.wall_south[position.x][position.y] == FALSE ){
						tmp_step = maze.step[position.x][position.y-1];
						tmp_dir = RIGHT;
					}
				}
			}
			if( tmp_step == MAX_STEP){
				if(maze.wall_east[position.x][position.y] == FALSE){
					tmp_dir = UTURN;
				}else if(maze.wall_east[position.x][position.y] == TRUE){
					tmp_dir = KABEATE;
				}
			}
			break;
		case SOUTH:
			if( maze.step[position.x][position.y-1] < tmp_step ){
				if( position.y > 0 ){
					if( maze.wall_south[position.x][position.y] == FALSE ){
						tmp_step = maze.step[position.x][position.y-1];
						tmp_dir = FALSE;
				    }
				}
			}
			if( maze.step[position.x+1][position.y] < tmp_step ){
				if( position.x < MAZE_SIZE-1){
					if( maze.wall_east[position.x][position.y] == FALSE ){
						tmp_step = maze.step[position.x+1][position.y];
						tmp_dir = LEFT;
					}
				}
			}
			if( maze.step[position.x-1][position.y] < tmp_step ){
				if( position.x > 0 ){
					if( maze.wall_west[position.x][position.y] == FALSE ){
						tmp_step = maze.step[position.x-1][position.y];
						tmp_dir = RIGHT;
					}
				}
			}
			if( tmp_step == MAX_STEP){
				if(maze.wall_south[position.x][position.y] == FALSE){
					tmp_dir = UTURN;
				}else if(maze.wall_south[position.x][position.y] == TRUE){
					tmp_dir = KABEATE;
				}
			}
			break;
		case WEST:
			if( maze.step[position.x-1][position.y] < tmp_step ){
				if( position.x > 0 ){
					if( maze.wall_west[position.x][position.y] == FALSE ){
						tmp_step = maze.step[position.x-1][position.y];
						tmp_dir = FRONT;
					}
				}
			}
			if( maze.step[position.x][position.y-1] < tmp_step ){
				if( position.y > 0 ){
					if( maze.wall_south[position.x][position.y] == FALSE ){
						tmp_step = maze.step[position.x][position.y-1];
						tmp_dir = LEFT;
					}
				}
			}
			if( maze.step[position.x][position.y+1] < tmp_step ){
				if( position.y < MAZE_SIZE-1 ){
					if( maze.wall_north[position.x][position.y] == FALSE){
						tmp_step = maze.step[position.x][position.y+1];
						tmp_dir = RIGHT;
					}
				}
			}
			if( tmp_step == MAX_STEP){
				if(maze.wall_west[position.x][position.y] == FALSE){
					tmp_dir = UTURN;
				}else if(maze.wall_west[position.x][position.y] == TRUE){
					tmp_dir = KABEATE;
				}
			}
			break;
		default:
			break;
	}
	return tmp_dir;
}

void Plan_Adachi(void){
	uint8_t flag_goal_is=FALSE;
    int8_t next_dir;

   
    Init_maze();

    flag.ir_led = ON;
    while(sen_front.is_wall==FALSE){}
	Output_Buzzer(HZ_G);
    gyro_offset_calc_reset();
    HAL_Delay(2500);
    Motion_Start();
    position.x=0;
    position.y=1;
    position.dir=NORTH;
    Maze_Set();
    
    while(flag_goal_is==FALSE){
        Maze_Get_Wall(position.x,position.y);
        MAZE_Create_Step();
        next_dir=Maze_Next_Motion();
        Update_Position(next_dir);
        if(position.x==mazeDef.maze_goal_x && position.y==mazeDef.maze_goal_y){
            flag_goal_is=TRUE;
        }

        switch( next_dir ){
            case LEFT:
                Motion_Left();
                break;

            case FRONT:
                Motion_Straight();
                break;
            
            case RIGHT:
                Motion_Right();
                break;

            case UTURN:
                Motion_Uturn();
                break;
            case KABEATE:
                Motion_Kabeate();
                break;
        }
    }
    Motion_Goal();
}