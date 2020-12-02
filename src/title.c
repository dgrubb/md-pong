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

/* The options array contains a list of user-selectable options
 * on this screen. It serves both to provide geometry (compile-time)
 * for each entry and also as a store for pointers to the sprite
 * instances which are dynamically created (run-time) to represent
 * the on-screen elements
 */
static option_info_t options[] = {
    { TITLE_OPTION_ONE_PLAYER, {NULL, NULL}, 96, 60},
    { TITLE_OPTION_TWO_PLAYER, {NULL, NULL}, 96, 94},
    { TITLE_OPTION_CREDITS,    {NULL, NULL}, 96, 128},
    { TITLE_OPTION_COUNT,      {NULL, NULL}, 0,  0}
};

/* This screen only has one piece of dynamic state to consider when drawing
 * elements and responding to user input: which option is currently
 * highlighted.
 */
static u16 current_option = DEFAULT_OPTION;

/* Creates instances of sprites used to display the menu options. Should only
 * be called once at startup as they will persist throughout the lifetime of
 * the program.
 */
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

/* Helper function used to generate each sprite instance. */
Sprite*
title_screen_init_sprite(const SpriteDefinition* sprite, option_t option, u16 palette)
{
    return SPR_addSprite(sprite, options[option].x, options[option].y, TILE_ATTR(palette, 0, FALSE, FALSE));
}

/* Clears the screen and redraws all the menu options
 * with the default selection.
 */
void
title_screen_show()
{
    title_set_palettes();
    VDP_drawImageEx(BG_B, &title_background, 0, 0, 0, PAL0, TRUE);
    title_set_option(DEFAULT_OPTION);
}

/* Clears the screen and clears out sprites so they
 * don't persist onto incorrect screens.
 */
void
title_screen_hide()
{
    int i=0;
    current_option = DEFAULT_OPTION;
    while (i<TITLE_OPTION_COUNT) {
        SPR_setVisibility(options[i].res[TITLE_OPTION_INACTIVE], HIDDEN);
        SPR_setVisibility(options[i].res[TITLE_OPTION_ACTIVE], HIDDEN);
        i++;
    }
}

/* Called in response to user input, changing the highlighted
 * menu option and triggering a redraw.
 */
void
title_set_next_option()
{
    option_t option = current_option+1;
    if (option >= TITLE_OPTION_COUNT) option = TITLE_OPTION_ONE_PLAYER;
    title_set_option(option);
}

/* Called in response to user input, changing the highlighted
 * menu option and triggering a redraw.
 */
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

/* Called in response to user input, changing the highlighted
 * menu option and triggering a redraw.
 */
void
title_set_option(option_t option)
{
    if (option >= TITLE_OPTION_COUNT) return;
    current_option = option;
    title_refresh_options();
}

/* Loads colour information used by assets particular to
 * this screen.
 */
void
title_set_palettes()
{
    VDP_setPalette(PAL0, title_background.palette->data);
    VDP_setPalette(PAL1, text_two_player_default.palette->data);
    VDP_setPalette(PAL2, text_two_player_focus.palette->data);
}


/* Triggers redrawing of menu option assets depending on the
 * current screen state.
 */
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

/* Accepts user input and translates it into an action supported
 * by the current screen.
 */
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
