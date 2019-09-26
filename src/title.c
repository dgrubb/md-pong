/*
 * File: title.c
 * Author: dgrubb
 * Date: 24/09/2019
 */

/* Platform includes */
#include "genesis.h"

/* Project includes */
#include "title.h"

/* Resource includes */
#include "img.h"
#include "spr.h"

void
title_screen_init()
{
}

void
title_screen_show()
{
    /* Disable interrupts while accessing VDP memory */
    SYS_disableInts();
    VDP_resetScreen();
    VDP_setScreenWidth320();
    VDP_setScreenHeight224();
    VDP_loadTileSet(background.tileset, 1, DMA);
    VDP_setPalette(PAL1, paddle.palette->data);
    VDP_setPalette(PAL2, background.palette->data);
    VDP_drawImage(PLAN_B, &background, 0, 0);
    SYS_enableInts();
}

void
title_screen_hide()
{
}


