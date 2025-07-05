
#include "pid.h"




//float PID_Update(PIDController *pid)
//{
//    float error = pid->Ref - pid->Fbk;
//	
//    pid->integral += error * pid->sample_time;
//	
//	
//    float derivative = (error - pid->prev_error)  / pid->sample_time;
//    pid->prev_error = error;


//	float output = pid->Kp * ( error + pid->Ki * pid->integral + pid->Kd * derivative );

//	if(output > 100) 			 output =  100;
//	else if(output < -100) output = -100;
//	
//    return output;
//}


// 將原本 float 形式的 PID 控制邏輯，整合 TI MACRO 架構進入你現有的 PID 控制器程式碼中（不使用 IQ 格式）

#include <math.h>



// PID 宏（改寫成浮點數邏輯）
float PID_Update(PIDController *v)
{
    v->data.up = v->param.Kr * (v->term.Ref - v->term.Fbk);
                                                                                      
    v->data.ui = v->param.Ki * (v->data.w1 * v->data.up) + v->data.i1;                    
    v->data.i1 = v->data.ui;                                                            
                                                                                      
    v->data.d2 = v->param.Kd * (v->data.up - v->data.d1);                                
    v->data.ud = v->term.c2 * v->data.ud + v->term.c1 * v->data.d2;                        
    v->data.d1 = v->data.up;                                                            
                                                                                      
    v->data.v1 = v->param.Kp * (v->data.up + v->data.ui + v->data.ud);                     
    v->term.Out = fminf(fmaxf(v->data.v1, v->param.Umin), v->param.Umax);                 
    v->data.w1 = (v->term.Out == v->data.v1) ? 1 : 0;
	
	return v->term.Out;
}

