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
    ASSET_BACKGROUND,
    ASSET_COUNT
} assets_asset;

typedef struct {
    Sprite* paddle_player_one;
    Sprite* paddle_player_two;
    Sprite* ball;
} assets_table_t;

void assets_init();
void assets_set_visible(u16 asset, u16 visible);
u16 assets_verify_asset(u16 asset);


#endif /* ASSETS_H_ */
