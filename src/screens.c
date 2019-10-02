/*
 * File: screens.c
 * Author: dgrubb
 * Date: 24/09/2019
 */

/* Project includes */
#include "screens.h"

Screen_t current_screen = Screens_Title;

void
screens_set_screen(Screen_t screen, u16 force)
{
    if ((!force) && (screen == current_screen)) {
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
        case Screens_Title:
            title_screen_show();
            break;
        case Screens_Playfield:
            playfield_screen_show();
            break;
        case Screens_Credits:
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
        case Screens_Title:
            title_screen_hide();
            break;
        case Screens_Playfield:
            playfield_screen_hide();
            break;
        case Screens_Credits:
            credits_screen_hide();
            break;
        default:
            break;
    }
}

Screen_t
screens_get_current_screen()
{
    return current_screen;
}

void
screens_controller_input(u16 controller, u16 button, u16 state)
{
    switch (current_screen) {
        case Screens_Credits: credits_controller_input(controller, button, state); break;
        case Screens_Playfield: playfield_controller_input(controller, button, state); break;
        case Screens_Title: title_controller_input(controller, button, state); break;
        default: break;
    }
}
