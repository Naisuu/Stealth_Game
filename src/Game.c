#include "../include/Game.h"

void read_file_player(void) {
    FILE* f;
    int i;
    long  nbr;
    Tab_time *tab_t;
    Tab_mana *tab_m;

    f = fopen("score.bin", "rb");
    if (f == NULL) {
        fprintf(stderr, "file empty\n");
        exit(1);
    }
    fseek(f, 0, SEEK_END); /* Pointer à la fin du fichier */
    nbr = ftell(f) / 60;  /* Calcule le nombre d'enregistrement */
    fseek(f, 0, SEEK_SET); /* Pointer au debut du fichier */
    tab_t = (Tab_time*) malloc(sizeof(Tab_time) * nbr);
    tab_m = (Tab_mana*) malloc(sizeof(Tab_mana) * nbr);
    
    i = 0;
    while(i < nbr) {
        fread(&tab_t[i].date, 22, 1, f);
        fread(&tab_t[i].name, 21, 1, f);
        fread(&tab_t[i].time, 13, 1, f);

        strcpy(tab_m[i].date, tab_t[i].date);
        strcpy(tab_m[i].name, tab_t[i].name);
        fread(&tab_m[i].mana, sizeof(int), 1, f);
        i++;
    }
    fclose(f);
    sort_scoretime(tab_t, nbr);
    sort_scoremana(tab_m, nbr);
    display_score(tab_t, tab_m, i);
    free(tab_t);
    free(tab_m);
}

void end_game(int state) {
    if (state == 1) { /* victoire */
        display_win();
        clic();
        read_file_player();
        clic();
    }
    else {            /* défaite */
        display_lost();
        clic();
    }
}

void calcul_waiting_time(struct timespec end_time, double *extratime) {
    double frametime;
    struct timespec new_time;
    clock_gettime(CLOCK_REALTIME, &new_time);
    frametime = new_time.tv_sec - end_time.tv_sec;
    frametime += (new_time.tv_nsec - end_time.tv_nsec) / 1.0E9;
    (*extratime) = 1.0 / 60 - frametime;
}

void play(Guardian guardian[], Player *player, Tile *board[], TabRelic tab_relic[], char* name) {
    int cmpt, time_panic, guardian_frame, player_frame, dirX, dirY;
    char chrono[20];
    double extratime;
    struct timespec end_time, start_time_panic, end_time_panic, start_time_player;
    
    dirX = 0;
    dirY = 0;
    guardian_frame = 0;
    player_frame = 0;
    cmpt = 0; 
    (player->level == 5) ? (time_panic = 30) : (time_panic = 600);/* Déterminer le nombre de gardiens */
    clock_gettime(CLOCK_REALTIME, &start_time_player);
    while(1) {
        clock_gettime(CLOCK_REALTIME, &end_time);
        move_guardian(guardian, board, tab_relic, player->level, &guardian_frame); /* Déplacer les gardiens */
        display_mana_duration(player->mana, start_time_player, chrono);/* Afficher MANA & le chronomètre */
        if (check_lost(player, guardian, board, name, chrono)) { /* Vérifier Perdu */
            end_game(0);     /* Perdu */
            break;
        }
        display_player(player);
        if (move_player(player, board, &player_frame, &dirX, &dirY)) /* Déplacer le joueur */
            break;
        if (player->relic + guardian[0].relic > 3) {
            update_relic(tab_relic, board);
        }
        if (check_victory(player, name, chrono)) {  /* Vérifier Gagné */
            end_game(1); /* 1 = Gagné */
            break;
        }
        calcul_waiting_time(end_time, &extratime); /* Calcule le temp d'attente d'afficher */
        if (extratime > 0) {
            MLV_wait_milliseconds((int)(extratime * 1000));
        }
        cmpt++;
        if (cmpt == 180) {  /* 180 frames = 3 seconds => changer la direction */
            cmpt = 0;
            change_dir(guardian, player->level);
        }
        if (player->relic + guardian[0].relic > 3) { /* Vérifier les reliques */
            if (check_relic(guardian, board, tab_relic, player->level)) {
                clock_gettime(CLOCK_REALTIME, &start_time_panic);
                MLV_stop_music();
                MLV_play_music(MLV_load_music("Alarm.mp3"), 0.5, -1);
                start_panic(guardian, player->level);
            }
        }
        if (guardian[0].mode == PANIC) {
            display_alert();
            clock_gettime(CLOCK_REALTIME, &end_time_panic);
            if (end_time_panic.tv_sec - start_time_panic.tv_sec >= time_panic) {
                MLV_stop_music();
                MLV_free_music(MLV_load_music("Alarm.mp3"));
                MLV_play_music(MLV_load_music("Prison Life.mp3"), 0.5, -1);
                stop_panic(guardian, player->level);
            }
        }
    }
}

char* input_name(void) {
    MLV_Font* font = MLV_load_font("Garuda-Oblique.ttf", 30);
    char* name, *tmp;
    name = (char*) malloc(sizeof(char) * 20);
    tmp = (char*) malloc(sizeof(char) * 100);
    MLV_draw_filled_rectangle(200, 80, 700, 270, MLV_COLOR_AQUAMARINE1);
    MLV_draw_rectangle(200, 80, 700, 270, MLV_COLOR_BLACK);
    MLV_draw_text_with_font(400, 100, "Enter your name :", font, MLV_COLOR_BLACK);
    while(1) {
        MLV_wait_input_box_with_font(370, 200, 300, 60, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
        MLV_rgba(35, 35, 230, 255), "", &tmp, MLV_load_font("Garuda-Oblique.ttf", 25));
        if (strlen(tmp)> 0) break;
    }
    strncpy(name, tmp, 20);
    name[20] = '\0';
    free (tmp);
    MLV_free_font(font);
    return name;
}

void new_part(int level) {
    char* name;
    int i;
    Tile **board;
    Guardian guardian[level];
    Player player;
    TabRelic tab_relic[3];
    board = (Tile**) malloc(sizeof(Tile*) * 45);
    for (i = 0; i < 45; i++) {
        board[i] = (Tile*) malloc(sizeof(Tile) * 60);
    }
    name = input_name();
    initialize_board(board, tab_relic);
    initialize_relic(board, tab_relic);
    initialize_player(&player, level); 
    initialize_guardian(board, guardian, level);

    MLV_stop_music();
    MLV_free_music(MLV_load_music("Foreign Affairs.mp3"));
    MLV_play_music(MLV_load_music("Prison Life.mp3"), 0.5, -1);
    display_board(board);
    display_player(&player);
    display_guardian(guardian, level);

    play(guardian, &player, board, tab_relic, name);
    MLV_stop_music();
    MLV_free_music(MLV_load_music("Prison Life.mp3"));
    free(board);
}