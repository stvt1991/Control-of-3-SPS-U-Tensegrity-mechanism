/*
 *  gpio.h
 *  
 * COPYRIGHTS: Swaminath VENKATESWARAN, Damien CHABLAT, LS2N, Centrale Nantes, France
 * Date de création: 05/05/2020
 *
 */

#ifndef _GPIO_H
#define _GPIO_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* Le chemin des GPIO dans la BBB  */
#define GPIO_47 "/sys/class/gpio/gpio47/"
#define GPIO_117 "/sys/class/gpio/gpio117/"
#define GPIO_31 "/sys/class/gpio/gpio31/"


/* Registers */
#define ACTIVE_LOW "active_low"
#define DIRECTION "direction"
#define EDGE "edge"
#define VALUE "value"
#define GPIO_IN "in"
#define GPIO_OUT "out"

void set_gpio(const char * dev, const char * reg, int val);
int get_gpio(const char * dev, const char * reg);

#endif
