/*
 * File: main.c
 * Author: dgrubb
 * Date: 24/09/2019
 */

/* Platform includes */
#include "genesis.h"

/* Project includes */
#include "playfield.h"
#include "screens.h"
#include "sprites.h"
#include "title.h"

static void controllerHandler(u16 controller, u16 button, u16 state);

int main()
{
    /* Initialise game modules to allow for any dynamic allocation (e.g.,
     * loading sprite data)
     */
    title_screen_init();
    playfield_init();
    sprites_init();
    screens_set_screen(Title, TRUE);

    /* Begin allowing user input */
    JOY_setEventHandler(controllerHandler);

    /* Main game loop */
    for (;;) {
        VDP_waitVSync();
    }

    return 0;
}

static void
controllerHandler(u16 controller, u16 button, u16 state)
{
}
