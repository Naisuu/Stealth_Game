#include "../include/Initialization.h"

void initialize_player(Player *player, int level) {
    player->position.x = 36;
    player->position.y = 36;
    player->speed = SPEED_PLAYER;
    player->mana = 0;
    player->mana_used = 0;
    player->acceleration = 0;
    player->invisibility = 0;
    player->relic = 0;
    player->level = level;
}

void initialize_guardian(Tile *board[], Guardian guardian[], int level) {
    int i, x, y, x1, y1, x2, y2;
    int dirX[6] = {1, 0, -1, 0, 1, 0};
    int dirY[6] = {0, 1, 0, -1, 0, 1};

    int zone[6][4] = { { 6, 20, 6, 5},
                       { 8, 30, 6, 20},
                       { 6, 30, 6, 50},
                       { 6, 20, 6, 40},
                       { 6, 5, 6, 50},
                       { 6, 15, 11, 20}};
    
    for (i = 0; i < 6; i++) {
        y1 = zone[i][0]; y2 = zone[i][1];
        x1 = zone[i][2]; x2 = zone[i][3];
        while (1){
            y = rand() % y1 + y2; /* y1 = 6, y2 = 20 random donne 20 -> 25 */
            x = rand() % x1 + x2; /* x1 = 6,  x2 = 5 random donne 5 -> 10 */
            if (board[y][x] == MANA) {
                guardian[i].position.x = x * SIZE;
                guardian[i].position.y = y * SIZE;
                break;
            }
        }
    }
    for (i = 0; i < level; i++) {
        guardian[i].dirX = dirX[i];
        guardian[i].dirY = dirY[i];
        guardian[i].speed = SPEED_NORMAL;
        guardian[i].mode = NORMAL;
        guardian[i].relic = 3;
        guardian[i].radius = 4;
    }
}

void initialize_relic(Tile *board[], TabRelic tab_relic[]) {
    int i, x, y, x1, y1, x2, y2;
    int zone[3][4] = { { 8, 35, 11, 2},
                       { 8, 33, 7, 52},
                       { 6, 2, 11, 45} };
    
    for (i = 0; i < 3; i++) {
        y1 = zone[i][0]; y2 = zone[i][1];
        x1 = zone[i][2]; x2 = zone[i][3];
        while(1) {
            y = rand() % y1 + y2; /* y1 = 8, y2 = 35 random donne 35 -> 42 */
            x = rand() % x1 + x2; /* x1 = 11,  x2 = 2 random donne 2 -> 12 */
            if (board[y][x] == MANA) {
                board[y][x] = RELIC;
                tab_relic[i].position.x = x;
                tab_relic[i].position.y = y;
                tab_relic[i].state = 1;
                break;
            }
        }
    }
}

void create_wall(Tile *board[], Area area) {
    int i, random;
    random = rand() % 2;
    /* Mur Nord */
    if (board[area.line - 1][area.column] == MANA) {
        for (i = 1; i <= area.width; ++i) {
            board[area.line - 1][area.column - 1 + i] = WALL;
            if ((random == 0 && i <= 3) || (random == 1 && i >= area.width - 2))
                board[area.line - 1][area.column - 1 + i] = MANA;
        }
    }
    /* Mur Sud */
    if (board[area.line + area.height][area.column] == MANA) {
        for (i = 1; i <= area.width; ++i) {
            board[area.line + area.height][area.column - 1 + i] = WALL;
            if ((random == 0 && i <= 3) || (random == 1 && i >= area.width - 2))
                board[area.line + area.height][area.column - 1 + i] = MANA;
        }
    }
    /* Mur Ouest */
    if (board[area.line][area.column - 1] == MANA) {
        for (i = 1; i <= area.height; ++i) {
            board[area.line - 1 + i][area.column - 1] = WALL;
            if ((random == 0 && i <= 3) || (random == 1 && i >= area.height - 2))
                board[area.line - 1 + i][area.column - 1] = MANA;
        }
    }
    /* Mur Est */
    if (board[area.line][area.column + area.width] == MANA) {
        for (i = 1; i <= area.height; ++i) {
            board[area.line - 1 + i][area.column + area.width] = WALL;
            if ((random == 0 && i <= 3) || (random == 1 && i >= area.height - 2))
                board[area.line - 1 + i][area.column + area.width] = MANA;
        }
    }
}

void update_area(Area area, Area * area1, Area * area2, int wall, int inv) {
    if (inv == 0) {
        area1->column = area.column;
        area1->line = area.line;
        area1->width = wall - area1->column;
        area1->height = area.height;
        area2->column = wall + 1;
        area2->line = area.line;
        area2->width = area.width - area1->width - 1;
        area2->height = area.height;
    } else {
        area1->column = area.column;
        area1->line = area.line;
        area1->width = area.width;
        area1->height = wall - area1->line;
        area2->column = area.column;
        area2->line = wall + 1;
        area2->width = area.width;
        area2->height = area.height - area1->height - 1;
    }
}

void generate_area(Tile *board[], Area area, int minside) {
    int x, x_size, inv, wall;
    Area area1, area2;

    create_wall(board, area);
    if (area.width > area.height) {
        x = area.column;
        x_size = area.width;
        inv = 0;
    }
    else {
        x = area.line;
        x_size = area.height;
        inv = 1;
    }
    if (x_size < 2 * minside + 1) {
        return;
    }
    if (x_size < 4 * minside) {
        if (rand() % 2 == 0)
            return;
    }
    wall = x + minside + rand() % (x_size - 2 * minside);
    update_area(area, &area1, &area2, wall, inv);
    generate_area(board, area1, minside);
    generate_area(board, area2, minside);
}

void initialize_board(Tile *board[], TabRelic tab_relic[]) {
    int i, j, minside;
    Area area;

    minside = 9;
    area.line = 1;
    area.column = 1;
    area.height = 43;
    area.width = 58;
    for (i = 0; i < 45; i++) {
        for (j = 0; j < 60; j++) {
            board[i][j] = MANA;
        }
    }
    generate_area(board, area, minside);
    for (i = 0; i < 45; i++) {
        for (j = 0; j < 60; j++) {
            if (i == 0 || i == 44 || j == 0 || j == 59){
                board[i][j] = WALL;
            }
        }
    }
    board[1][1] = HALL;
    board[1][2] = HALL;
    board[2][1] = HALL;
    board[2][2] = HALL;
}