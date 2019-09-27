/*
 * File: assets.c
 * Author: dgrubb
 * Date: 27/09/2019
 */

/* Project includes */
#include "assets.h"

const u16 PaddlePalette = PAL1;
const u16 BackgroundPalette = PAL2;

/* Store pointers to instances of things created dynamically */
assets_table_t assets_table;

void
assets_init()
{
    memset(&assets_table, 0, sizeof(assets_table_t));

    /* Load tile and palette data for backgrounds */
    SYS_disableInts();
    VDP_loadTileSet(background.tileset, 1, DMA);
    VDP_setPalette(PaddlePalette, paddle.palette->data);
    VDP_setPalette(BackgroundPalette, background.palette->data);
    VDP_drawImage(PLAN_B, &background, 0, 0);
    SYS_enableInts();

    /* Initialise the sprite engine and load data */
    SPR_init();
    assets_table.paddle_player_one = SPR_addSprite(&paddle, 20, 10, TILE_ATTR(PaddlePalette, 0, TRUE, FALSE));
    assets_table.paddle_player_two = SPR_addSprite(&paddle, 20, 40, TILE_ATTR(PaddlePalette, 0, TRUE, FALSE));
    /* N.B: Ball re-uses the same palette as the paddles for now*/
    assets_table.ball = SPR_addSprite(&ball, 20, 40, TILE_ATTR(PaddlePalette, 0, TRUE, FALSE));
}

