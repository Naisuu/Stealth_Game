#include "../include/Check.h"

int test_wall_A(Tile *board[], double x0, double y0, double x1, double y1) {
    double a;
    if (y0 < y1) {
        a = y0 + 1;
        while (a < y1) {
            if (board[(int)a][(int)x0] == WALL)  return 1;
            a++;
        }
    }
    else {
        a = y0 - 1;
        while (a > y1) {
            if (board[(int)a][(int)x0] == WALL)  return 1;
            a--;
        }
    }
    return 0;
}

int test_wall_B(Tile *board[], double x0, double y0, double x1, double y1) {
    double a;
    if (x0 < x1) {
        a = x0 + 1;
        while (a < x1) {
            if (board[(int)y0][(int)a] == WALL)  return 1;
            a++;
        }
    }
    else {
        a = x0 - 1;
        while (a < y1) {
            if (board[(int)y0][(int)x0] == WALL)  return 1;
            a--;
        }
    }
    return 0;
}

int test_wall(Tile *board[], Guardian guardian, Player *player) {
    double x0, y0, x1, y1, xa, ya, a, m, p;
    x0 = player->position.x / SIZE;
    y0 = player->position.y / SIZE;
    x1 = guardian.position.x / SIZE;
    y1 = guardian.position.y / SIZE;
    m = (y1 - y0)/(x1 - x0);    /* y = mx + p */
    p = y0 - ((y1 - y0)/(x1 - x0) * x0);
    if (x0 == x1 && y0 == y1) return 0;
    if (x0 == x1) {
        if (test_wall_A(board, x0, y0, x1, y1)) return 1;
        else return 0;
    }
    if (y0 == y1) {
        if (test_wall_B(board, x0, y0, x1, y1)) return 1;
        else return 0;
    }

    if (x0 < x1) { 
        a = x0 + 1;
        while (a < x1) {
            ya = (m * a) + p;
            if(board[(int)ya][(int)a] == WALL)  return 1;
            a++;
        }
    }
    else {
        a = x0;
        while (a > x1) {
            ya = (m * a) + p;
            if(board[(int)ya][(int)a] == WALL)  return 1;
            a--;
        }
    }
    
    if (y0 < y1) {
        a = y0 + 1;
        while (a < y1) {
            xa = (a - p) / m;
            if(board[(int)a][(int)xa] == WALL)  return 1;
            a++;
        }
    }
    else {
        a = y0;
        while (a > y1) {
            xa = (a - p) / m;
            if(board[(int)a][(int)xa] == WALL)  return 1;
            a--;
        }
    }
    return 0; /* pas de mur */
}

int check_lost(Player *player, Guardian guardian[], Tile *board[], char *name, char *chrono) {
    int i;
    for (i = 0; i < player->level; i++) {
        if (calcul_distance(player->position.x, player->position.y, guardian[i].position.x,
            guardian[i].position.y) <= guardian[i].radius * SIZE) {
            if (test_wall(board, guardian[i], player) == 0 && player->invisibility == 0) {
                return 1; 
            }
        }
    }
    return 0;
}


int detect_relic(Guardian guardian, Tile *board[], TabRelic tab_relic[], int level) {
    int i;
    for (i = 0; i < 3; i++) {
        if (tab_relic[i].state == -1) {
            if (calcul_distance(tab_relic[i].position.x * SIZE, tab_relic[i].position.y * SIZE,
                guardian.position.x, guardian.position.y) <= guardian.radius * SIZE) {
                tab_relic[i].state = 0;
                return 1; 
            }
        }
    }
    return 0;
}

int check_relic(Guardian guardian[], Tile *board[], TabRelic tab_relic[], int level) {
    int i;
    int flag = 0;
    for (i = 0; i < 3; i++) {
        if (tab_relic[i].state == -1)
            flag = 1;
    }
    if (flag) {
        for(i = 0; i < level; i++) {
            if (detect_relic(guardian[i], board, tab_relic, level))
                return 1;
        }
    }
    return 0;
}

void test_guardian(Guardian guardian[], Tile *board[], int level) {
    int i;
    for (i = 0; i < level; i++) {
        cross_guardian(guardian, i, level); /* Test collision entre les gardiens */
        if (test_collision_guardian(board, guardian[i]) > 0) {/* Changer la direction et la vitesse */
            guardian[i].dirX *= -1;
            guardian[i].dirY *= -1;
            if (guardian[i].mode == NORMAL){
                if (guardian[i].speed == SPEED_NORMAL) guardian[i].speed += 0.2;
                else guardian[i].speed = SPEED_NORMAL;
            }
        }
    }
}

int check_victory(Player *player, char *name, char *chrono) {
    if (player->relic == 3) {
        if ((player->position.x / SIZE == 1 && player->position.y / SIZE == 1) ||
            (player->position.x / SIZE == 2 && player->position.y / SIZE == 1) ||
            (player->position.x / SIZE == 1 && player->position.y / SIZE == 2) ||
            (player->position.x / SIZE == 2 && player->position.y / SIZE == 2)) {
            save_file_score(name, chrono, player->mana_used);
            return 1;
        }
    }
    return 0;
}

void update_relic(TabRelic tab_relic[], Tile* board[]) {
    int i;
    for (i = 0; i < 3; i++) {
        if (board[tab_relic[i].position.y][tab_relic[i].position.x] == TILE && tab_relic[i].state == 1) {
            tab_relic[i].state = -1; /* la relique vient de disparaître */
        }
    }
}