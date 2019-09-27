/*
 * File: assets.c
 * Author: dgrubb
 * Date: 27/09/2019
 */

/* Project includes */
#include "assets.h"

/* Store pointers to instances of things created dynamically */
assets_table_t assets_table;
u16 palette_table[ASSET_COUNT];

void
assets_init()
{
    memset(&assets_table, 0, sizeof(assets_table_t));

    /* Initialise some default palettes, these
     * are liable to be updated during runtime
     */
    palette_table[ASSET_PADDLE_P1] = PAL1;
    palette_table[ASSET_PADDLE_P2] = PAL1;
    palette_table[ASSET_BACKGROUND] = PAL2;
    palette_table[ASSET_BALL] = PAL3;

    /* Load tile and palette data for backgrounds and sprites*/
    SYS_disableInts();
    VDP_loadTileSet(background.tileset, 1, DMA);
    VDP_setPalette(palette_table[ASSET_PADDLE_P1], paddle.palette->data);
    VDP_setPalette(palette_table[ASSET_BACKGROUND], background.palette->data);
    VDP_setPalette(palette_table[ASSET_BALL], ball.palette->data);
    VDP_drawImage(PLAN_B, &background, 0, 0);
    SYS_enableInts();

    /* Initialise the sprite engine and load data */
    SPR_init();
    assets_table.paddle_player_one = SPR_addSprite(
        &paddle,                                                    /* Image pointer */
        20, 10,                                                     /* X, Y coordinates */
        TILE_ATTR(palette_table[ASSET_PADDLE_P1], 0, TRUE, FALSE)   /* Tile data */
    );
    assets_table.paddle_player_two = SPR_addSprite(
        &paddle,
        20, 40,
        TILE_ATTR(palette_table[ASSET_PADDLE_P2], 0, TRUE, FALSE)
    );
    assets_table.ball = SPR_addSprite(
        &ball,
        20, 50,
        TILE_ATTR(palette_table[ASSET_BALL], 0, TRUE, FALSE)
    );

    /* Hide all sprites until called for */
    SPR_setVisibility(assets_table.paddle_player_one, HIDDEN);
    SPR_setVisibility(assets_table.paddle_player_two, HIDDEN);
    SPR_setVisibility(assets_table.ball, HIDDEN);
}

void
assets_set_visible(u16 asset, u16 visible)
{
    Sprite* asset_sprite;
    switch (asset) {
        case ASSET_BALL: asset_sprite = assets_table.ball; break;
        case ASSET_PADDLE_P1: asset_sprite = assets_table.paddle_player_one; break;
        case ASSET_PADDLE_P2: asset_sprite = assets_table.paddle_player_two; break;
        case ASSET_BACKGROUND:
            /* Intentional fall through */
        case ASSET_COUNT:
            /* Intentional fall through */
        default:
            return;
    }
    SPR_setVisibility(asset_sprite, visible);
}

u16
assets_verify_asset(u16 asset)
{
    if (asset < ASSET_COUNT) return TRUE;
    return FALSE;
}
