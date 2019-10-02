/*
 * File: playfield.h
 * Author: dgrubb
 * Date: 24/09/2019
 */

#ifndef PLAYFIELD_H_
#define PLAYFIELD_H_

/* Platform includes */
#include <genesis.h>

/* Project includes */
#include "assets.h"

#define PLAYFIELD_PLAYERS 2

typedef struct {
    s16 x;
    s16 y;
    s16 velocity;
} playfield_elem_state_t;

void playfield_init();
void playfield_screen_show();
void playfield_screen_hide();
void playfield_update();
void playfield_controller_input(u16 controller, u16 button, u16 state);
void playfield_reset_elements();
void playfield_update_player(u16 player);

#endif /* PLAYFIELD_H_ */
