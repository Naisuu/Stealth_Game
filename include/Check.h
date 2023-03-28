#ifndef __CHECK__
#define __CHECK__

#include "Score.h"

/**
 * @brief Fonction vérifiant s'il y a un mur entre le joueur
 * et le gardien sur une ligne verticale.
 * 
 * @param board 
 * @param x0 
 * @param y0 
 * @param x1 
 * @param y1 
 * @return int 
 */
int test_wall_A(Tile *board[], double x0, double y0, double x1, double y1);

/**
 * @brief Fonction vérifiant s'il y a un mur entre le joueur
 * et le gardien sur une ligne horizontale.
 * 
 * @param board 
 * @param x0 
 * @param y0 
 * @param x1 
 * @param y1 
 * @return int 
 */
int test_wall_B(Tile *board[], double x0, double y0, double x1, double y1);

/**
 * @brief Fonction vérifiant la collision entre le joueur et le gardien à travers un mur.
 * 
 * @param board 
 * @param guardian 
 * @param player 
 * @return int 
 */
int test_wall(Tile *board[], Guardian guardian, Player *player);

/**
 * @brief Fonction vérifiant si le joueur est en contact avec les gardiens.
 * 
 * @param player 
 * @param guardian 
 * @param board 
 * @param name 
 * @param chrono 
 * @return int 
 */
int check_lost(Player *player, Guardian guardian[], Tile *board[], char *name, char *chrono);

/**
 * @brief Fonction gérant la détection des reliques.
 * 
 * @param guardian 
 * @param board 
 * @param tab_relic 
 * @param level 
 * @return int 
 */
int detect_relic(Guardian guardian, Tile *board[], TabRelic tab_relic[], int level);

/**
 * @brief Fonction vérifiant la présence de la relique.
 * 
 * @param guardian 
 * @param board 
 * @param tab_relic 
 * @param level 
 * @return int 
 */
int check_relic(Guardian guardian[], Tile *board[], TabRelic tab_relic[], int level);

/**
 * @brief Fonction vérifiant pour chaque gardien si il y a une collision avec un autre gardien
 * ou un mur, et si c'est le cas, change sa direction de déplacement et sa vitesse.
 * 
 * @param guardian 
 * @param board 
 * @param level 
 */
void test_guardian(Guardian guardian[], Tile *board[], int level);

/**
 * @brief Fonction vérifiant si le joueur a pu s'échapper avec les 3 reliques.
 * 
 * @param player 
 * @param name 
 * @param chrono 
 * @return int 
 */
int check_victory(Player *player, char *name, char *chrono);


/**
 * @brief Fonction mettant à jour le tableau des reliques.
 * 
 * @param tab_relic 
 * @param board 
 */
void update_relic(TabRelic tab_relic[], Tile* board[]);

#endif