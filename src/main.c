/*
 * File: main.c
 * Author: dgrubb
 * Date: 24/09/2019
 */

/* Platform includes */
#include "genesis.h"

int main()
{
    const char *title = "Hello, RGS!";

    /* Enable double buffering and write to plane A using a default palette 0.
     * 41kb of VRAM will be dynamically allocated.
     */
    BMP_init(TRUE, PLAN_A, PAL0, FALSE);
    BMP_clear();
    BMP_drawText(title, 14, 3);

    while(1) {
        
    }

    return 0;
}
