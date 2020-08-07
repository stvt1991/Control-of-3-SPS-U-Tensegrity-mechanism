/*
 *  servo.c
 *
 * COPYRIGHTS: Swaminath VENKATESWARAN, Damien CHABLAT, LS2N, Centrale Nantes, France
 * Date de création: 05/05/2020
 *
 *
 */

#include "servo.h"

void servo_start(void)
{
	printf("Motor status = START \n");
	printf("Initializing PWM, GPIO and EQEP's: IDLE States!!! \n");
	
	/* Motor 0 */
	set_pwm(PWM_MOT_0, PWM_PERIOD, PWM_MOT_PERIOD);
	set_pwm(PWM_MOT_0, PWM_DUTY, PWM_MOT_HALF_PERIOD);
	set_pwm(PWM_MOT_0, PWM_POLARITY, 0);
	set_gpio(UNLOCKING_MOT_0, DIRECTION, 1);
	set_gpio(UNLOCKING_MOT_0, VALUE, 0);
	set_eqep(ENCODER_MOT_0,POSITION,0);
	
	/* Motor 1 */
	set_pwm(PWM_MOT_1, PWM_PERIOD, PWM_MOT_PERIOD);
	set_pwm(PWM_MOT_1, PWM_DUTY, PWM_MOT_HALF_PERIOD);
	set_pwm(PWM_MOT_1, PWM_POLARITY, 0);
	set_gpio(UNLOCKING_MOT_1, DIRECTION, 1);
	set_gpio(UNLOCKING_MOT_1, VALUE, 0);
	set_eqep(ENCODER_MOT_1,POSITION,0);
	
	/* Motor 2 */
	set_pwm(PWM_MOT_2, PWM_PERIOD, PWM_MOT_PERIOD);
	set_pwm(PWM_MOT_2, PWM_DUTY, PWM_MOT_HALF_PERIOD);
	set_pwm(PWM_MOT_2, PWM_POLARITY, 0);
	set_gpio(UNLOCKING_MOT_2, DIRECTION, 1);
	set_gpio(UNLOCKING_MOT_2, VALUE, 0);
	set_eqep(ENCODER_MOT_2,POSITION,0);
	
}

void servo_run(float k[],struct_robot *Robot, int trajet, int Tf)
{
	float t;
	struct timeval t_ref;
	unsigned char axe; 
	
	float meas_pos[3] = {0.0,0.0,0.0};
	float sum_err_pos[3] = {0.0,0.0,0.0};
	float err_pos[3] = {0.0,0.0,0.0};
	float err_pos_old[3] = {0.0,0.0,0.0};
	float current[3] = {0.0,0.0,0.0};
	float current_old[3] = {0.0,0.0,0.0};
	float meas_pos_old[3] = {0.0,0.0,0.0};
	float meas_vel[3] = {0.0,0.0,0.0};
	float meas_vel_old[3] = {0.0,0.0,0.0};
	float meas_accl[3] = {0.0,0.0,0.0};
	float des_pos[3] = {0.0,0.0,0.0};
	float des_vel[3] = {0.0,0.0,0.0};
	float des_acc[3] = {0.0,0.0,0.0};
	float pos_eta[3] = {0.0,0.0,0.0};
	float pos_phi[3] = {0.0,0.0,0.0};
	
	float position_eta[(int) (Tf / SAMPLING_PERIOD)+1];
	float position_phi[(int) (Tf / SAMPLING_PERIOD)+1];
	float vitesse_eta[(int) (Tf / SAMPLING_PERIOD)+1];
	float vitesse_phi[(int) (Tf / SAMPLING_PERIOD)+1];
	float accel_eta[(int) (Tf / SAMPLING_PERIOD)+1];
	float accel_phi[(int) (Tf / SAMPLING_PERIOD)+1];
	float position_m1[(int) (Tf / SAMPLING_PERIOD)+1]; // trajectoire en 15 s
	float position_m2[(int) (Tf / SAMPLING_PERIOD)+1];
	float position_m3[(int) (Tf / SAMPLING_PERIOD)+1];
	float vitesse_m1[(int) (Tf / SAMPLING_PERIOD)+1]; // trajectoire en 15 s
	float vitesse_m2[(int) (Tf / SAMPLING_PERIOD)+1]; // trajectoire en 15 s
	float vitesse_m3[(int) (Tf / SAMPLING_PERIOD)+1]; // trajectoire en 15 s
	float accel_m1[(int) (Tf / SAMPLING_PERIOD)+1];
	float accel_m2[(int) (Tf / SAMPLING_PERIOD)+1];
	float accel_m3[(int) (Tf / SAMPLING_PERIOD)+1];
	int   h, pas;               // position dans le tableau des poistions en fonction du temps à 2KHz
	printf("Motors ready to RUN!!! \n");
	
	/* Moteur 0 */
	set_pwm(PWM_MOT_0, PWM_DUTY, PWM_MOT_HALF_PERIOD);
	set_pwm(PWM_MOT_0, PWM_RUN, 1);
	set_gpio(UNLOCKING_MOT_0, VALUE, 1);
	
	/* Moteur 1 */
	set_pwm(PWM_MOT_1, PWM_DUTY, PWM_MOT_HALF_PERIOD);
	set_pwm(PWM_MOT_1, PWM_RUN, 1);
	set_gpio(UNLOCKING_MOT_1, VALUE, 1);
	
	/* Moteur 2 */
	set_pwm(PWM_MOT_2, PWM_DUTY, PWM_MOT_HALF_PERIOD);
	set_pwm(PWM_MOT_2, PWM_RUN, 1);
	set_gpio(UNLOCKING_MOT_2, VALUE, 1);
	gettimeofday(&t_ref, NULL);
	
	t=0.0;
	float r1,r2,r3;
	float theta1,theta2,theta3; 
	float theta1d, theta2d, theta3d;
	float theta1dd, theta2dd, theta3dd;
	
	/* Définition des positions en fonction du temps */
	//double m = Tf/SAMPLING_PERIOD;
	
	/* Définition des positions en fonction du temps */

	double m = Tf/SAMPLING_PERIOD;
	
	for (h=0; h< (int) m ; h++)
	{
		/* La trajectoire degré 5 */
		r1 = 10*pow(h,3)*pow(m,-3)  - 15 *pow(h,4)*pow(m,-4)  + 6*pow(h,5)*pow(m,-5);
		r2 = 30*pow(h,2)*pow(m,-3) - 60 * pow(h,3)*pow(m,-4)  + 30*pow(h,4)*pow(m,-5);
		r3 = 60*h*pow(m,-3) - 180*pow(h,2)*pow(m,-4) + 120*pow(h,3)*pow(m,-5);
		if(trajet==1)
		{
			position_eta[h] = k[0] + (k[2]-k[0]) * r1;
			vitesse_eta[h] = (k[2]-k[0]) * r2;
			accel_eta[h] = (k[2]-k[0]) * r3;
	
			position_phi[h] = k[1] + (k[3]-k[1]) * r1;
			vitesse_phi[h] = (k[3]-k[1]) * r2;
			accel_phi[h] = (k[3]-k[1]) * r3;
	
			values(position_eta[h], vitesse_eta[h], accel_eta[h], position_phi[h],vitesse_phi[h], accel_phi[h], &theta1, &theta2, &theta3, &theta1d, &theta2d, &theta3d, &theta1dd, &theta2dd, &theta3dd);
	
			position_m1[h] = theta1;
			vitesse_m1[h] = theta1d;
	
			position_m2[h]= theta2;
			vitesse_m2[h] = theta2d;
	
			position_m3[h]= theta3; 
			vitesse_m3[h] = theta3d;
		}
		else if(trajet ==2)
		{
			if(k[0]-k[2] != 0 || k[1]-k[3] != 0 )
			{
			
				position_eta[h] = k[0] + (k[2]-k[0]) * r1;
				vitesse_eta[h] = (k[2]-k[0]) * r2;
				accel_eta[h] = (k[2]-k[0]) * r3;
		
				position_phi[h] = k[1] + (k[3]-k[1]) * r1;
				vitesse_phi[h] = (k[3]-k[1]) * r2;
				accel_phi[h] = (k[3]-k[1]) * r3;
		
				values(position_eta[h], vitesse_eta[h], accel_eta[h], position_phi[h],vitesse_phi[h], accel_phi[h], &theta1, &theta2, &theta3, &theta1d, &theta2d, &theta3d, &theta1dd, &theta2dd, &theta3dd);
		
				position_m1[h] = theta1;
				vitesse_m1[h] = theta1d;
		
				position_m2[h]= theta2;
				vitesse_m2[h] = theta2d;
		
				position_m3[h]= theta3; 
				vitesse_m3[h] = theta3d;
			}
			
			else if (k[0]-k[2] == 0 && k[1]-k[3] == 0)
			{	
				float nmin = 0;
				float nmax = -2*M_PI;
				position_eta[h] = CIRCRAD*sin(nmin+ (nmax-nmin)*r1);	
				vitesse_eta[h] = CIRCRAD*(nmax-nmin)*r2*cos(nmin + (nmax-nmin)*r1);
				accel_eta[h] = CIRCRAD * (nmax - nmin) * (0.120e3 * pow(h, 0.3e1) * pow(m, -0.5e1) - 0.300e3 * pow(h, 0.4e1) * pow(m, -0.6e1) + 0.180e3 * pow(h, 0.5e1) * pow(m, -0.7e1)) * cos(nmin + (nmax - nmin) * (0.10e2 * pow(h, 0.3e1) * pow(m, -0.3e1) - 0.15e2 * pow(h, 0.4e1) * pow(m, -0.4e1) + 0.6e1 * pow(h, 0.5e1) * pow(m, -0.5e1))) - CIRCRAD * pow(nmax - nmin, 0.2e1) * pow(-0.30e2 * pow(h, 0.3e1) * pow(m, -0.4e1) + 0.60e2 * pow(h, 0.4e1) * pow(m, -0.5e1) - 0.30e2 * pow(h, 0.5e1) * pow(m, -0.6e1), 0.2e1) * sin(nmin + (nmax - nmin) * (0.10e2 * pow(h, 0.3e1) * pow(m, -0.3e1) - 0.15e2 * pow(h, 0.4e1) * pow(m, -0.4e1) + 0.6e1 * pow(h, 0.5e1) * pow(m, -0.5e1)));
				position_phi[h] = CIRCRAD*cos(nmin+ (nmax-nmin)*r1);	
				vitesse_phi[h] = -CIRCRAD*(nmax-nmin)*r2*sin(nmin + (nmax-nmin)*r1);
				accel_phi[h] = -CIRCRAD * (nmax - nmin) * (0.120e3 * pow(h, 0.3e1) * pow(m, -0.5e1) - 0.300e3 * pow(h, 0.4e1) * pow(m, -0.6e1) + 0.180e3 * pow(h, 0.5e1) * pow(m, -0.7e1)) * sin(nmin + (nmax - nmin) * (0.10e2 * pow(h, 0.3e1) * pow(m, -0.3e1) - 0.15e2 * pow(h, 0.4e1) * pow(m, -0.4e1) + 0.6e1 * pow(h, 0.5e1) * pow(m, -0.5e1))) - CIRCRAD * pow(nmax - nmin, 0.2e1) * pow(-0.30e2 * pow(h, 0.3e1) * pow(m, -0.4e1) + 0.60e2 * pow(h, 0.4e1) * pow(m, -0.5e1) - 0.30e2 * pow(h, 0.5e1) * pow(m, -0.6e1), 0.2e1) * cos(nmin + (nmax - nmin) * (0.10e2 * pow(h, 0.3e1) * pow(m, -0.3e1) - 0.15e2 * pow(h, 0.4e1) * pow(m, -0.4e1) + 0.6e1 * pow(h, 0.5e1) * pow(m, -0.5e1)));
				
				values(position_eta[h], vitesse_eta[h], accel_eta[h], position_phi[h],vitesse_phi[h], accel_phi[h], &theta1, &theta2, &theta3, &theta1d, &theta2d, &theta3d, &theta1dd, &theta2dd, &theta3dd);
		
				position_m1[h] = theta1;
				vitesse_m1[h] = theta1d;
		
				position_m2[h]= theta2;
				vitesse_m2[h] = theta2d;
		
				position_m3[h]= theta3; 
				vitesse_m3[h] = theta3d;
			}
			
		}
		//printf("%f,%f\n",position_eta[h],position_phi[h]); // Pour tester ll'equation polynomiale, supprimer les commentaires
		//printf("%f,%f,%f,%f,%f,%f\n",position_m1[h],position_m2[h],position_m3[h],vitesse_m1[h],vitesse_m2[h],vitesse_m3[h]);
		
	}
	
	for (h=0; h< (int) m ; h++)
	{	
		r3 = 60*h*pow(m,-3) - 180*pow(h,2)*pow(m,-4) + 120*pow(h,3)*pow(m,-5);
		accel_m1[h] = (position_m1[(int) m]-position_m1[0])*r3;
		accel_m2[h] = (position_m2[(int) m]-position_m2[0])*r3;
		accel_m3[h] = (position_m3[(int) m]-position_m3[0])*r3;
	
	}

	/* Le PID (servo) */

	for (pas=0;pas < (int) Tf / SAMPLING_PERIOD; pas++)
	{
		
		meas_pos[0] = get_eqep(ENCODER_MOT_0, POSITION) * ENCODER_INC_TO_AXE_ANGLE;
		meas_pos[1] = get_eqep(ENCODER_MOT_1, POSITION) * ENCODER_INC_TO_AXE_ANGLE;
		meas_pos[2] = get_eqep(ENCODER_MOT_2, POSITION) * ENCODER_INC_TO_AXE_ANGLE;
		des_pos[0] = position_m1[pas];
		des_pos[1] = position_m2[pas];
		des_pos[2] = position_m3[pas];
		pos_eta[0] = position_eta[pas];
		pos_eta[1] = position_eta[pas];
		pos_eta[2] = position_eta[pas];
		pos_phi[0] = position_phi[pas];
		pos_phi[1] = position_phi[pas];
		pos_phi[2] = position_phi[pas];

		
		des_vel[0] = vitesse_m1[pas];
		des_vel[1] = vitesse_m2[pas];
		des_vel[2] = vitesse_m3[pas];
		des_acc[0] = accel_m1[pas];
		des_acc[1] = accel_m2[pas];
		des_acc[2] = accel_m3[pas];
		
		for(axe=0;axe<3;axe++)
		{

			err_pos[axe] = des_pos[axe] - meas_pos[axe];
			sum_err_pos[axe] += err_pos[axe] * SAMPLING_PERIOD;		
			meas_vel[axe] = (meas_pos[axe] - meas_pos_old[axe])/SAMPLING_PERIOD;
			meas_accl[axe] = (meas_vel[axe] - meas_vel_old[axe])/SAMPLING_PERIOD;
			meas_pos_old[axe] = meas_pos[axe];
			meas_vel_old[axe] = meas_vel[axe];
			
			/* On règle le courant */ 
			
			current[axe]=-PID_KA_CURRENT*des_acc[axe] 
						-PID_KP_CURRENT*err_pos[axe]
						-PID_KV_CURRENT*(des_vel[axe]-meas_vel[axe])
						-PID_KI_CURRENT*sum_err_pos[axe];
			current_old[axe]= current[axe];
			if (current[axe]>SAT_CURRENT_MAX)
			{
				current[axe] = SAT_CURRENT_MAX;
				(*Robot).des_eta[axe] = pos_eta[axe];
				(*Robot).des_phi[axe] = pos_phi[axe];
				(*Robot).mes_pos[axe] = meas_pos[axe];
				(*Robot).des_pos[axe] = des_pos[axe];
				(*Robot).mes_vel[axe] = meas_vel[axe];
				(*Robot).des_vel[axe] = des_vel[axe];
				(*Robot).mes_accl[axe] = meas_accl[axe];
				(*Robot).des_accl[axe] = des_acc[axe];
				(*Robot).curr_new[axe] = current[axe];
				(*Robot).curr_old[axe] = current_old[axe];
			}
			else if (current[axe]< SAT_CURRENT_MIN)
			{
				current[axe] = SAT_CURRENT_MIN;
				(*Robot).des_eta[axe] = pos_eta[axe];
				(*Robot).des_phi[axe] = pos_phi[axe];
				(*Robot).mes_pos[axe] = meas_pos[axe];
				(*Robot).des_pos[axe] = des_pos[axe];
				(*Robot).mes_vel[axe] = meas_vel[axe];
				(*Robot).des_vel[axe] = des_vel[axe];
				(*Robot).mes_accl[axe] = meas_accl[axe];
				(*Robot).des_accl[axe] = des_acc[axe];
				(*Robot).curr_new[axe] = current[axe];
				(*Robot).curr_old[axe] = current_old[axe];
			}
		}
		set_pwm(PWM_MOT_0, PWM_DUTY, (int)(current[0]*PWM_CURRENT_TO_PWM_DUTY + PWM_MOT_HALF_PERIOD));
		if((int)(current[0]*PWM_CURRENT_TO_PWM_DUTY + PWM_MOT_HALF_PERIOD) > PWM_MOT_HALF_PERIOD)
		{
			(*Robot).m1 = -1;
		}
		else if((int)(current[0]*PWM_CURRENT_TO_PWM_DUTY + PWM_MOT_HALF_PERIOD) < PWM_MOT_HALF_PERIOD)
		{
			(*Robot).m1 = 1;
		}
		set_pwm(PWM_MOT_1, PWM_DUTY, (int)(current[1]*PWM_CURRENT_TO_PWM_DUTY + PWM_MOT_HALF_PERIOD));
		if((int)(current[1]*PWM_CURRENT_TO_PWM_DUTY + PWM_MOT_HALF_PERIOD) > PWM_MOT_HALF_PERIOD)
		{
			(*Robot).m2 = -1;
		}
		else if((int)(current[1]*PWM_CURRENT_TO_PWM_DUTY + PWM_MOT_HALF_PERIOD) < PWM_MOT_HALF_PERIOD)
		{
			(*Robot).m2 = 1;
		}
		set_pwm(PWM_MOT_2, PWM_DUTY, (int)(current[2]*PWM_CURRENT_TO_PWM_DUTY + PWM_MOT_HALF_PERIOD));
		if((int)(current[2]*PWM_CURRENT_TO_PWM_DUTY + PWM_MOT_HALF_PERIOD) > PWM_MOT_HALF_PERIOD)
		{
			(*Robot).m3 = -1;
		}
		else if((int)(current[2]*PWM_CURRENT_TO_PWM_DUTY + PWM_MOT_HALF_PERIOD) < PWM_MOT_HALF_PERIOD)
		{
			(*Robot).m3 = 1;
		}
		while ( (t+= elapsed_time_f(&t_ref))<SAMPLING_PERIOD);
		t=0.0;
	}
	current[0]=0.0;
	current[1]=0.0;
	current[2]=0.0;
	meas_vel[0]=0.0;
	meas_vel[1]=0.0;
	meas_vel[2]=0.0;
	meas_accl[0]=0.0;
	meas_accl[1]=0.0;
	meas_accl[2]=0.0;
	set_pwm(PWM_MOT_0, PWM_DUTY, PWM_MOT_HALF_PERIOD);
	(*Robot).m1 = 0;
	set_gpio(UNLOCKING_MOT_0, VALUE, 0);
	set_pwm(PWM_MOT_1, PWM_DUTY, PWM_MOT_HALF_PERIOD);
	(*Robot).m2 = 0;
	set_gpio(UNLOCKING_MOT_1, VALUE, 0);
	set_pwm(PWM_MOT_2, PWM_DUTY, PWM_MOT_HALF_PERIOD);
	(*Robot).m3 = 0;
	set_gpio(UNLOCKING_MOT_2, VALUE, 0);
	
	sleep(5);
}





