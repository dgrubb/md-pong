/*
 * File: assets.h
 * Author: dgrubb
 * Date: 27/09/2019
 */

#ifndef ASSETS_H_
#define ASSETS_H_

/* Platform includes */
#include <genesis.h>

/* Resources */
#include "images.h"
#include "sprites.h"

typedef enum {
    ASSET_SPRITE_BALL = 0,
    ASSET_SPRITE_PADDLE_P1,
    ASSET_SPRITE_PADDLE_P2,
    ASSET_SPRITE_ONE_PLAYER,
    ASSET_SPRITE_TWO_PLAYER,
    ASSET_SPRITE_CREDITS,
    ASSET_SPRITE_COUNT
} assets_sprites;

typedef enum {
    ASSET_BACKGROUND_TITLE = 0,
    ASSET_BACKGROUND_PLAYFIELD,
    ASSET_BACKGROUND_CREDITS,
    ASSET_BACKGROUND_COUNT
} assets_asset;

void assets_init();
void assets_set_visible(u16 asset, u16 visible);
u16 assets_verify_sprite_asset(u16 asset);
void assets_draw_background(u16 asset);
void assets_clear_background(u16 asset);
u16 assets_verify_background_asset(u16 asset);
Sprite* assets_get_sprite_ptr(u16 asset);
void assets_load_default_palettes();
void assets_set_palette(u16 palette, u16* palette_data);
void assets_set_sprite_palette(u16 asset, u16 palette);

#endif /* ASSETS_H_ */
