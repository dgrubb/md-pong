/*
 * File: main.c
 * Author: dgrubb
 * Date: 24/09/2019
 */

/* Platform includes */
#include <genesis.h>

/* Project includes */
#include "assets.h"
#include "playfield.h"
#include "screens.h"
#include "title.h"


/* Forward declarations */
static void controllerHandler(u16 controller, u16 button, u16 state);
void display_setup();

int main()
{
    display_setup();
    /* Initialise game modules to allow for any dynamic allocation (e.g.,
     * loading sprite data)
     */
    assets_init();
    screens_set_screen(Screens_Title, TRUE);

    /* Begin allowing user input */
    JOY_init();
    JOY_setEventHandler(controllerHandler);

    /* Main game loop */
    for (;;) {
        SPR_update();
        VDP_waitVSync();
    }

    return 0;
}

static void
controllerHandler(u16 controller, u16 button, u16 state)
{
    screens_controller_input(controller, button, state);
}

void
display_setup()
{
    /* Disable interrupts while accessing VDP memory, reset
     * screen memory and set output resolution to 320x224
     */
    SYS_disableInts();
    VDP_resetScreen();
    VDP_setScreenWidth320();
    VDP_setScreenHeight224();
    SYS_enableInts();
}
