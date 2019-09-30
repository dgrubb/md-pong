/*
 * File: assets.c
 * Author: dgrubb
 * Date: 27/09/2019
 */

/* Project includes */
#include "assets.h"

/* Store pointers to instances of things created dynamically */
assets_sprite_table_t assets_sprite_table;
u16 palette_table[ASSET_SPRITE_COUNT + ASSET_BACKGROUND_COUNT];
VDPPlan plane_table[ASSET_BACKGROUND_COUNT];

void
assets_init()
{
    memset(&assets_sprite_table, 0, sizeof(assets_sprite_table_t));

    /* Initialise some default palettes, these
     * are liable to be updated during runtime
     */
    assets_load_default_palettes();

    /* Initialise the sprite engine and load data */
    SPR_init();
    assets_sprite_table.paddle_player_one = SPR_addSprite(
        &paddle,                                                    /* Image pointer */
        20, 10,                                                     /* X, Y coordinates */
        TILE_ATTR(palette_table[ASSET_SPRITE_PADDLE_P1], 0, TRUE, FALSE)   /* Tile data */
    );
    assets_sprite_table.paddle_player_two = SPR_addSprite(
        &paddle,
        20, 40,
        TILE_ATTR(palette_table[ASSET_SPRITE_PADDLE_P2], 0, TRUE, FALSE)
    );
    assets_sprite_table.ball = SPR_addSprite(
        &ball,
        20, 50,
        TILE_ATTR(palette_table[ASSET_SPRITE_BALL], 0, TRUE, FALSE)
    );
    assets_sprite_table.title_one_player = SPR_addSprite(
        &title_1up,
        120, 10,
        TILE_ATTR(palette_table[ASSET_SPRITE_BALL], 0, TRUE, FALSE)
    );
    assets_sprite_table.title_two_player = SPR_addSprite(
        &title_2up,
        120, 40,
        TILE_ATTR(palette_table[ASSET_SPRITE_BALL], 0, TRUE, FALSE)
    );
    assets_sprite_table.title_credits = SPR_addSprite(
        &title_1up,
        120, 60,
        TILE_ATTR(palette_table[ASSET_SPRITE_BALL], 0, TRUE, FALSE)
    );

    /* Hide all sprites until called for */
    SPR_setVisibility(assets_sprite_table.paddle_player_one, HIDDEN);
    SPR_setVFlip(assets_sprite_table.paddle_player_one, TRUE);
    SPR_setVisibility(assets_sprite_table.paddle_player_two, HIDDEN);
    SPR_setVisibility(assets_sprite_table.ball, HIDDEN);
    SPR_setVisibility(assets_sprite_table.title_one_player, HIDDEN);
    SPR_setVFlip(assets_sprite_table.title_one_player, FALSE);
    SPR_setVisibility(assets_sprite_table.title_two_player, HIDDEN);
    SPR_setVFlip(assets_sprite_table.title_two_player, FALSE);
    SPR_setVisibility(assets_sprite_table.title_credits, HIDDEN);
    SPR_setVFlip(assets_sprite_table.title_credits, FALSE);
}

void
assets_load_default_palettes()
{
    /* Initialise some default palettes, these
     * are liable to be updated during runtime
     */
    palette_table[ASSET_SPRITE_PADDLE_P1] = PAL1;
    palette_table[ASSET_SPRITE_PADDLE_P2] = PAL1;
    palette_table[ASSET_SPRITE_ONE_PLAYER] = PAL1;
    palette_table[ASSET_SPRITE_TWO_PLAYER] = PAL1;
    palette_table[ASSET_SPRITE_CREDITS] = PAL1;
    palette_table[ASSET_BACKGROUND_TITLE] = PAL2;
    palette_table[ASSET_BACKGROUND_CREDITS] = PAL2;
    palette_table[ASSET_BACKGROUND_PLAYFIELD] = PAL2;
    palette_table[ASSET_SPRITE_BALL] = PAL3;
    SYS_disableInts();
    VDP_setPalette(palette_table[ASSET_SPRITE_PADDLE_P1], title_1up.palette->data);
    VDP_setPalette(palette_table[ASSET_BACKGROUND_TITLE], background.palette->data);
    VDP_setPalette(palette_table[ASSET_SPRITE_BALL], ball.palette->data);
    SYS_enableInts();
}

void
assets_draw_background(u16 asset)
{
    if (FALSE == assets_verify_background_asset(asset)) return;
    SYS_disableInts();
    VDP_loadTileSet(background.tileset, 1, DMA);
    VDP_drawImage(plane_table[asset], &background, 0, 0);
    SYS_enableInts();
}

void
assets_clear_background(u16 asset)
{
    VDP_clearPlan(plane_table[asset], TRUE);
}

void
assets_set_visible(u16 asset, u16 visible)
{
    Sprite* asset_sprite = assets_get_sprite_ptr(asset);
    if (NULL != asset_sprite) SPR_setVisibility(asset_sprite, visible);
}

void
assets_set_sprite_palette(u16 asset, u16 palette)
{
    Sprite* asset_sprite = assets_get_sprite_ptr(asset);
    if (NULL != asset_sprite) SPR_setPalette(asset_sprite, palette_table[palette]);
}
void
assets_set_palette(u16 palette, u16* palette_data)
{
    VDP_setPalette(palette, palette_data);
}

Sprite*
assets_get_sprite_ptr(u16 asset)
{
    Sprite* asset_sprite = NULL;
    if (FALSE == assets_verify_sprite_asset(asset)) return asset_sprite;
    switch (asset) {
        case ASSET_SPRITE_BALL: asset_sprite = assets_sprite_table.ball; break;
        case ASSET_SPRITE_PADDLE_P1: asset_sprite = assets_sprite_table.paddle_player_one; break;
        case ASSET_SPRITE_PADDLE_P2: asset_sprite = assets_sprite_table.paddle_player_two; break;
        case ASSET_SPRITE_ONE_PLAYER: asset_sprite = assets_sprite_table.title_one_player; break;
        case ASSET_SPRITE_TWO_PLAYER: asset_sprite = assets_sprite_table.title_two_player; break;
        case ASSET_SPRITE_CREDITS: asset_sprite = assets_sprite_table.title_credits; break;
        default: break;
    }
    return asset_sprite;
}

u16
assets_verify_sprite_asset(u16 asset)
{
    if (asset < ASSET_SPRITE_COUNT) return TRUE;
    return FALSE;
}

u16
assets_verify_background_asset(u16 asset)
{
    if (asset < ASSET_BACKGROUND_COUNT) return TRUE;
    return FALSE;
}
