/*
 * File: credits.h
 * Author: dgrubb
 * Date: 25/09/2019
 */

#ifndef CREDITS_H_
#define CREDITS_H_

/* Platform includes */
#include <genesis.h>

void credits_init();
void credits_screen_show();
void credits_screen_hide();
void credits_controller_input(u16 controller_one_state, u16 controller_two_state);

#endif /* CREDITS_H_ */
