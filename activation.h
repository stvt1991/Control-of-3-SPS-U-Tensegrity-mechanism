  
#ifndef _ACTIVATION_H
#define _ACTIVATION_H


#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ACTIV_CAPEMGR "/sys/devices/bone_capemgr.9"

//Define PWM
#define ACTIV_PWM0 "/sys/devices/platform/ocp/48300000.epwmss/48300200.pwm/pwm/pwmchip1/export"
#define ACTIV_PWM1 "/sys/devices/platform/ocp/48302000.epwmss/48302200.pwm/pwm/pwmchip4/export"
#define ACTIV_PWM2 "/sys/devices/platform/ocp/48304000.epwmss/48304200.pwm/pwm/pwmchip7/export"

#define STATE_PWM0 "/sys/devices/platform/ocp/ocp:P9_31_pinmux/state"
#define STATE_PWM1 "/sys/devices/platform/ocp/ocp:P9_14_pinmux/state"
#define STATE_PWM2 "/sys/devices/platform/ocp/ocp:P8_13_pinmux/state"

#define STATE_EQEP0A "/sys/devices/platform/ocp/ocp:P9_92_pinmux/state"
#define STATE_EQEP0B "/sys/devices/platform/ocp/ocp:P9_27_pinmux/state"
#define STATE_EQEP1A "/sys/devices/platform/ocp/ocp:P8_35_pinmux/state"
#define STATE_EQEP1B "/sys/devices/platform/ocp/ocp:P8_33_pinmux/state"
#define STATE_EQEP2A "/sys/devices/platform/ocp/ocp:P8_12_pinmux/state"
#define STATE_EQEP2B "/sys/devices/platform/ocp/ocp:P8_11_pinmux/state"

#define CONFIG_PWM0A "/sys/devices/platform/ocp/48300000.epwmss/48300200.pwm/pwm/pwmchip1/pwm-1:0"
#define CONFIG_PWM1A "/sys/devices/platform/ocp/48302000.epwmss/48302200.pwm/pwm/pwmchip4/pwm-4:0"
#define CONFIG_PWM2B "/sys/devices/platform/ocp/48304000.epwmss/48304200.pwm/pwm/pwmchip7/pwm-7:1"

#define PWM_PERIOD "period"
#define PWM_DUTY "duty_cycle"
#define PWM_STATUS "enable"

//Define GPIO
#define ACTIV_GPIO "/sys/class/gpio/export"

void active_pwm(const char * dev, unsigned int val);
void set_gpio(const char * dev1, unsigned int val1);
void set_pwm(const char *dev2, const char * reg2);
void set_activ(const char * dev3, const char * reg3, const char * val3);
void set_eqep(const char *dev4, const char * reg4);
char *get_info1(const char * file_name);
int get_pwm(const char * dev6, const char * reg6);

#endif // ACTIVATION_H_INCLUDED