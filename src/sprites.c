/*
 * File: sprites.c
 * Author: dgrubb
 * Date: 25/09/2019
 */

/* Platform includes */
#include "genesis.h"

/* Project includes */
#include "sprites.h"

#include "spr.h"

Sprite* paddle_ptr;

const u32 sprites_paddle_top_tile[SPRITES_TILE_HEIGHT] = {
    0x01457530,
    0x14245511,
    0x14245511,
    0x02454831,
    0x02457841,
    0x14245511,
    0x14245511,
    0x01457534
};

const u32 sprites_paddle_mid_tile[SPRITES_TILE_HEIGHT] = {
    0x02233204,
    0x02243424,
    0x12234341,
    0x31111341,
    0x31111341,
    0x12234341,
    0x02243424,
    0x02233204
};

const u16 sprites_paddle_palette[SPRITES_PALETTE_LEN] = {
    RGB24_TO_VDPCOLOR(0x000000),
    RGB24_TO_VDPCOLOR(0x000000),
    RGB24_TO_VDPCOLOR(0x010101),
    RGB24_TO_VDPCOLOR(0x020202),
    RGB24_TO_VDPCOLOR(0x030303),
    RGB24_TO_VDPCOLOR(0x050505),
    RGB24_TO_VDPCOLOR(0x060606),
    RGB24_TO_VDPCOLOR(0x070707),
};

void
sprites_init()
{
    SPR_init();
    paddle_ptr = SPR_addSprite(&paddle, 20, 10, TILE_ATTR(PAL1, 0, FALSE, FALSE));
    SPR_update();
}

