/*
 *  servo.h
 *  
 *
 * COPYRIGHTS: Swaminath VENKATESWARAN, Damien CHABLAT, LS2N, Centrale Nantes, France
 * Date de création: 05/05/2020
 *
 */

#ifndef _SERVO_H
#define _SERVO_H

#include "eqep.h"
#include "calc.h"
#include "gpio.h"
#include "pwm.h"
#include "utils.h"
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

typedef struct struct_robot struct_robot;
struct struct_robot {
	float des_eta[3];
	float des_phi[3];
	float mes_pos[3];
	float des_pos[3];
	float mes_vel[3];
	float des_vel[3];
	float mes_accl[3];
	float des_accl[3];
	float curr_new[3];
	float curr_old[3];
	int m1;
	int m2;
	int m3;
};

/* Controlleur */

#define SAMPLING_PERIOD 0.001


#define MOT_KT 0.0348 // N.m/A
#define MOT_KT_INV 28.73 // A/(N.m)
#define MOT_KE 0.034 
#define MOT_PULSE 14.5// OMEGA = (Kt*Ke*2*Pi)/(R*Jm*60) rad/s
#define INERTIE 4.1e-8 //Inertie 
#define PID_KP  3.0*MOT_PULSE*MOT_PULSE   //12.0
#define PID_KV  3.0*MOT_PULSE  //1.0
#define PID_KI  MOT_PULSE*MOT_PULSE*MOT_PULSE  //6.0


#define PID_KP_CURRENT  PID_KP*MOT_KT_INV/1621 // 1621: Rapport de réduction
#define PID_KV_CURRENT  PID_KV*MOT_KT_INV/1621
#define PID_KI_CURRENT  PID_KI*MOT_KT_INV/1621
#define PID_KA_CURRENT  MOT_KT_INV*INERTIE/1621

/* Saturation */
#define SAT_CURRENT_MAX 0.177
#define SAT_CURRENT_MIN -0.177


/* Codeur */
#define	ENCODER_RESOLUTION 500
#define	GEAR_RATIO 1621
#define	ENCODER_INC_TO_AXE_ANGLE (1.937e-6) // M_PI / (2.0 * ENCODER_RESOLUTION * GEAR_RATIO)

#define ENCODER_MOT_0 EQEP0
#define ENCODER_MOT_1 EQEP1
#define ENCODER_MOT_2 EQEP2

/* PWM */
#define PWM_MOT_PERIOD 500000
#define PWM_MOT_HALF_PERIOD 250000 // PWM_PERIOD/2
#define PWM_MOT_0 EHRPWM1A
#define PWM_MOT_1 EHRPWM2B
#define PWM_MOT_2 EHRPWM0A
#define PWM_CURRENT_TO_PWM_DUTY  1129943     // 0.4 * PWM_PERIOD/SAT_CURRENT


/*Déblocage moteur */
#define UNLOCKING_MOT_0 GPIO_31
#define UNLOCKING_MOT_1	GPIO_47
#define UNLOCKING_MOT_2	GPIO_117

#define RAD_TO_DEG 5.729578e1
#define DEG_TO_RAD 1.7453e-2
#define M_PI 3.14159265358979323846
#define CIRCRAD 0.305


void servo_start(void);
void servo_run(float k[],struct_robot *Robot, int trajet, int Tf);


#endif