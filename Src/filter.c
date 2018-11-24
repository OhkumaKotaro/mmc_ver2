#include "filter.h"
#include "global.h"
#include "gpio.h"
#include "interface.h"

//pt sensor
void update_wall(void){
  sen_l.adc = sen_l.adc_on - sen_l.adc_off;
  sen_fl.adc = sen_fl.adc_on - sen_fl.adc_off;
  sen_fr.adc = sen_fr.adc_on - sen_fr.adc_off;
  sen_r.adc = sen_r.adc_on - sen_r.adc_off;

  sen_front.adc = ( sen_fl.adc + sen_fr.adc ) /2;
  
  if(sen_l.adc > sen_l.thresh){
    sen_l.is_wall = TRUE;
  }else{
    sen_l.is_wall = FALSE;
  }
  
  if(sen_front.adc > sen_front.thresh){
    sen_front.is_wall = TRUE;
  }else{
    sen_front.is_wall = FALSE;
  }
  
  if(sen_r.adc > sen_r.thresh){
    sen_r.is_wall = TRUE;
  }else{
    sen_r.is_wall = FALSE;
  }
}


/****************************************************************************************
 * outline  : turn off all infrared led
 * argument : void
 * return   : void
********************************************************************************************/
void All_IR_OFF(void){
  HAL_GPIO_WritePin(paluse0_GPIO_Port,paluse0_Pin,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(paluse1_GPIO_Port,paluse1_Pin,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(paluse2_GPIO_Port,paluse2_Pin,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(paluse3_GPIO_Port,paluse3_Pin,GPIO_PIN_RESET);
}

/****************************************************************************************
 * outline  : control infrared led
 * argument : pattern
 *            (front_left  side_right  side_left  front_right
 *                1000        0100        0010       0001     )
 * return   : void
********************************************************************************************/
void IR_Contoroll(int pattern){
  if((pattern & 0b0001) == 0b0001) HAL_GPIO_WritePin(paluse0_GPIO_Port,paluse0_Pin,GPIO_PIN_SET);
  else                             HAL_GPIO_WritePin(paluse0_GPIO_Port,paluse0_Pin,GPIO_PIN_RESET);
  if((pattern & 0b0010) == 0b0010) HAL_GPIO_WritePin(paluse1_GPIO_Port,paluse1_Pin,GPIO_PIN_SET);
  else                             HAL_GPIO_WritePin(paluse1_GPIO_Port,paluse1_Pin,GPIO_PIN_RESET);
  if((pattern & 0b0100) == 0b0100) HAL_GPIO_WritePin(paluse2_GPIO_Port,paluse2_Pin,GPIO_PIN_SET);
  else                             HAL_GPIO_WritePin(paluse2_GPIO_Port,paluse2_Pin,GPIO_PIN_RESET);
  if((pattern & 0b1000) == 0b1000) HAL_GPIO_WritePin(paluse3_GPIO_Port,paluse3_Pin,GPIO_PIN_SET);
  else                             HAL_GPIO_WritePin(paluse3_GPIO_Port,paluse3_Pin,GPIO_PIN_RESET);
}

void Input_Sensor(void){
  sen_l.thresh = 2500;
  sen_l.reference = 2000;

  sen_front.thresh = 3050;
  sen_front.reference = 2000;
  
  sen_r.thresh = 2900;
  sen_r.reference = 2000;
}

//batt check
void Batt_check(void){
  float buffer=0;
  uint8_t pattern;
  for(int i=0;i<10;i++){
    buffer += batt.adc;
  }
  buffer /= 10.0f;
  batt.voltage = buffer/4095.0f*133.0f/33.0f*3.3f;
  pattern=(uint8_t)batt.voltage;

  printf("\nbatt:%lf\r\n",batt.voltage);
  LED_Control(pattern);

  while(1){
    if(Push()==ON){
      Output_Buzzer(HZ_C_H);
      HAL_Delay(500);
      break;
    }
  }
}
