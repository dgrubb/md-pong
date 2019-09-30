/*
 * File: title.h
 * Author: dgrubb
 * Date: 24/09/2019
 */

#ifndef TITLE_H_
#define TITLE_H_

/* Platform includes */
#include <genesis.h>

/* Project includes */
#include "assets.h"
#include "screens.h"

#define TITLE_OPTION_ONE_PLAYER 0
#define TITLE_OPTION_TWO_PLAYER 1
#define TITLE_OPTION_CREDITS    2
#define TITLE_OPTION_COUNT      3

void title_screen_init();
void title_screen_show();
void title_screen_hide();
void title_focus_element(u16 option, u16 focus);
void title_update_selection(u16 option);
void title_controller_input(u16 controller, u16 button, u16 down);

#endif /* TITLE_H_ */
