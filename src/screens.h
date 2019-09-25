/*
 * File: screens.h
 * Author: dgrubb
 * Date: 24/09/2019
 */

#ifndef SCREENS_H_
#define SCREENS_H

typedef enum {
    Title = 0,
    Playfield,
} Screen_t;

Screen_t current_screen;

void screens_set_screen(Screen_t screen, u16 force);
void screens_show_screen(Screen_t screen);
void screens_hide_screen(Screen_t screen);

#endif /* SCREENS_H_ */
