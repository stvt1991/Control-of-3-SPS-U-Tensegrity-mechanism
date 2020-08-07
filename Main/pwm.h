/*
 *  pwm.h
 *  
 *
 * COPYRIGHTS: Swaminath VENKATESWARAN, Damien CHABLAT, LS2N, Centrale Nantes, France
 * Date de création: 05/05/2020
 *
 */

#ifndef _PWM_H
#define _PWM_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Device */ 
//Le chemin des PWM dans la BBB: 
#define EHRPWM0A "/sys/devices/platform/ocp/48300000.epwmss/48300200.pwm/pwm/pwmchip1/pwm-1:0/"
#define EHRPWM1A "/sys/devices/platform/ocp/48302000.epwmss/48302200.pwm/pwm/pwmchip4/pwm-4:0/"
#define EHRPWM2B "/sys/devices/platform/ocp/48304000.epwmss/48304200.pwm/pwm/pwmchip7/pwm-7:1/"

/* Registers */
#define PWM_DUTY "duty_cycle"
#define PWM_PERIOD "period"
#define PWM_POLARITY "polarity"
#define PWM_POWER "power"
#define PWM_RUN "enable"

void set_pwm(const char * dev, const char * reg, unsigned int val);
int get_pwm(const char * dev, const char * reg);

#endif

