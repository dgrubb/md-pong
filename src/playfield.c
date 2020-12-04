/*
 * File: playfield.c
 * Author: dgrubb
 * Date: 24/09/2019
 */

/* Project includes */
#include "playfield.h"

void
playfield_init()
{
}

void
playfield_screen_show()
{
    VDP_clearPlane(BG_B, TRUE);
    VDP_setPalette(PAL0, center_line.palette->data);
    VDP_drawImageEx(BG_B, &center_line, 0, 19, 0, PAL0, TRUE);
}

void
playfield_screen_hide()
{
}

void
playfield_controller_input(u16 controller, u16 button, u16 state)
{
}
