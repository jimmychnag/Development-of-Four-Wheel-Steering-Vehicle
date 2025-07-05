#ifndef __PID_H
#define __PID_H


// 定義 PID 控制器結構（浮點版）
typedef struct {
    struct {
        float up, ui, ud, v1;     // 比例、積分、微分、總和輸出
        float d1, d2;             // 微分記憶
        float i1;                 // 積分記憶
        float w1;                // anti-windup 開關
    } data;

    struct {
        float Ref;
        float Fbk;
        float Out;
        float c1, c2;             // 微分濾波器係數
    } term;

    struct {
        float Kp, Ki, Kd;         // PID 參數
        float Kr;                // 前饋增益（預設為 1）
        float Umax, Umin;        // 輸出限制
    } param;
} PIDController;

float PID_Update(PIDController *v);



#endif
