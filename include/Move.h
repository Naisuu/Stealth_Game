#ifndef __MOVE__
#define __MOVE__

#include "Display.h"

/**
 * @brief Fonction qui gère le déplacement du joueur sur le terrain.
 * 
 * @param player 
 * @param board 
 * @param player_frame 
 * @param dirX 
 * @param dirY 
 * @return int 
 */
int move_player(Player *player, Tile *board[], int *player_frame, int *dirX, int *dirY);

/**
 * @brief Fonction faisant passer le gardien en mode panique.
 * 
 * @param guardian 
 * @param level 
 */
void start_panic(Guardian guardian[], int level);

/**
 * @brief Fonction faisant passer le gardien en mode normal.
 * 
 * @param guardian 
 * @param level 
 */
void stop_panic(Guardian guardian[], int level);

/**
 * @brief Fonction qui change les directions des gardiens.
 * 
 * @param guardian 
 * @param level 
 */
void change_dir(Guardian guardian[], int level);

/**
 * @brief Fonction calculant la distance de déplacement des gardiens en fonction de leur vitesse.
 * 
 * @param speed 
 * @param guardian_frame 
 * @return int 
 */
int calcul_move_guardian(double speed, int *guardian_frame);

/**
 * @brief Fonction qui gère le déplacement des gardiens sur le terrain.
 * 
 * @param guardian 
 * @param board 
 * @param tab_relic 
 * @param level 
 * @param guardian_frame 
 */
void move_guardian(Guardian guardian[], Tile *board[], TabRelic tab_relic[], int level, int *guardian_frame);

#endif