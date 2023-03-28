#include "../include/Menu.h"

char* help(void) {
    char* text;
    text = "    HELP\n\
Your goal is to infiltrate the room to recover all relics and return to the entrance\n\
without being spotted by the guards. Also you have magic skills to succeed this task.\n\
When you passes over a tile, you picks up the traces of mana in this tile.\n\
Furthermore, you can consume this mana by using the magic skills\n\
which are 'Acceleration' or 'Invisibility'.\n\
But the cooldown of these skills are limited compared to the mana pool you have.\n\
After you succeeds, your personal time and the best timesof other players\n\
are showed.                      \
                                                        ↑\n\
To move you must use the arrow keys on the keyboard.  ← ↓ →  \n\
Acceleration: press the LSHIFT key. (consume 2 mana)\n\
Invisibility: press the SPACE key. (consume 1 mana)\n\
To quit the game, press the ESCAPE key.";
    return text;
}

void menu(void) {
    int x, y, choix, level;
    MLV_Font* font = MLV_load_font("Garuda-Oblique.ttf", 50);
    MLV_init_audio();
    display_menu(font);
    MLV_save_screen();
    MLV_play_music(MLV_load_music("Foreign Affairs.mp3"), 0.5, -1);
    while(1) {
        MLV_wait_mouse(&x, &y);
        if (x > 700 && x < 1000 && y > 200 && y < 700) {
            if (y > 200 && y < 350) {
                choix = display_choice(font);
                (choix == 1) ? (level = 5) : (level = 6);
                new_part(level);
                MLV_play_music(MLV_load_music("Foreign Affairs.mp3"), 0.5, -1);
            }
            if (y > 375 && y < 525) {
                display_help(help());
            }
            if (y > 550 && y < 700) {
                break;
            }
        }
        MLV_load_screen();
        MLV_actualise_window();
    }
    MLV_free_font(font);
}