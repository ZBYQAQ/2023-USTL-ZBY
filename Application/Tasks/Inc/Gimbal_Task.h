#ifndef GIMBAL_TASK_H
#define GIMBAL_TASK_H
#include "stdint.h"
#include "pid.h"

typedef struct 
{
   float v1,v2;
	struct{
		 int16_t v1_velocity;
	   int16_t v2_velocity;
	 }Target;
			int16_t SendValue[8]; 
}Gimbal_Info_Typedef;
	

extern Gimbal_Info_Typedef Gimbal_Info;





#endif

