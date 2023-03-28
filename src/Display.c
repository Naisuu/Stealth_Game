#include "../include/Display.h"

void clic(void) {
    int x, y;
    MLV_wait_keyboard_or_mouse(NULL, NULL, NULL, &x, &y);
}

void display_score(Tab_time *tab_t, Tab_mana *tab_m, int len) {
    int i;
    char text1[10], text2[10];
    char *msg1 = "Score player / time";
    char *msg2 = "Score player / mana";
    
    MLV_draw_filled_rectangle(90, 100, 900, 40, MLV_rgba(100, 100, 200, 255));
    MLV_draw_filled_rectangle(90, 140, 900, 500, MLV_rgba(200, 200, 200, 255));
    MLV_draw_text(260, 110, msg1, MLV_COLOR_WHITE);
    MLV_draw_text(670, 110, msg2, MLV_COLOR_WHITE);
    
    for (i = 0; i < len; i++) {
        MLV_draw_text(100, 150 + 25 * i, tab_t[i].date, MLV_COLOR_BLACK);
        MLV_draw_text(250, 150 + 25 * i, tab_t[i].name, MLV_COLOR_BLACK);
        MLV_draw_text(460, 150 + 25 * i, tab_t[i].time, MLV_COLOR_BLACK);
        MLV_draw_text(550, 150 + 25 * i, tab_m[i].date, MLV_COLOR_BLACK);
        MLV_draw_text(700, 150 + 25 * i, tab_m[i].name, MLV_COLOR_BLACK);
        sprintf(text1, "%d", tab_m[i].mana);
        strncpy(text2, text1, 5);
        MLV_draw_text(920, 150 + 25 * i, text1, MLV_COLOR_BLACK);
        if (i > 15) break;
    }
    MLV_draw_rectangle(90, 100, 900, 540, MLV_COLOR_BLACK);
    MLV_draw_line(240, 140, 240, 640, MLV_COLOR_BLACK);
    MLV_draw_line(450, 140, 450, 640, MLV_COLOR_BLACK);
    MLV_draw_filled_rectangle(540, 140, 2, 500, MLV_rgba(100, 100, 200, 255));
    MLV_draw_line(690, 140, 690, 640, MLV_COLOR_BLACK);
    MLV_draw_line(900, 140, 900, 640, MLV_COLOR_BLACK);
    MLV_actualise_window(); 
}

void display_alert(void) {
    int i;
    for (i = 0; i < 5; i++) {
        MLV_draw_rectangle(i, i, WIDTH - 2*i, HEIGHT - 2*i, MLV_COLOR_RED);
    }
    MLV_actualise_window();
}

void display_win(void) {
    MLV_draw_filled_rectangle(290, 200, 500, 300, MLV_COLOR_YELLOW1);
    MLV_draw_rectangle(290, 200, 500, 300, MLV_COLOR_BLACK);
    MLV_draw_text_with_font(450, 250, "VICTORY", MLV_load_font("Garuda-Oblique.ttf", 40), MLV_COLOR_GREEN);
    MLV_draw_text_with_font(450, 350, "You've won !", MLV_load_font("Garuda-Oblique.ttf", 30), MLV_COLOR_BLACK);
    MLV_actualise_window();
}

void display_lost(void) {
    MLV_draw_filled_rectangle(290, 200, 500, 300, MLV_COLOR_YELLOW1);
    MLV_draw_rectangle(290, 200, 500, 300, MLV_COLOR_BLACK);
    MLV_draw_text_with_font(380, 250, "GAME OVER", MLV_load_font("Garuda-Oblique.ttf", 50), MLV_COLOR_RED);
    MLV_draw_text_with_font(450, 350, "You've lost !", MLV_load_font("Garuda-Oblique.ttf", 30), MLV_COLOR_BLACK);
    MLV_actualise_window();
}

void display_player(Player *player) {
    if (player->acceleration == 1) {
        MLV_draw_circle(player->position.x, player->position.y, SIZE/2, MLV_COLOR_BLACK);
        MLV_draw_filled_circle(player->position.x, player->position.y, SIZE/2-1, MLV_COLOR_RED);
    }
    else if(player->invisibility == 1) {
        MLV_draw_filled_circle(player->position.x, player->position.y, SIZE/2-1, MLV_rgba(240, 100, 0, 100));
    }
    else {
        MLV_draw_circle(player->position.x, player->position.y, SIZE/2, MLV_COLOR_BLACK);
        MLV_draw_filled_circle(player->position.x, player->position.y, SIZE/2-1, MLV_rgba(240, 100, 0, 255));
    }
    MLV_actualise_window();
}

void display_guardian(Guardian guardian[], int level) {
    int i;
    for (i = 0; i < level; i++) {
        MLV_draw_circle(guardian[i].position.x, guardian[i].position.y, SIZE/2, MLV_COLOR_BLACK);
        MLV_draw_filled_circle(guardian[i].position.x, guardian[i].position.y, SIZE/2-1, MLV_COLOR_BLUE);
        MLV_draw_circle(guardian[i].position.x, guardian[i].position.y, SIZE * guardian[i].radius, MLV_COLOR_BLUE);
    }
    MLV_actualise_window();
}

void display_board(Tile *board[]) {
    int i, j;
    for (i = 0; i < 45; i++) {
        for (j = 0; j < 60; j++) {
            switch (board[i][j]) {
                case TILE: MLV_draw_filled_rectangle(j * SIZE, i * SIZE, SIZE, SIZE, MLV_COLOR_GREY);  /* TILL */
                        break;
                case WALL: MLV_draw_filled_rectangle(j * SIZE, i * SIZE, SIZE, SIZE, MLV_COLOR_BLACK); /* WALL */
                        break;
                case RELIC: MLV_draw_filled_rectangle(j * SIZE, i * SIZE, SIZE, SIZE, MLV_COLOR_GREEN); /* RELIC */
                        break;
                case MANA: MLV_draw_filled_rectangle(j * SIZE, i * SIZE, SIZE, SIZE, MLV_rgba(177, 224, 198, 255));  /* MANA */
                        break;
                case HALL: MLV_draw_filled_rectangle(j * SIZE, i * SIZE, SIZE, SIZE, MLV_rgba(200, 200, 100, 255));  /* HALL */
                        break;
                default: break;
            }
            MLV_draw_rectangle(j * SIZE, i * SIZE, SIZE, SIZE, MLV_COLOR_BLACK);
        }
    }
    MLV_actualise_window();
}

void display_mana_duration(int mana, struct timespec start, char* chrono) {
    struct timespec new;
    char msg[20];
    int nb_ms, h, m, s;
    clock_gettime(CLOCK_REALTIME, &new);
    nb_ms = ((new.tv_sec - start.tv_sec) * 1000) + ((new.tv_sec - start.tv_sec) / 1000);
    s = (nb_ms / 1000) % 60;
    m = (nb_ms / (1000 * 60)) % 60;
    h = (nb_ms / (1000 * 60 * 60));
    sprintf(chrono, "%02d : %02d : %02d", h, m, s);
    MLV_draw_filled_rectangle(0, 45 * SIZE, WIDTH, SIZE, MLV_COLOR_BLUE);
    MLV_draw_text(WIDTH/2 -50, 45 * SIZE + 2, chrono, MLV_COLOR_WHITE);
    sprintf(msg, "MANA = %4d", mana);
    MLV_draw_text(SIZE, 45 * SIZE + 2, msg, MLV_COLOR_WHITE);
    MLV_actualise_window();
}

void display_help(char* text) {
    MLV_draw_text_box(200, 200, 600, 400, text, 15, MLV_COLOR_AZURE1,
    MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_LEFT, MLV_HORIZONTAL_LEFT, MLV_VERTICAL_TOP);
    MLV_actualise_window();
    clic();
    MLV_load_screen();
    MLV_actualise_window();
}

int display_choice(MLV_Font* font) {
    int x, y, choice;
    MLV_draw_filled_rectangle(200, 80, 700, 270, MLV_COLOR_AQUAMARINE1);
    MLV_draw_rectangle(200, 80, 700, 270, MLV_COLOR_BLACK);
    MLV_draw_filled_rectangle(260, 225, 210, 100, MLV_COLOR_BLACK);
    MLV_draw_filled_rectangle(640, 225, 210, 100, MLV_COLOR_BLACK);
    MLV_draw_filled_rectangle(270, 235, 190, 80, MLV_COLOR_GREEN);
    MLV_draw_filled_rectangle(650, 235, 190, 80, MLV_COLOR_RED);
    MLV_draw_text_with_font(330, 100, "Choose the difficulty", font, MLV_COLOR_BLACK);
    MLV_draw_text_with_font(285, 225, "Normal", font, MLV_COLOR_BLACK);
    MLV_draw_text_with_font(690, 225, "Hard", font, MLV_COLOR_BLACK);
    MLV_actualise_window();
    while(1) {
        MLV_wait_mouse(&x, &y);
        if (x >= 260 && x <= 470 && y >= 225 && y <= 325) { /* Bouton Normal */
            choice = 1;
            break;
        }
        else if (x >= 640 && x <= 850 && y >= 225 && y <= 325) { /* Bouton Hard */
            choice = 2;
            break;
        }
    }
    return choice;
}

void display_menu(MLV_Font* font) {
    int i;
    char* text[3] = { "Play", "Help", "Exit" };
    MLV_draw_filled_rectangle(2, 2, WIDTH - 4, HEIGHT - 4, MLV_rgba(180, 110, 255, 255));
    MLV_draw_text_with_font(400, 25, "Stealth", MLV_load_font("Garuda-Oblique.ttf", 100), MLV_COLOR_LIGHTSTEELBLUE1);
    MLV_draw_text_with_font(160, 668, "Made by Julien VU & Xavier GIANG", MLV_load_font("Garuda-Oblique.ttf", 25), MLV_COLOR_BLACK);
    for (i = 0; i < 3; i++) {
        MLV_draw_filled_rectangle(700, 200 + 150 * i + (i * 25), 300, 150, MLV_COLOR_GREEN);
        MLV_draw_rectangle(700, 200 + 150 * i + (i * 25) , 300, 150, MLV_COLOR_BLACK);

        MLV_draw_filled_rectangle(725, 200 + i * 150 + 25 * (i + 1), 250, 100, MLV_COLOR_ANTIQUEWHITE1);
        MLV_draw_text_with_font(800, 200 + i * 150 + 25 * (i + 1), text[i], font, MLV_COLOR_BLACK);
        MLV_draw_rectangle(725, 200 + i * 150 + 25 * (i + 1), 250, 100, MLV_COLOR_BLACK);
    }
    MLV_draw_image(MLV_load_image("igm.png"), 100, 650);
    MLV_draw_image(MLV_load_image("board.png"), 100, 200);
    MLV_actualise_window();
}