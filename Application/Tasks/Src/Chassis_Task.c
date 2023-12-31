#include "Chassis_Task.h"
#include "cmsis_os.h"
#include "motor.h"
#include "remote_control.h"
#include "arm_math.h"
Chassis_Info_Typedef Chassis_Info={
   .vx = 0,
   .vy = 0,
	 .vw = 0,
	.SendValue=0,
};
float Wheel_PID_Param_A_velocity[6]={10,0,0,0.f,5000.f,15000,};
float Wheel_PID_Param_B_velocity[6]={10,0,0,0.f,5000.f,15000,};
float Wheel_PID_Param_C_velocity[6]={10,0,0,0.f,5000.f,15000,};
float Wheel_PID_Param_D_velocity[6]={10,0,0,0.f,5000.f,15000,};

PID_Info_TypeDef Chassis_PID_v1;
PID_Info_TypeDef Chassis_PID_v2;
PID_Info_TypeDef Chassis_PID_v3;
PID_Info_TypeDef Chassis_PID_v4;

static void Chassis_Task_Init(void);
static void Quanxiang_Calculate(Chassis_Info_Typedef *Chassis_Info);

void Chassis_Task(void const * argument)
{
	
  Chassis_Task_Init();
  for(;;)
  {
		if(remote_ctrl.rc.s[0]==1)
		{
		  Chassis_Info.SendValue[0]=0;
			Chassis_Info.SendValue[0]=0;
			Chassis_Info.SendValue[0]=0;
			Chassis_Info.SendValue[0]=0;
		}
		else
		{
    Quanxiang_Calculate(&Chassis_Info);
	}
		
		osDelay(1);
  }
		//osDelay(1);
}
//���������ʼ��  
  static void Chassis_Task_Init(){
  PID_Init(&Chassis_PID_v1,PID_POSITION,Wheel_PID_Param_A_velocity); 
  PID_Init(&Chassis_PID_v2,PID_POSITION,Wheel_PID_Param_B_velocity);
  PID_Init(&Chassis_PID_v3,PID_POSITION,Wheel_PID_Param_C_velocity);
	PID_Init(&Chassis_PID_v4,PID_POSITION,Wheel_PID_Param_D_velocity);
}
static void Quanxiang_Calculate(Chassis_Info_Typedef *Chassis_Info){

	//���ֽ���
	//left&front
	Chassis_Info->Target.A_velocity = Chassis_Info->vx + Chassis_Info->vy+Chassis_Info->vw;
	//right&front
  Chassis_Info->Target.B_velocity = -Chassis_Info->vx + Chassis_Info->vy+Chassis_Info->vw;
	//left&behind
  Chassis_Info->Target.C_velocity = Chassis_Info->vx - Chassis_Info->vy+Chassis_Info->vw;
	//right&behind
  Chassis_Info->Target.D_velocity = -Chassis_Info->vx - Chassis_Info->vy+Chassis_Info->vw;
  //ң��������
	Chassis_Info->vx = remote_ctrl.rc.ch[3]*6;
  Chassis_Info->vy = remote_ctrl.rc.ch[2]*6;
  Chassis_Info->vw = remote_ctrl.rc.ch[0]*6;
//PID����
	Chassis_Info->SendValue[0]=f_PID_Calculate(&Chassis_PID_v1,Chassis_Info->Target.A_velocity,Chassis_motor[A].Data.velocity);
	Chassis_Info->SendValue[1]=f_PID_Calculate(&Chassis_PID_v2,Chassis_Info->Target.B_velocity,Chassis_motor[B].Data.velocity);
	Chassis_Info->SendValue[2]=f_PID_Calculate(&Chassis_PID_v3,Chassis_Info->Target.C_velocity,Chassis_motor[C].Data.velocity);
	Chassis_Info->SendValue[3]=f_PID_Calculate(&Chassis_PID_v4,Chassis_Info->Target.D_velocity,Chassis_motor[D].Data.velocity);
	
}
