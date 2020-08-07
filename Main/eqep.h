/*
 *  eqep.h
 *  
 * COPYRIGHTS: Swaminath VENKATESWARAN, Damien CHABLAT, LS2N, Centrale Nantes, France
 * Date de création: 05/05/2020
 */

#ifndef _EQEP_H
#define _EQEP_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Le chemin des EQEP dans la BeagleBone */
#define EQEP0 "/sys/devices/platform/ocp/48300000.epwmss/48300180.eqep"
#define EQEP1 "/sys/devices/platform/ocp/48302000.epwmss/48302180.eqep"
#define EQEP2 "/sys/devices/platform/ocp/48304000.epwmss/48304180.eqep"

/* EQEP files */
#define POSITION "position"  
#define MODE "mode"
#define PERIOD "period"
#define ENABLED "enabled"

int get_eqep(const char * dev, const char * reg);
void set_eqep(const char * dev, const char * reg, int val);

#endif