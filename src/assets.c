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
VDPPlan plane_table[ASSET_BG_COUNT];

void
assets_init()
{
    memset(&assets_table, 0, sizeof(assets_table_t));

    /* Initialise some default palettes, these
     * are liable to be updated during runtime
     */
    assets_load_default_palettes();

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
    assets_table.title_one_player = SPR_addSprite(
        &title_1up,
        120, 10,
        TILE_ATTR(palette_table[ASSET_ONE_PLAYER], 0, TRUE, FALSE)
    );
    assets_table.title_two_player = SPR_addSprite(
        &title_2up,
        120, 40,
        TILE_ATTR(palette_table[ASSET_TWO_PLAYER], 0, TRUE, FALSE)
    );
    assets_table.title_credits = SPR_addSprite(
        &title_1up,
        120, 60,
        TILE_ATTR(palette_table[ASSET_CREDITS], 0, TRUE, FALSE)
    );

    /* Hide all sprites until called for */
    SPR_setVisibility(assets_table.paddle_player_one, HIDDEN);
    SPR_setVisibility(assets_table.paddle_player_two, HIDDEN);
    SPR_setVisibility(assets_table.ball, HIDDEN);
    SPR_setVisibility(assets_table.title_one_player, HIDDEN);
    SPR_setVisibility(assets_table.title_two_player, HIDDEN);
    SPR_setVisibility(assets_table.title_credits, HIDDEN);
}

void
assets_load_default_palettes()
{
    /* Initialise some default palettes, these
     * are liable to be updated during runtime
     */
    palette_table[ASSET_PADDLE_P1] = PAL1;
    palette_table[ASSET_PADDLE_P2] = PAL1;
    palette_table[ASSET_ONE_PLAYER] = PAL1;
    palette_table[ASSET_TWO_PLAYER] = PAL1;
    palette_table[ASSET_CREDITS] = PAL1;
    palette_table[ASSET_BACKGROUND_TITLE] = PAL2;
    palette_table[ASSET_BACKGROUND_CREDITS] = PAL2;
    palette_table[ASSET_BACKGROUND_PLAYFIELD] = PAL2;
    palette_table[ASSET_BALL] = PAL3;
    SYS_disableInts();
    //VDP_setPalette(palette_table[ASSET_PADDLE_P1], paddle.palette->data);
    VDP_setPalette(palette_table[ASSET_PADDLE_P1], title_1up.palette->data);
    VDP_setPalette(palette_table[ASSET_BACKGROUND_TITLE], background.palette->data);
    VDP_setPalette(palette_table[ASSET_BALL], ball.palette->data);
    SYS_enableInts();
}

void
assets_draw_background(u16 asset)
{
    if (FALSE == assets_verify_asset(asset)) return;
    SYS_disableInts();
    VDP_loadTileSet(background.tileset, 1, DMA);
    VDP_drawImage(plane_table[asset], &background, 0, 0);
    SYS_enableInts();
}

void
assets_clear_background(u16 asset)
{
    if (FALSE == assets_verify_asset(asset)) return;
    VDP_clearPlan(plane_table[asset], TRUE);
}

void
assets_set_visible(u16 asset, u16 visible)
{
    if (FALSE == assets_verify_asset(asset)) return;
    Sprite* asset_sprite = NULL;
    u16 asset_bg = 0;
    switch (asset) {
        case ASSET_BALL: asset_sprite = assets_table.ball; break;
        case ASSET_PADDLE_P1: asset_sprite = assets_table.paddle_player_one; break;
        case ASSET_PADDLE_P2: asset_sprite = assets_table.paddle_player_two; break;
        case ASSET_ONE_PLAYER: asset_sprite = assets_table.title_one_player; break;
        case ASSET_TWO_PLAYER: asset_sprite = assets_table.title_two_player; break;
        case ASSET_CREDITS: asset_sprite = assets_table.title_credits; break;
        case ASSET_BACKGROUND_TITLE:
            /* Intentional fall through */
        case ASSET_BACKGROUND_PLAYFIELD:
            /* Intentional fall through */
        case ASSET_BACKGROUND_CREDITS:
            asset_bg = asset;
            break;
        case ASSET_COUNT:
            /* Intentional fall through */
        default:
            return;
    }
    if (NULL != asset_sprite) SPR_setVisibility(asset_sprite, visible);
    if (asset_bg) {
        if (visible == VISIBLE) {
            assets_draw_background(asset_bg);
        } else {
            assets_clear_background(asset_bg);
        }
    }
}

void
assets_set_palette(u16 palette, u16* palette_data)
{
    VDP_setPalette(palette, palette_data);
}

void
assets_set_asset_palette(u16 asset, u16 palette) {
    if (FALSE == assets_verify_asset(asset)) return;
    Sprite* asset_sprite = NULL;
    u16 asset_bg = 0;
    switch (asset) {
        case ASSET_BALL: asset_sprite = assets_table.ball; break;
        case ASSET_PADDLE_P1: asset_sprite = assets_table.paddle_player_one; break;
        case ASSET_PADDLE_P2: asset_sprite = assets_table.paddle_player_two; break;
        case ASSET_ONE_PLAYER: asset_sprite = assets_table.title_one_player; break;
        case ASSET_TWO_PLAYER: asset_sprite = assets_table.title_two_player; break;
        case ASSET_CREDITS: asset_sprite = assets_table.title_credits; break;
        case ASSET_BACKGROUND_TITLE:
            /* Intentional fall through */
        case ASSET_BACKGROUND_PLAYFIELD:
            /* Intentional fall through */
        case ASSET_BACKGROUND_CREDITS:
            asset_bg = asset;
            break;
        case ASSET_COUNT:
            /* Intentional fall through */
        default:
            return;
    }
    if (NULL != asset_sprite) SPR_setPalette(asset_sprite, palette_table[palette]);
    if (asset_bg) {
        /* TODO: switch palette for backgrounds */
    }

}

u16
assets_verify_asset(u16 asset)
{
    if (asset < ASSET_COUNT) return TRUE;
    return FALSE;
}
