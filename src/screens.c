/*
 * File: screens.c
 * Author: dgrubb
 * Date: 24/09/2019
 */

/* Platform includes */
#include "genesis.h"

/* Project includes */
#include "screens.h"
#include "single_player.h"
#include "title.h"
#include "two_player.h"

Screen_t current_screen = Title;

void
screens_set_screen(Screen_t screen, u16 force)
{
    if((!force) && (screen != current_screen)) {
        return;
    }
    screens_hide_screen(current_screen);
    current_screen = screen;
    screens_show_screen(current_screen);
}

void
screens_show_screen(Screen_t screen)
{
    switch(screen) {
        case Title:
            title_screen_show();
            break;
        case Playfield:
            playfield_screen_show();
            break;
        default:
            break;
    }
}

void
screens_hide_screen(Screen_t screen)
{
    switch(screen) {
        case Title:
            title_screen_hide();
            break;
        case Playfield:
            playfield_screen_hide();
            break;
        default:
            break;
    }

}
