#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "activation.h"

int main ()
{
    //Activation PWM
    
	active_pwm(ACTIV_PWM0,0);
	active_pwm(ACTIV_PWM1,0);
	active_pwm(ACTIV_PWM2,1);
	
	set_pwm(STATE_PWM0,"pwm");
	set_pwm(STATE_PWM1,"pwm");
	set_pwm(STATE_PWM2,"pwm");
	
	//Activation EQEP
	
	set_eqep(STATE_EQEP0A,"qep");
	set_eqep(STATE_EQEP0B,"qep");
	set_eqep(STATE_EQEP1A,"qep");
	set_eqep(STATE_EQEP1B,"qep");
	set_eqep(STATE_EQEP2A,"qep");
	set_eqep(STATE_EQEP2B,"qep");
	
	const char* pwm0a  = get_info1(STATE_PWM0);
	const char* pwm1a  = get_info1(STATE_PWM0);
	const char* pwm2b  = get_info1(STATE_PWM0);
	
	set_activ(CONFIG_PWM0A,PWM_PERIOD,"500000");
	set_activ(CONFIG_PWM0A,PWM_DUTY,"250000");
	set_activ(CONFIG_PWM0A,PWM_STATUS,"1");
	
	set_activ(CONFIG_PWM1A,PWM_PERIOD,"500000");
	set_activ(CONFIG_PWM1A,PWM_DUTY,"250000");
	set_activ(CONFIG_PWM1A,PWM_STATUS,"1");
		
	set_activ(CONFIG_PWM2B,PWM_PERIOD,"500000");
	set_activ(CONFIG_PWM2B,PWM_DUTY,"250000");
	set_activ(CONFIG_PWM2B,PWM_STATUS,"1");


	int duty0a   = get_pwm(CONFIG_PWM0A,PWM_DUTY);
	int period0a = get_pwm(CONFIG_PWM0A,PWM_PERIOD);
	int enable0a = get_pwm(CONFIG_PWM0A,PWM_STATUS);
	
	int duty1a   = get_pwm(CONFIG_PWM1A,PWM_DUTY);
	int period1a = get_pwm(CONFIG_PWM1A,PWM_PERIOD);
	int enable1a = get_pwm(CONFIG_PWM1A,PWM_STATUS);
	
	int duty2b   = get_pwm(CONFIG_PWM2B,PWM_DUTY);
	int period2b = get_pwm(CONFIG_PWM2B,PWM_PERIOD);
	int enable2b = get_pwm(CONFIG_PWM2B,PWM_STATUS);
	
	printf("The status of PWM pins and EQEP's are as follows:\n");
	printf("PWM0A (P9.31) , State: %s , Duty cycle: %d , Period: %d , Enable: %d\n" ,pwm0a,duty0a,period0a,enable0a);
	printf("PWM1A (P9.14) , State: %s , Duty cycle: %d , Period: %d , Enable: %d\n" ,pwm1a,duty1a,period1a,enable1a);
	printf("PWM2B (P8.13) , State: %s , Duty cycle: %d , Period: %d , Enable: %d\n" ,pwm2b,duty2b,period2b,enable2b);

	
	const char* eqep0a  = get_info1(STATE_EQEP0A);
	const char* eqep0b  = get_info1(STATE_EQEP0B);
	const char* eqep1a  = get_info1(STATE_EQEP1A);
	const char* eqep1b  = get_info1(STATE_EQEP1B);
	const char* eqep2a  = get_info1(STATE_EQEP2A);
	const char* eqep2b  = get_info1(STATE_EQEP2B);

	printf("State of EQEP0A (P9.92) is: %s\n",eqep0a);
	printf("State of EQEP0B (P9.27) is: %s\n",eqep0b);
	printf("State of EQEP1A (P8.35) is: %s\n",eqep1a);
	printf("State of EQEP1B (P8.33) is: %s\n",eqep1b);
	printf("State of EQEP2A (P8.12) is: %s\n",eqep2a);
    printf("State of EQEP2B (P8.11) is: %s\n",eqep2a);


    //Activation GPIO
/*
    set_gpio(ACTIV_GPIO,60);
    set_gpio(ACTIV_GPIO,46);
    set_gpio(ACTIV_GPIO,117);
*/
    return 0;
}
