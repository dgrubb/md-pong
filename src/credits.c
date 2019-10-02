/*
 * File: credits.c
 * Author: dgrubb
 * Date: 25/09/2019
 */

/* Platform includes */
#include "credits.h"

void
credits_init()
{
}

void
credits_screen_show()
{
    VDP_drawTextBG(PLAN_B, "By dgrubb", 15, 37);
    VDP_drawTextBG(PLAN_B, "With special thanks", 10, 40);
    VDP_drawTextBG(PLAN_B, "to Retro Game Squad", 10, 41);
    VDP_drawTextBG(PLAN_B, "and Discord members:", 10, 42);
    VDP_drawTextBG(PLAN_B, "@inkypinkyandclyde and @RGSJon", 5, 45);
}

void
credits_screen_hide()
{
    VDP_clearPlan(PLAN_B, TRUE);
}

void
credits_controller_input(u16 controller, u16 button, u16 state)
{
    /* This screen only needs to respond to singular button down presses */
    if (FALSE == state) return;

    if ((button & BUTTON_START) || (button & BUTTON_A) || (button & BUTTON_B) || (button & BUTTON_C)) {
        screens_set_screen(Screens_Title, FALSE);
    }
}
