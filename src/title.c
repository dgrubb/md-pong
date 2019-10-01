/*
 * File: title.c
 * Author: dgrubb
 * Date: 24/09/2019
 */

/* Project includes */
#include "title.h"

u16 current_option = TITLE_OPTION_ONE_PLAYER;

void
title_screen_init()
{
}

void
title_screen_show()
{
    assets_draw_background(ASSET_BACKGROUND_TITLE);
    assets_set_visible(ASSET_SPRITE_ONE_PLAYER, VISIBLE);
    assets_set_visible(ASSET_SPRITE_TWO_PLAYER, VISIBLE);
    assets_set_visible(ASSET_SPRITE_CREDITS, VISIBLE);
    title_update_selection(TITLE_OPTION_ONE_PLAYER);
}

void
title_screen_hide()
{
    assets_set_visible(ASSET_SPRITE_ONE_PLAYER, HIDDEN);
    assets_set_visible(ASSET_SPRITE_TWO_PLAYER, HIDDEN);
    assets_set_visible(ASSET_SPRITE_CREDITS, HIDDEN);
    assets_clear_background(ASSET_BACKGROUND_TITLE);
}

void
title_focus_element(u16 option, u16 focus)
{
    u16 asset;
    switch (option) {
        case TITLE_OPTION_ONE_PLAYER: asset = ASSET_SPRITE_ONE_PLAYER; break;
        case TITLE_OPTION_TWO_PLAYER: asset = ASSET_SPRITE_TWO_PLAYER; break;
        case TITLE_OPTION_CREDITS: asset = ASSET_SPRITE_CREDITS; break;
        default: return;
    }
    if (focus) {
        assets_set_sprite_palette(asset, ASSET_SPRITE_PADDLE_P1);
    } else {
        assets_set_sprite_palette(asset, ASSET_SPRITE_BALL);
    }
}

void
title_update_selection(u16 option)
{
    title_focus_element(current_option, FALSE);
    current_option = option;
    title_focus_element(current_option, TRUE);
}

void
title_controller_input(u16 controller, u16 button, u16 down)
{
    u16 new_option;

    /* This screen only needs to respond to singular button down presses */
    if (FALSE == down) return;

    if ((button & BUTTON_START) || (button & BUTTON_A) || (button & BUTTON_B) || (button & BUTTON_C)) {
        /* Use is selecting an option */
        switch (current_option) {
            case TITLE_OPTION_ONE_PLAYER:
                /* Intentional fall-through */
            case TITLE_OPTION_TWO_PLAYER:
                screens_set_screen(Screens_Playfield, FALSE);
                return;
            case TITLE_OPTION_CREDITS:
                screens_set_screen(Screens_Credits, FALSE);
                return;
            default: break;
        }
    }

    /* User is not selecting an option, instead they're navigating */
    if (button & BUTTON_DOWN) {
        new_option = current_option + 1;
        if (new_option == TITLE_OPTION_COUNT) {
            new_option = TITLE_OPTION_ONE_PLAYER;
        }
    }
    if (button & BUTTON_UP) {
        new_option = current_option;
        if (current_option == TITLE_OPTION_ONE_PLAYER) {
            new_option = TITLE_OPTION_COUNT;
        }
        new_option--;;
    }

    title_update_selection(new_option);
}
