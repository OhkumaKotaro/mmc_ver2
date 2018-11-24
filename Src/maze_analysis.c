#include "maze_analysis.h"
#include "maze_infomation.h"
#include "global.h"

/****************************************************************************************************
 * outline : create map
 * argument : void
 * return : void
******************************************************************************************************/
void MAZE_Create_Step( void ){
	/* <概要>   : 歩数マップ作成
	 * <引数>   : 走行の状態( 探索,最短 )
	 * <戻り値> : なし
	 */
	// 初期化
	for( int i = 0; i <= MAZE_SIZE; i++ ){
		for( int j = 0; j <= MAZE_SIZE; j++ ){
			if( i == mazeDef.maze_goal_x && j == mazeDef.maze_goal_y ){
				maze.step[i][j] = 0;
			}
			else{
				maze.step[i][j] = MAX_STEP;
			}
		}
	}

	volatile uint8_t end_flag = TRUE;	// 終了フラグ
	uint8_t stepNum = 0;		// 設定中の歩数
	// 探索
	
	while( end_flag == TRUE ){
		end_flag = FALSE;
		uint8_t i=0;
		for( i = 0; i <= MAZE_SIZE; i++ ){
			uint8_t j=0;
			for( j = 0; j <= MAZE_SIZE; j++ ){
				if( maze.step[i][j] == MAX_STEP ){
					if( j < MAZE_SIZE){	//北壁
						if( (maze.wall_north[i][j] == FALSE)&&(maze.step[i][j+1] == stepNum) ){
							maze.step[i][j] = stepNum + 1;
							end_flag = TRUE;
						}
					}
					if( i < MAZE_SIZE){	//東壁
						if( (maze.wall_east[i][j] == FALSE)&&(maze.step[i+1][j] == stepNum) ){
							maze.step[i][j] = stepNum + 1;
							end_flag = TRUE;
						}
					}
					if( j > 0 ) {					//南壁
						if( (maze.wall_south[i][j] == FALSE)&&(maze.step[i][j-1] == stepNum) ){
							maze.step[i][j] = stepNum + 1;
							end_flag = TRUE;
						}
					}
					if( i > 0 ){					//西壁
						if( (maze.wall_west[i][j] == FALSE)&&(maze.step[i-1][j] == stepNum) ){
							maze.step[i][j] = stepNum + 1;
							end_flag = TRUE;
						}
					}
				}
			}
		}
		if (end_flag == TRUE) {
			stepNum++;
		}
	}
	
}