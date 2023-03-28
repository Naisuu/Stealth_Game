#include "../include/Collide.h"

int test_dir_horizontal_player(Tile *board[], Player *player, int dirX) {
    int x, y, flag, move;
    double X0, Y0, X1, Y1;
    X1 = player->position.x;
    Y1 = player->position.y;
    x = (int)X1 / SIZE; /*  Chercher colonne */
    y = (int)Y1/ SIZE; /*  Chercher ligne */
    X0 = x * SIZE;
    Y0 = y * SIZE;
    flag = 0;
    if (dirX * player ->speed * V < 1)
        move = dirX * 1;
    else move = dirX * player->speed * V;
    if (board[y][x+dirX] == WALL) {
        switch (dirX) {
            case 1:  if (X1 + move >= X0 + (SIZE/2))  flag = 1;
                     break;
            case -1: if (X1 + move - 2 <= X0 + (SIZE/2))  flag = 1;
                     break;
            default : break;
        }
    }
    else if (board[y-1][x+dirX] == WALL) {
        if (Y1 < Y0 + SIZE/2 && X1 + move >= X0 + 1 - racine(1/4 - expo(Y1 - Y0, 2)))
            flag = 1;
    }
    else {
        if (board[y+1][x+dirX] == WALL) {
            if (Y1 >= Y0 + SIZE/2 && X1 + move >= X0 + 1 - racine(1/4 - expo(Y0 + 1 - Y1, 2)))
                flag = 1;
        }
    }
    return flag;
}

int test_dir_vertical_player(Tile *board[], Player *player, int dirY) {
    int x, y, flag, move;
    double X0, Y0, X1, Y1;
    X1 = player->position.x;
    Y1 = player->position.y;
    x = (int)X1 / SIZE; /*  Chercher colonne */
    y = (int)Y1/ SIZE; /*  Chercher ligne */
    X0 = x * SIZE;
    Y0 = y * SIZE;
    flag = 0;
    if (dirY * player->speed * V < 1)
        move = dirY * 1;
    else move = dirY * player->speed * V + 1;
    if (board[y+dirY][x] == WALL) {
        switch (dirY) {
            case 1: if (Y1 + move >= Y0 + (SIZE/2))  flag = 1;
                    break;
            case -1: if (Y1 + move <= Y0 + (SIZE/2))  flag = 1;
                     break;
            default : break;
        }
    }
    else if (board[y+dirY][x-1] == WALL) {
        if (X1 < X0 + SIZE/2 && Y1 + move >= Y0 + 1 - racine(1/4 - expo(X1 - X0, 2)))
            flag = 1;
    }
    else {
        if (board[y+dirY][x+1] == WALL) {
            if (X1 >= X0 + SIZE/2 && Y1 + move >= Y0 + 1 - racine(1/4 - expo(X0 + 1 - X1, 2)))
                flag = 1;
        }
    }
    return flag;
}

int test_collision_player(Tile *board[], Player *player, int dirX, int dirY) {
    int flag;
    if (dirX == 1 || dirX == -1)
        flag = test_dir_horizontal_player(board, player, dirX);
    else
        flag = test_dir_vertical_player(board, player, dirY);
    return flag;
}

int test_dir_horizontal_guardian(Tile *board[], Guardian guardian, int dirX) {
    int x, y, flag, move, panic;
    double X0, Y0, X1, Y1;
    X1 = guardian.position.x;
    Y1 = guardian.position.y;
    x = (int)X1 / SIZE; /*  Chercher colonne */
    y = (int)Y1 / SIZE; /*  Chercher ligne */
    X0 = x * SIZE;
    Y0 = y * SIZE;
    flag = 0;
    if (dirX * guardian.speed * V < 1) 
        move = dirX * 1;
    else move = dirX * guardian.speed * V;
    (guardian.mode == PANIC) ? (panic = dirX) : (panic = 0); /* le mur est à une case de distance*/
    if (board[y][x+dirX+panic] == WALL || board[y][x+dirX+panic] == RELIC) {
        switch (dirX) {
            case 1: if (X1 + move >= X0 + (SIZE/2))  flag = 1;
                    break;
            case -1: if (X1 + move <= X0 + (SIZE/2))  flag = 1;
                     break;
            default : break;
        }
    }
    else if (board[y-1][x+dirX+panic] == WALL || board[y-1][x+dirX+panic] == RELIC) {
        if (Y1 < Y0 + SIZE/2 && X1 + move >= X0 + 1 - racine(1/4 - expo(Y1 - Y0, 2)))
            flag = 1;
    }
    else {
        if (board[y+1][x+dirX+panic] == WALL || board[y+1][x+dirX+panic] == RELIC) {
            if (Y1 >= Y0 + SIZE/2 && X1 + move >= X0 + 1 - racine(1/4 - expo(Y0 + 1 - Y1, 2)))
                flag = 1;
        }
    }
    return flag;
}

int test_dir_vertical_guardian(Tile *board[], Guardian guardian, int dirY) {
    int x, y, flag, move, panic;
    double X0, Y0, X1, Y1;
    X1 = guardian.position.x;
    Y1 = guardian.position.y;
    x = (int)X1 / SIZE; /*  Chercher colonne */
    y = (int)Y1/ SIZE; /*  Chercher ligne */
    X0 = x * SIZE;
    Y0 = y * SIZE;
    flag = 0;
    if (dirY * guardian.speed * V < 1)
        move = dirY * 1;
    else move = dirY * guardian.speed * V;
    (guardian.mode == PANIC) ? (panic = dirY) : (panic = 0); /* le mur est à une case de distance*/
    if (board[y+dirY+panic][x] == WALL || board[y+dirY+panic][x] == RELIC) {
        switch (dirY) {
            case 1: if (Y1 + move >= Y0 + (SIZE/2))  flag = 1;
                    break;
            case -1: if (Y1 + move <= Y0 + (SIZE/2))  flag = 1;
                     break;
            default : break;
        }
    }
    else if (board[y+dirY+panic][x-1] == WALL || board[y+dirY+panic][x-1] == RELIC) {
        if (X1 < X0 + SIZE/2 && Y1 + move >= Y0 + 1 - racine(1/4 - expo(X1 - X0, 2)))
            flag = 1;
    }
    else {
        if (board[y+dirY+panic][x+1] == WALL || board[y+dirY+panic][x+1] == RELIC) {
            if (X1 >= X0 + SIZE/2 && Y1 + move >= Y0 + 1 - racine(1/4 - expo(X0 + 1 - X1, 2)))
                flag = 1;
        }
    }
    return flag;
}

int test_collision_guardian(Tile *board[], Guardian guardian) {
    int flag;
    if (guardian.dirX == 1 || guardian.dirX == -1)
        flag = test_dir_horizontal_guardian(board, guardian, guardian.dirX);
    else
        flag = test_dir_vertical_guardian(board, guardian, guardian.dirY);
    return flag;
}

void cross_guardian(Guardian guardian[], int n, int level) {
    int i, m, dir_tmp;
    i = 0;
    m = n;
    while (i < level) {
        if (i != n && i != m) {
            if (racine(expo(guardian[n].position.x - guardian[i].position.x, 2) +
                    expo(guardian[n].position.y - guardian[i].position.y, 2)) <= SIZE) {
                m = i;
                guardian[n].dirX *= -1; /* Les gardiens se sont croisés en horizontal -> on change leur direction */
                guardian[n].dirY *= -1; /* Les gardiens se sont croisés en vertical -> on change leur direction */
                
                dir_tmp = guardian[i].dirX;
                guardian[i].dirX = guardian[i].dirY;
                guardian[i].dirY =  dir_tmp;
            }
        }
        i++;
    }
}
