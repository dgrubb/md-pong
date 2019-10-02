/*
 * File: playfield.c
 * Author: dgrubb
 * Date: 24/09/2019
 */

/* Project includes */
#include "playfield.h"

u16 controller_states[PLAYFIELD_PLAYERS];
playfield_elem_state_t paddles[PLAYFIELD_PLAYERS];

const u16 player_one = 0;
const u16 player_two = 1;

void
playfield_init()
{
}

void
playfield_reset_elements()
{
    memset(&paddles[player_one], 0, sizeof(playfield_elem_state_t));
    memset(&paddles[player_two], 0, sizeof(playfield_elem_state_t));
    paddles[player_one].x = 24;
    paddles[player_one].y = 100;
    paddles[player_two].x = 296;
    paddles[player_two].y = 100;
    assets_set_sprite_coordinates(ASSET_SPRITE_PADDLE_P1, 24, 100);
    assets_set_sprite_coordinates(ASSET_SPRITE_PADDLE_P2, 296, 100);
    controller_states[player_one] = 0;
    controller_states[player_two] = 0;
}

void
playfield_screen_show()
{
    VDP_setBackgroundColor(1);
    playfield_reset_elements();
    assets_set_visible(ASSET_SPRITE_PADDLE_P1, VISIBLE);
    assets_set_visible(ASSET_SPRITE_PADDLE_P2, VISIBLE);
    assets_set_visible(ASSET_SPRITE_BALL, VISIBLE);
}

void
playfield_screen_hide()
{
    assets_set_visible(ASSET_SPRITE_PADDLE_P1, HIDDEN);
    assets_set_visible(ASSET_SPRITE_PADDLE_P2, HIDDEN);
    assets_set_visible(ASSET_SPRITE_BALL, HIDDEN);
}

void
playfield_update()
{
    playfield_update_player(player_one);
    playfield_update_player(player_two);
    assets_set_sprite_coordinates(ASSET_SPRITE_PADDLE_P1, paddles[player_one].x, paddles[player_one].y);
    assets_set_sprite_coordinates(ASSET_SPRITE_PADDLE_P2, paddles[player_two].x, paddles[player_two].y);
}

void
playfield_update_player(u16 player)
{
    if (BUTTON_UP & controller_states[player]) {
        paddles[player].velocity--;
    } else if (BUTTON_DOWN & controller_states[player]) {
        paddles[player].velocity++;
    } else {
        paddles[player].velocity = 0;
    }
    paddles[player].y += paddles[player].velocity;
}

void
playfield_controller_input(u16 controller, u16 button, u16 state)
{
    u16 *controller_state;
    if (controller == PORT_1) controller_state = &controller_states[player_one];
    if (controller == PORT_2) controller_state = &controller_states[player_two];
    if (button & state) {
        *controller_state |= button;
    } else {
        *controller_state &= ~button;
    }
}
