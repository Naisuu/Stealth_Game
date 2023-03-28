#include "../include/Skill.h"

void relic_or_mana (Tile *board[], int y, int x, Player *player) {
    switch (board[y][x]) {
        case 2: board[y][x] = TILE;
                player->relic++;
                player->mana++;
                break;
        case 3: board[y][x] = TILE;
                player->mana++;
                break;
        default: break;
    }
}

void remove_relic_mana(Tile *board[], int y, int x, Player *player, int dirX, int dirY) {
    int X, Y;
    X = x;
    Y = y;
    relic_or_mana(board, y, x, player);
    /* Test pour récuperer le 2e mana */
    if (dirX != 0) {
        if (player->position.y + 1 < (y * SIZE) + (SIZE / 2))
            Y = y - 1;
        else {
            if (player->position.y - 1 > (y * SIZE) + (SIZE / 2))
                Y = y + 1;
        }
        if (test_collision_player(board, player, dirX, dirY) == 0) {
            relic_or_mana(board, Y, X, player);
        }
    }
    if (dirY != 0) {
        if (player->position.x + 1 < (x * SIZE) + (SIZE / 2))
            X = x - 1;
        else {
            if (player->position.x - 1 > (x * SIZE) + (SIZE / 2))
                X = x + 1;
        }
        if (test_collision_player(board, player, dirX, dirY) == 0) {
            relic_or_mana(board, Y, X, player);
        }
    }
}

void redistribute_mana(Tile *board[], int nbr) {
    int i, j, n, cmpt;
    if (nbr > 2)
        n = rand() % (nbr + 1 - 1);
    else
        n = 0;
    cmpt = 0;
    for (i = 0; i < 45; i++) {
        for (j = 0; j < 60; j++) {
            if (board[i][j] == TILE) {
                if (cmpt == n) {
                    board[i][j] = MANA;
                    return;
                }
                else cmpt++;
            }
        }
    }
}

void calcul_mana(Player *player, Tile *board[]) {
    if (player->invisibility == 1 && player->mana > 0) {
        redistribute_mana(board, player->mana);
        player->mana -= 1;
        player->mana_used += 1;
    }
    if (player->acceleration == 1 && player->mana > 1) {
        redistribute_mana(board, player->mana);
        player->mana -= 1;
        redistribute_mana(board, player->mana);
        player->mana -= 1;
        player->mana_used += 2;
    }
}

int calcul_move_player(Player *player, int *player_frame, int *dirX, int *dirY, int x, int y) {
    double move;
    if ((*dirX) != x || (*dirY) != y) { /* changer la direction */
        (*dirX) = x;
        (*dirY) = y;
        move = 0.1 * V;
        (*player_frame) = 1;
    }
    else {
        if (player->speed < 0.9) {
            player->speed += (0.03 * (*player_frame));
        }
        else player->speed = 0.9;
        move = player->speed * V;
        (*player_frame)++;
    }
    return (int)move;
}

int direction(Player *player, Tile *board[], int *player_frame, int *dirX, int *dirY) {
    int x, y, move;
    x = player->position.x / SIZE; /*  Chercher colonne */
    y = player->position.y / SIZE; /*  Chercher ligne */
    if (MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) == MLV_PRESSED)
        return 1;   /* Le joueur annule la partie */
    if (MLV_get_keyboard_state(MLV_KEYBOARD_UP) == MLV_PRESSED) {
        if (test_collision_player(board, player, 0, -1) == 0) {
            move = calcul_move_player(player, player_frame, dirX, dirY, 0, -1);
            player->position.y -= move;
            remove_relic_mana(board, y-1, x, player, 0, -1);
            calcul_mana(player, board); 
        }
    }
    else if (MLV_get_keyboard_state(MLV_KEYBOARD_DOWN) == MLV_PRESSED) {
        if (test_collision_player(board, player, 0, 1) == 0) {
            move = calcul_move_player(player, player_frame, dirX, dirY, 0, 1);
            player->position.y += move;
            remove_relic_mana(board, y+1, x, player, 0, 1);
            calcul_mana(player, board);
        }
    }
    else if (MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED) {
        if (test_collision_player(board, player, -1, 0) == 0) {
            move = calcul_move_player(player, player_frame, dirX, dirY, -1, 0);
            player->position.x -= move;
            remove_relic_mana(board, y, x-1, player, -1, 0);
            calcul_mana(player, board);
        }
    }
    else if (MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED) {
        if (test_collision_player(board, player, 1, 0) == 0) {
            move = calcul_move_player(player, player_frame, dirX, dirY, 1, 0);
            player->position.x += move;
            remove_relic_mana(board, y, x+1, player, 1, 0);
            calcul_mana(player, board);
        }
    }
    else {
        (*dirX) = 0;
        (*dirY) = 0;
    }
    return 0;
}

void skill_used(Player *player, Tile *board[]) {
    if (MLV_get_keyboard_state(MLV_KEYBOARD_SPACE) == MLV_PRESSED && player->mana > 0) {
        player->invisibility = 1;
        calcul_mana(player, board);
    }
    else {
        player->invisibility = 0;
    }
    if (MLV_get_keyboard_state(MLV_KEYBOARD_LSHIFT) == MLV_PRESSED && player->mana > 1) {
        player->acceleration = 1;
        player->speed = SPEED_PLAYER_ACCEL;
    }
    else {
        player->acceleration = 0;
        player->speed = SPEED_PLAYER;
    }
}