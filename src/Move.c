#include "../include/Move.h"

int move_player(Player *player, Tile *board[], int *player_frame, int *dirX, int *dirY) {
    if (direction(player, board, player_frame, dirX, dirY))
        return 1;
    skill_used(player, board);
    display_player(player);
    return 0;
}

void start_panic(Guardian guardian[], int level) {
    int i;
    for (i = 0; i < level; i++) {
        guardian[i].mode = PANIC;
        guardian[i].speed = SPEED_PANIC;
        guardian[i].relic--;
        guardian[i].radius = 6;
    }
}

void stop_panic(Guardian guardian[], int level) {
    int i;
    for (i = 0; i < level; i++) {
        guardian[i].mode = NORMAL;
        guardian[i].speed = SPEED_NORMAL;
        guardian[i].radius = 4;
    }
}

void change_dir(Guardian guardian[], int level) {
    int i, n;
    n = rand() % 2;
    if (n == 0) n = -1; /* Pour avoir la valeur 1 ou -1 */
    for (i = 0; i < level; i++) {
        guardian[i].dirX = (guardian[i].dirX + n) % 2;
        guardian[i].dirY = (guardian[i].dirY + n) % 2;
        if (guardian[i].speed == SPEED_PANIC) return;
        if (guardian[i].speed == SPEED_NORMAL) guardian[i].speed += 0.2;
        else guardian[i].speed = SPEED_NORMAL;
    }
}

int calcul_move_guardian(double speed, int *guardian_frame) {
    int i;
    double move;
    if((*guardian_frame) == 60) (*guardian_frame) = 0;
    else (*guardian_frame) ++;
    i = 1;
    while(1) {
        if ((double) (i * speed * V) > 1 )
            break;
        i++;
    }
    if ((*guardian_frame) % i == 0)
        move = (double)(i * speed * V);
    else move = 0;
    return round(move);
}

void move_guardian(Guardian guardian[], Tile *board[], TabRelic tab_relic[], int level, int *guardian_frame) {
    int i, move;
    test_guardian(guardian, board, level); 
    move = calcul_move_guardian(guardian[0].speed, guardian_frame);
    for(i = 0; i < level; i++) {
        guardian[i].position.x += guardian[i].dirX * move;
        guardian[i].position.y += guardian[i].dirY * move;
    }
    display_board(board);
    display_guardian(guardian, level);
}
