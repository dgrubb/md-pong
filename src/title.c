/*
 * File: title.c
 * Author: dgrubb
 * Date: 24/09/2019
 */

/* Project includes */
#include "title.h"

u16 current_selection = TITLE_OPTION_ONE_PLAYER;

void
title_screen_init()
{
}

void
title_screen_show()
{
    assets_set_visible(ASSET_BACKGROUND_TITLE, TRUE);
    VDP_drawTextBG(PLAN_B, "Pong", 16, 1);
}

void
title_screen_hide()
{
    assets_set_visible(ASSET_BACKGROUND_TITLE, FALSE);
}

void
title_focus_element(u16 option, u16 focus)
{
    if (focus) {
        /* TODO: draw appropriate sprites */
    } else {
        /* TODO: draw appropriate sprites */
    }
}

void
title_update_selection(u16 option)
{
    title_focus_element(current_option, FALSE)
    current_option = option;
    title_focus_element(current_option, TRUE)
}

void
title_controller_input(u16 controller, u16 button, u16 state)
{
    u16 new_option;
    if ((button | BUTTON_START) || (button | BUTTON_A) || (button | BUTTON_B) || (button | BUTTON_C)) {
        /* Use is selecting an option */
        /* TODO: set new screen */
        switch (current_option) {
            case TITLE_OPTION_ONE_PLAYER:
                /* Intentional fall-through */
            case TITLE_OPTION_ONE_PLAYER:
                screens_set_screen(Playfield, FALSE);
                return;
            case TITLE_OPTION_CREDITS:
                screens_set_screen(Credits, FALSE);
                return;
            default: break;
        }
    }

    

    title_update_selection(new_option);
}
