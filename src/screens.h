/*
 * File: screens.h
 * Author: dgrubb
 * Date: 24/09/2019
 */

#ifndef SCREENS_H_
#define SCREENS_H_

/* Platform includes */
#include <genesis.h>

/* Project includes */
#include "credits.h"
#include "playfield.h"
#include "title.h"

typedef enum {
    Screens_Title = 0,
    Screens_Playfield,
    Screens_Credits
} Screen_t;

void screens_set_screen(Screen_t screen, u16 force);
void screens_show_screen(Screen_t screen);
void screens_hide_screen(Screen_t screen);
void screens_controller_input(u16 controller_one_input, u16 controller_two_input);

#endif /* SCREENS_H_ */
