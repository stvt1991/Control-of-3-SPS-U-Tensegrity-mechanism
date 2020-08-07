/*
 *  main.c
 *
 * COPYRIGHTS: Swaminath VENKATESWARAN, Damien CHABLAT, LS2N, Centrale Nantes, France
 * Date de création: 10/05/2020
 * Date de modification: 06/08/2020
 *
 */

#include <stdio.h>
#include "eqep.h"
#include "gpio.h"
#include "calc.h"
#include "servo.h"
#include "pwm.h"
#include "utils.h"
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <pthread.h>

struct_robot Robot;

void* fonction_cmd()
{
	/* Définition du Home-Pose */
	printf("Initialization sequence\n");
	servo_start();
	printf("Motors initialized, mechanism ready to Tilt\n");
	
	int trajet,Tf;
    printf("Trajectory selection: Enter 1 for Linear, Enter 2 for Circular\n");
    scanf("%d",&trajet);
    
    if(trajet==1)
    {
        printf("\n Linear trajectory chosen, start of operations \n");
    }
    else if (trajet==2)
    {
        printf("\n Circular trajectory chosen, start of operations \n");
    }    
    else
    {
        printf("\n Invalid choice: Exiting program, re-run the code \n");
        
    }
    
    if(trajet == 1 || trajet ==2)
    
    {
    
        switch(trajet)
        
        {
            
            case 1 :;
            
                float Tilt1[7][2] = {
            		{0.0,0.0},
            		{-0.364,0.212},
            		{0.0,0.0},
            		{0.0,-0.419},
            		{0.0,0.0},
            		{0.364,0.212},
            		{0.0,0.0}
	            };	
	           
	           /* 
	            float Tilt1[7][2] = {
            		{0.0,0.0},
            		{-0.364,-0.212},
            		{0.0,0.0},
            		{0.364,-0.212},
            		{0.0,0.0},
            		{0.0,0.419},
            		{0.0,0.0}
	            };
	            */
	            float k1[4];
            	for (int i=0;i<6;i++)
            	{
            		for(int j=0;j<2;j++)
            		{	k1[j] = Tilt1[i][j];
            			k1[j+2] = Tilt1[i+1][j];
            		}
            		Tf=17;
            		servo_run(k1,&Robot,trajet,Tf);
            	}
                
            break;
            
            
            case 2 :;
            
                float Tilt2[4][2] = {
            		{0.0,0.0},
            		{0.0,0.305},
            		{0.0,0.305},
            		{0.0,0.0}
	            };	
	            
	            float k2[4];
            	for (int i=0;i<3;i++)
            	{
            		for(int j=0;j<2;j++)
            		{	k2[j] = Tilt2[i][j];
            			k2[j+2] = Tilt2[i+1][j];
            		}
            		if(k2[0]-k2[2] != 0 || k2[1]-k2[3] != 0 )
            		{
            			Tf=17;
            		}
            		else if(k2[0]-k2[2] == 0 && k2[1]-k2[3] == 0 )
            		{
            			Tf=60;
            		}
            		servo_run(k2,&Robot,trajet,Tf);
            	}
                
            break;
        }
			
	FILE *fend;
    fend = fopen("end","w");
    fclose(fend);
    }    
}

void* fonction_log()
{
	struct timeval t_ref;
	float tt;
	time_t t = time(NULL);
	struct tm *info1;
	struct tm *info2;
	struct tm *info3;
	info1 = localtime( &t );
	info2 = localtime( &t );
	info3 = localtime( &t );
	long clk_tck = CLOCKS_PER_SEC;
	
	char buffer1[256],buffer2[256],buffer3[256];
	strftime(buffer1, sizeof(buffer1), "Motor-1.txt", info1);
	strftime(buffer2, sizeof(buffer2), "Motor-2.txt", info2);
	strftime(buffer3, sizeof(buffer3), "Motor-3.txt", info3);
	printf("Formatted fil log : |%s|\n", buffer1 );
	printf("Formatted fil log : |%s|\n", buffer2 );
	printf("Formatted fil log : |%s|\n", buffer3 );
	
	
	clock_t start_t, end_t, total_t;
	start_t = clock();
	
	FILE *fp1;
	FILE *fp2;
	FILE *fp3;
	fp1 = fopen("end", "r");
	fp2 = fopen("end", "r");
	fp3 = fopen("end", "r");
	
	FILE *flog1;
	FILE *flog2;
	FILE *flog3;
	flog1 = fopen(buffer1,"w");
	flog2 = fopen(buffer2,"w");
	flog3 = fopen(buffer3,"w");
	gettimeofday(&t_ref, NULL);
	while(fp1 == NULL)
	{
		fp1 = fopen("end", "r");
		fp2 = fopen("end", "r");
		fp3 = fopen("end", "r");
		end_t = clock();
		
		double total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
		//fprintf(flog,"%lf\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n",total_t,Robot.mes[0],Robot.des[0],Robot.error[0],Robot.sum[0],Robot.diff[0],Robot.mes[1],Robot.des[1],Robot.error[1],Robot.sum[1],Robot.diff[1],Robot.mes[2],Robot.des[2],Robot.error[2],Robot.sum[2],Robot.diff[2]); 
		fprintf(flog1,"%lf\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%d\n",total_t,Robot.mes_pos[0],Robot.des_pos[0],Robot.mes_vel[0],Robot.des_vel[0],Robot.mes_accl[0],Robot.des_accl[0],Robot.curr_new[0],Robot.curr_old[0],Robot.des_eta[0],Robot.des_phi[0],Robot.m1);
		fprintf(flog2,"%lf\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%d\n",total_t,Robot.mes_pos[1],Robot.des_pos[1],Robot.mes_vel[1],Robot.des_vel[1],Robot.mes_accl[1],Robot.des_accl[1],Robot.curr_new[1],Robot.curr_old[1],Robot.des_eta[1],Robot.des_phi[1],Robot.m2);
		fprintf(flog3,"%lf\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%d\n",total_t,Robot.mes_pos[2],Robot.des_pos[2],Robot.mes_vel[2],Robot.des_vel[2],Robot.mes_accl[2],Robot.des_accl[2],Robot.curr_new[2],Robot.curr_old[2],Robot.des_eta[2],Robot.des_phi[2],Robot.m3);
		
		while ( (tt+= elapsed_time_f(&t_ref))<SAMPLING_PERIOD);
		tt=0.0;
		usleep(1);
	}
	fclose(flog1);
	fclose(flog2);
	fclose(flog3);
	fclose (fp1);
	fclose (fp2);
	fclose (fp3);
}

int main (int argc, char ** argv)
{
	printf("debut du programme\n\n");
	remove("end");
	pthread_t thread_cmd;
	pthread_t thread_log;
	
	pthread_create(&thread_cmd , NULL , fonction_cmd ,NULL);
	pthread_create(&thread_log , NULL , fonction_log ,NULL);
	
	pthread_join(thread_cmd,NULL);
	pthread_join(thread_log,NULL);
	
	printf("\nfin programme\n");
	
	return 0;
}

