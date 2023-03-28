#ifndef __COLLIDE__
#define __COLLIDE__

#include "Util.h"
#define SIZE 18

/**
 * @brief Fonction vérifiant si le mouvement horizontal du joueur est valide
 * en comparant sa position actuelle à celle du mur ou des bords du terrain de jeu.
 * 
 * @param board 
 * @param player 
 * @param dirX 
 * @return int 
 */
int test_dir_horizontal_player(Tile *board[], Player *player, int dirX);

/**
 * @brief Fonction vérifiant si le mouvement vertical du joueur est valide
 * en comparant sa position actuelle à celle du mur ou des bords du terrain de jeu.
 * 
 * @param board 
 * @param player 
 * @param dirY 
 * @return int 
 */
int test_dir_vertical_player(Tile *board[], Player *player, int dirY);

/**
 * @brief Fonction gérant les collisions entre le joueur et les murs ou les bords du terrain.
 * 
 * @param board 
 * @param player 
 * @param dirX 
 * @param dirY 
 * @return int 
 */
int test_collision_player(Tile *board[], Player *player, int dirX, int dirY);

/**
 * @brief Fonction vérifiant si le gardien peut se déplacer dans une direction horizontale
 * en fonction de la présence de murs ou de reliques sur le terrain.
 * 
 * @param board 
 * @param guardian 
 * @param dirX 
 * @return int 
 */
int test_dir_horizontal_guardian(Tile *board[], Guardian guardian, int dirX);

/**
 * @brief Fonction vérifiant si le gardien peut se déplacer dans une direction verticale
 * en fonction de la présence de murs ou de reliques sur le terrain.
 * 
 * @param board 
 * @param guardian 
 * @param dirY 
 * @return int 
 */
int test_dir_vertical_guardian(Tile *board[], Guardian guardian, int dirY);

/**
 * @brief Fonction vérifiant si le gardien est en collision avec un mur ou un relique sur le terrain.
 * 
 * @param board 
 * @param guardian 
 * @return int 
 */
int test_collision_guardian(Tile *board[], Guardian guardian);

/**
 * @brief Fonction gérant les collisions entre les gardiens.
 * Si deux gardiens se croisent, leur direction est inversée.
 * 
 * @param guardian 
 * @param n 
 * @param level 
 */
void cross_guardian(Guardian guardian[], int n, int level);

#endif