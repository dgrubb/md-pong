/*
 * File: title.c
 * Author: dgrubb
 * Date: 24/09/2019
 */

/* Project includes */
#include "title.h"

/* Resource data */
#include "assets.h"
#include "sprites.h"

static option_info_t options[] = {
    { TITLE_OPTION_ONE_PLAYER, {NULL, NULL}, 96, 60},
    { TITLE_OPTION_TWO_PLAYER, {NULL, NULL}, 96, 94},
    { TITLE_OPTION_CREDITS,    {NULL, NULL}, 96, 128},
    { TITLE_OPTION_COUNT,      {NULL, NULL}, 0, 0}
};

u16 current_option = DEFAULT_OPTION;

void
title_screen_init()
{
    options[TITLE_OPTION_ONE_PLAYER].res[TITLE_OPTION_INACTIVE] = title_screen_init_sprite(&text_one_player_default, TITLE_OPTION_ONE_PLAYER, PAL1);
    options[TITLE_OPTION_TWO_PLAYER].res[TITLE_OPTION_INACTIVE] = title_screen_init_sprite(&text_two_player_default, TITLE_OPTION_TWO_PLAYER, PAL1);
    options[TITLE_OPTION_CREDITS].res[TITLE_OPTION_INACTIVE] = title_screen_init_sprite(&text_credits_default, TITLE_OPTION_CREDITS, PAL1);

    options[TITLE_OPTION_ONE_PLAYER].res[TITLE_OPTION_ACTIVE] = title_screen_init_sprite(&text_one_player_focus, TITLE_OPTION_ONE_PLAYER, PAL2);
    options[TITLE_OPTION_TWO_PLAYER].res[TITLE_OPTION_ACTIVE] = title_screen_init_sprite(&text_two_player_focus, TITLE_OPTION_TWO_PLAYER, PAL2);
    options[TITLE_OPTION_CREDITS].res[TITLE_OPTION_ACTIVE] = title_screen_init_sprite(&text_credits_focus, TITLE_OPTION_CREDITS, PAL2);
}

Sprite*
title_screen_init_sprite(const SpriteDefinition* sprite, option_t option, u16 palette)
{
    return SPR_addSprite(sprite, options[option].x, options[option].y, TILE_ATTR(palette, 0, FALSE, FALSE));
}

void
title_screen_show()
{
    VDP_resetScreen();
    title_set_palettes();
    VDP_drawImageEx(BG_B, &title_background, 0, 0, 0, PAL0, TRUE);
    title_set_option(DEFAULT_OPTION);
}

void
title_screen_hide()
{
    VDP_resetScreen();
    current_option = DEFAULT_OPTION;
}

void
title_set_next_option()
{
    option_t option = current_option+1;
    if (option >= TITLE_OPTION_COUNT) option = TITLE_OPTION_ONE_PLAYER;
    title_set_option(option);
}

void
title_set_previous_option()
{
    option_t option = current_option;
    if (option != TITLE_OPTION_ONE_PLAYER) {
        option--;
    } else {
        option = TITLE_OPTION_CREDITS;
    }
    title_set_option(option);
}

void
title_set_option(option_t option)
{
    if (option >= TITLE_OPTION_COUNT) return;
    current_option = option;
    title_refresh_options();
}

void
title_set_palettes()
{
    VDP_setPalette(PAL0, title_background.palette->data);
    VDP_setPalette(PAL1, text_two_player_default.palette->data);
    VDP_setPalette(PAL2, text_two_player_focus.palette->data);
}

void
title_refresh_options()
{
    int i = 0;
    while (i<TITLE_OPTION_COUNT) {
        SPR_setVisibility(options[i].res[TITLE_OPTION_INACTIVE], current_option == i ? HIDDEN : VISIBLE);
        SPR_setVisibility(options[i].res[TITLE_OPTION_ACTIVE], current_option == i ? VISIBLE : HIDDEN);
        i++;
    }
}

void
title_controller_input(u16 controller, u16 button, u16 down)
{
    /* This screen only needs to respond to singular button down presses */
    if (FALSE == down) return;

    if ((button & BUTTON_START) || (button & BUTTON_A) || (button & BUTTON_B) || (button & BUTTON_C)) {
        switch (current_option) {
            case TITLE_OPTION_ONE_PLAYER: screens_set_screen(Screens_Playfield, TRUE); break;
            case TITLE_OPTION_TWO_PLAYER: screens_set_screen(Screens_Playfield, TRUE); break;
            case TITLE_OPTION_CREDITS: screens_set_screen(Screens_Credits, TRUE); break;
            default: break;
        }
    }

    /* User is not selecting an option, instead they're navigating */
    if (button & BUTTON_DOWN) {
        title_set_next_option();
    }
    if (button & BUTTON_UP) {
        title_set_previous_option();
    }

}
