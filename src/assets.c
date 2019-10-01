/*
 * File: assets.c
 * Author: dgrubb
 * Date: 27/09/2019
 */

/* Project includes */
#include "assets.h"

/* Store pointers to instances of things created dynamically */
Sprite* assets_sprite_table[ASSET_SPRITE_COUNT];
const Image* assets_image_table[ASSET_BACKGROUND_COUNT];
u16 palette_table[ASSET_SPRITE_COUNT + ASSET_BACKGROUND_COUNT];
VDPPlan plane_table[ASSET_BACKGROUND_COUNT];

void
assets_init()
{
    memset(&assets_sprite_table, 0, sizeof(Sprite*) * ASSET_SPRITE_COUNT);
    memset(&assets_image_table, 0, sizeof(Image*) * ASSET_BACKGROUND_COUNT);

    /* Initialise some default palettes, these
     * are liable to be updated during runtime
     */
    assets_load_default_palettes();

    /* Initialise the sprite engine and load data */
    SPR_init();
    assets_sprite_table[ASSET_SPRITE_PADDLE_P1] = SPR_addSprite(
        &paddle,                                                            /* Image pointer */
        20, 10,                                                             /* X, Y coordinates */
        TILE_ATTR(palette_table[ASSET_SPRITE_PADDLE_P1], 0, FALSE, FALSE)   /* Tile data */
    );
    assets_sprite_table[ASSET_SPRITE_PADDLE_P2] = SPR_addSprite(
        &paddle,
        20, 40,
        TILE_ATTR(palette_table[ASSET_SPRITE_PADDLE_P2], 0, FALSE, FALSE)
    );
    assets_sprite_table[ASSET_SPRITE_BALL] = SPR_addSprite(
        &ball,
        20, 50,
        TILE_ATTR(palette_table[ASSET_SPRITE_BALL], 0, FALSE, FALSE)
    );
    assets_sprite_table[ASSET_SPRITE_ONE_PLAYER] = SPR_addSprite(
        &title_1up,
        120, 20,
        TILE_ATTR(palette_table[ASSET_SPRITE_BALL], 0, FALSE, FALSE)
    );
    assets_sprite_table[ASSET_SPRITE_TWO_PLAYER] = SPR_addSprite(
        &title_2up,
        120, 40,
        TILE_ATTR(palette_table[ASSET_SPRITE_BALL], 0, FALSE, FALSE)
    );
    assets_sprite_table[ASSET_SPRITE_CREDITS] = SPR_addSprite(
        &title_1up,
        120, 60,
        TILE_ATTR(palette_table[ASSET_SPRITE_BALL], 0, FALSE, FALSE)
    );

    /* Hide all sprites until called for */
    SPR_setVisibility(assets_sprite_table[ASSET_SPRITE_PADDLE_P1], HIDDEN);
    SPR_setVisibility(assets_sprite_table[ASSET_SPRITE_PADDLE_P2], HIDDEN);
    SPR_setVisibility(assets_sprite_table[ASSET_SPRITE_BALL], HIDDEN);
    SPR_setVisibility(assets_sprite_table[ASSET_SPRITE_ONE_PLAYER], HIDDEN);
    SPR_setVisibility(assets_sprite_table[ASSET_SPRITE_TWO_PLAYER], HIDDEN);
    SPR_setVisibility(assets_sprite_table[ASSET_SPRITE_CREDITS], HIDDEN);

    /* Load image data pointers
     */
    assets_image_table[ASSET_BACKGROUND_TITLE] = &background;
    assets_image_table[ASSET_BACKGROUND_PLAYFIELD] = &background;
    assets_image_table[ASSET_BACKGROUND_CREDITS] = &background;
}

void
assets_load_default_palettes()
{
    /* Initialise some default palettes, these
     * are liable to be updated during runtime
     */
    palette_table[ASSET_SPRITE_PADDLE_P1] = PAL0;
    palette_table[ASSET_SPRITE_PADDLE_P2] = PAL0;
    palette_table[ASSET_SPRITE_BALL] = PAL0;
    palette_table[ASSET_SPRITE_ONE_PLAYER] = PAL1;
    palette_table[ASSET_SPRITE_TWO_PLAYER] = PAL1;
    palette_table[ASSET_SPRITE_CREDITS] = PAL1;
    palette_table[ASSET_BACKGROUND_TITLE] = PAL2;
    palette_table[ASSET_BACKGROUND_CREDITS] = PAL2;
    palette_table[ASSET_BACKGROUND_PLAYFIELD] = PAL2;
    /* Now load some data into the available palettes.
     * This is also liable to be updated during execution.
     */
    SYS_disableInts();
    VDP_setPalette(PAL0, paddle.palette->data);
    VDP_setPalette(PAL1, title_1up.palette->data);
    VDP_setPalette(PAL2, background.palette->data);
    VDP_setPalette(PAL3, ball.palette->data);
    SYS_enableInts();
}

void
assets_draw_background(u16 asset)
{
    if (FALSE == assets_verify_background_asset(asset)) return;
    SYS_disableInts();
    VDP_loadTileSet(assets_image_table[asset]->tileset, TILE_USERINDEX, DMA);
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
    if (FALSE == assets_verify_sprite_asset(asset)) return NULL;
    return assets_sprite_table[asset];
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
