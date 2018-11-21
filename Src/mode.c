#include "mode.h"
#include "filter.h"
#include "global.h"
#include "gpio.h"

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
    }
}