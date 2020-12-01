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
#include "screens.h"

typedef enum {
    TITLE_OPTION_INACTIVE = 0,
    TITLE_OPTION_ACTIVE,
    TITLE_OPTION_STATES
} states_t;

typedef enum {
    TITLE_OPTION_ONE_PLAYER = 0,
    TITLE_OPTION_TWO_PLAYER,
    TITLE_OPTION_CREDITS,
    TITLE_OPTION_COUNT
} option_t;

#define DEFAULT_OPTION TITLE_OPTION_ONE_PLAYER

typedef struct {
    option_t option;
    Sprite* res[TITLE_OPTION_STATES];
    s16 x;
    s16 y;
} option_info_t;

void title_screen_init();
Sprite* title_screen_init_sprite(const SpriteDefinition* sprite, option_t option, u16 palette);
void title_screen_show();
void title_screen_hide();
void title_set_option(option_t option);
void title_set_next_option();
void title_set_previous_option();
void title_set_palettes();
void title_refresh_options();
void title_controller_input(u16 controller, u16 button, u16 down);

#endif /* TITLE_H_ */
