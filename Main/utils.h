/*
 *  utils.h
 *  
 * COPYRIGHTS: Swaminath VENKATESWARAN, Damien CHABLAT, LS2N, Centrale Nantes, France
 * Date de création: 05/05/2020
 *
 */

#ifndef _UTILS_H
#define _UTILS_H

#include <time.h>
#include <sys/time.h>
#include <math.h>
#include "servo.h"

double time_d(void);
float elapsed_time_f(struct timeval * t_ref);

#endif
