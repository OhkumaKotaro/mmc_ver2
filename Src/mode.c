#include "mode.h"
#include "filter.h"
#include "global.h"
#include "gpio.h"
#include "interface.h"
#include "motion.h"
#include "spi.h"
#include "motion_plan.h"



/****************************************************************************************
 * outline  : wright mode 
 * argument : mode nomber
 * return   : void
********************************************************************************************/
void Mode_mouse(int8_t mode){
    switch(mode){
        case 0:
            Mode_Run();
            break;
        case 1:
            flag.ir_led = TRUE;
            while(sen_front.is_wall != TRUE){}
            flag.ir_led = FALSE;
            Output_Buzzer(HZ_F);
            gyro_offset_calc_reset();
            HAL_Delay(2500);
            LeftTurn();
            while(flag.motion_end==FALSE){}
            break;
        case 2:
            flag.ir_led = TRUE;
            while(sen_front.is_wall != TRUE){}
            flag.ir_led = FALSE;
            Output_Buzzer(HZ_F);
            gyro_offset_calc_reset();
            HAL_Delay(2500);
            RightTurn();
            while(flag.motion_end==FALSE){}
            break;
        case 3:
            flag.ir_led = TRUE;
            while(sen_front.is_wall != TRUE){}
            flag.ir_led = FALSE;
            Output_Buzzer(HZ_F);
            gyro_offset_calc_reset();
            HAL_Delay(2500);
            U_Turn();
            while(flag.motion_end==FALSE){}
            break;
        case 4:
            
            break;
        case 5:
            
            break;
        case 6:
            Mode_Sensor_Check();
            break;
        default:
            break;
    }
}


/****************************************************************************************
 * outline  : return mode nomber
 * argument : void
 * return   : mode nomber 
********************************************************************************************/
int8_t Mode_select(void){
    int8_t mode=0;
    while(1){
        if((int16_t)enc_l.distance > 30 || (int16_t)enc_l.distance < -30){
            if((int16_t)enc_l.distance > 30){
                mode++;
            }else if((int16_t)enc_l.distance < -30){
                mode--;
            }
            if(mode > 6){
                mode = 0;
            }else if(mode < 0){
                mode = 6;
            }
            enc_l.distance = 0;
            Output_Buzzer(170-10*mode);
        }
        if(Push()==ON){
            Output_Buzzer(HZ_C_H);
            HAL_Delay(500);
            break;
        }
        LED_Control(mode);
        printf("%d\r",mode);
    }
    return mode;
}


void Mode_Run(void){
    Plan_Adachi();
}


void Mode_Sensor_Check(void){
    flag.ir_led = TRUE;
    while(1){
        if(sen_r.is_wall==TRUE){
            HAL_GPIO_WritePin(led0_GPIO_Port,led0_Pin,GPIO_PIN_RESET);
        }else{
            HAL_GPIO_WritePin(led0_GPIO_Port,led0_Pin,GPIO_PIN_SET);
        }
        if(sen_l.is_wall==TRUE){
            HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,GPIO_PIN_RESET);
        }else{
            HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,GPIO_PIN_SET);
        }
        if(sen_front.is_wall==TRUE){
            HAL_GPIO_WritePin(led3_GPIO_Port,led3_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(led2_GPIO_Port,led2_Pin,GPIO_PIN_RESET);
        }else{
            HAL_GPIO_WritePin(led3_GPIO_Port,led3_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(led2_GPIO_Port,led2_Pin,GPIO_PIN_SET);
        }
        printf("l:%d f:%d r:%d \r",sen_l.adc,sen_front.adc,sen_r.adc);

        if(Push()==ON){
            Output_Buzzer(HZ_C_H);
            HAL_Delay(500);
            break;
        }
    }
}