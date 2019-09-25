/*
 * File: main.c
 * Author: dgrubb
 * Date: 24/09/2019
 */

/* Platform includes */
#include "genesis.h"

/* Project includes */
#include "screens.h"

int main()
{
    /* Setup interfaces and initial state */
    SYS_disableInts();
    VDP_resetScreen();
    /* Enable double buffering and write to plan A using a default palette 0.
     * 41kb of VRAM will be dynamically allocated.
     */
    BMP_init(TRUE, PLAN_A, PAL0, FALSE);
    BMP_clear();
    SYS_enableInts();

    /* Initialise game modules to allow for any dynamic allocation (e.g.,
     * loading sprite data)
     */
    title_screen_init();
    playfield_init();
    screens_set_screen(Title, TRUE);

    /* Begin allowing user input */
    JOY_setEventHandler(controllerHandler);

    /* Main game loop */
    for(;;) {
        VDP_waitVSync();
    }

    return 0;
}

static void
controllerHandler(u16 controller, u16 button, u16 state)
{

}
