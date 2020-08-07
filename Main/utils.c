/*
 *  utils.c
 *  
 * COPYRIGHTS: Swaminath VENKATESWARAN, Damien CHABLAT, LS2N, Centrale Nantes, France
 * Date de création: 05/05/2020
 */

#include "utils.h"

double time_d(void)
{
	static struct timeval t1;
	
	gettimeofday(&t1, NULL);
	
	return (t1.tv_sec + t1.tv_usec * 1e-6);
}

float elapsed_time_f(struct timeval * t_ref)
{
	static struct timeval t_act, dt;
	
	gettimeofday(&t_act, NULL);
	if((dt.tv_sec = t_act.tv_sec - t_ref->tv_sec)<0) dt.tv_sec += 2147483647;
	dt.tv_usec = t_act.tv_usec - t_ref->tv_usec;
	t_ref->tv_sec = t_act.tv_sec;
	t_ref->tv_usec = t_act.tv_usec;
	return ( dt.tv_sec + (dt.tv_usec * 1e-6));
}

