/*
 * File: screens.c
 * Author: dgrubb
 * Date: 24/09/2019
 */

/* Platform includes */
#include "genesis.h"

/* Project includes */
#include "screens.h"
#include "credits.h"
#include "playfield.h"
#include "title.h"

Screen_t current_screen = Title;

void
screens_set_screen(Screen_t screen, u16 force)
{
    if ((!force) && (screen != current_screen)) {
        return;
    }
    screens_hide_screen(current_screen);
    current_screen = screen;
    screens_show_screen(current_screen);
}

void
screens_show_screen(Screen_t screen)
{
    switch (screen) {
        case Title:
            title_screen_show();
            break;
        case Playfield:
            playfield_screen_show();
            break;
        case Credits:
            credits_screen_show();
            break;
        default:
            break;
    }
}

void
screens_hide_screen(Screen_t screen)
{
    switch (screen) {
        case Title:
            title_screen_hide();
            break;
        case Playfield:
            playfield_screen_hide();
            break;
        case Credits:
            credits_screen_hide();
            break;
        default:
            break;
    }

}

void
screens_controller_input(u16 controller_one_input, u16 controller_two_input)
{

}
