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
    ASSET_BALL = 0,
    ASSET_PADDLE_P1,
    ASSET_PADDLE_P2,
    ASSET_ONE_PLAYER,
    ASSET_TWO_PLAYER,
    ASSET_CREDITS,
    ASSET_BACKGROUND_TITLE,
    ASSET_BACKGROUND_PLAYFIELD,
    ASSET_BACKGROUND_CREDITS,
    ASSET_COUNT
} assets_asset;

typedef enum {
    ASSET_BG_TITLE = 0,
    ASSET_BG_PLAYFIELD,
    ASSET_BG_CREDITS,
    ASSET_BG_COUNT
} assets_background;

typedef struct {
    Sprite* paddle_player_one;
    Sprite* paddle_player_two;
    Sprite* ball;
    Sprite* title_one_player;
    Sprite* title_two_player;
    Sprite* title_credits;
} assets_table_t;

void assets_init();
void assets_set_visible(u16 asset, u16 visible);
u16 assets_verify_asset(u16 asset);
void assets_load_default_palettes();
void assets_set_palette(u16 palette, u16* palette_data);
void assets_set_asset_palette(u16 asset, u16 palette);

#endif /* ASSETS_H_ */
