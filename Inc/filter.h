#ifndef __FILTER_H
#define __FILTER_H
#ifdef __cplusplus
 extern "C" {
#endif

//pt sensor
void update_wall(void);
void All_IR_OFF(void);
void IR_Contoroll(int pattern);
void Input_Sensor(void);
void Batt_check(void);



#ifdef __cplusplus
}
#endif
#endif /*__FILTER_H */