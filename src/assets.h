/*
 * File: assets.h
 * Author: dgrubb
 * Date: 27/09/2019
 */

#ifndef ASSETS_H_
#define ASSETS_H_

/* Platform includes */
#include "genesis.h"

/* Resources */
#include "images.h"
#include "sprites.h"

typedef struct {
    Sprite* paddle_player_one;
    Sprite* paddle_player_two;
    Sprite* ball;
} assets_table_t;

void assets_init();


#endif /* ASSETS_H_ */
