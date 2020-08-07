/*
 *  calc.h
 *  
 *
 * COPYRIGHTS: Swaminath VENKATESWARAN, Damien CHABLAT, LS2N, Centrale Nantes, France
 * Date de création: 03/07/2020
 * Date de modification: 06/08/2020
 */
 
#ifndef _CALC_H
#define _CALC_H

#include <math.h>
#include <stdlib.h>

#define PULLEY_RAD 20 // Il faut modifier cette valeur si on change le diamètre de la poulie

// Les valeurs qui correspondent au prototype de tenségrité
#define HOME 68.096
#define rf 56.7
#define H 0.6

void values(float eta_c, float etad_c, float etadd_c, float phi_c, float phid_c, float phidd_c, float *theta1, float *theta2, float *theta3, float *theta1d, float *theta2d, float *theta3d, float *theta1dd, float *theta2dd, float *theta3dd);

#endif