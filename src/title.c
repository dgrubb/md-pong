/*
 * File: title.c
 * Author: dgrubb
 * Date: 24/09/2019
 */

/* Project includes */
#include "title.h"

/* TODO: move into assets */

u16 current_option = TITLE_OPTION_ONE_PLAYER;

void
title_screen_init()
{
}

void
title_screen_show()
{
    VDP_resetScreen();
    VDP_drawImage(BG_B, &title_background, 0, 0);
}

void
title_screen_hide()
{
}

void
title_controller_input(u16 controller, u16 button, u16 down)
{
    u16 new_option;

    /* This screen only needs to respond to singular button down presses */
    if (FALSE == down) return;

    if ((button & BUTTON_START) || (button & BUTTON_A) || (button & BUTTON_B) || (button & BUTTON_C)) {
    }

    /* User is not selecting an option, instead they're navigating */
    if (button & BUTTON_DOWN) {
    }
    if (button & BUTTON_UP) {
    }

}
