#ifndef __SKILL__
#define __SKILL__

#include "Collide.h"
#include <MLV/MLV_all.h>

/**
 * @brief Fonction gérant la récupération de mana ou de relique
 * en fonction de la case sur laquelle le joueur se trouve
 * 
 * @param board 
 * @param y 
 * @param x 
 * @param player 
 */
void relic_or_mana (Tile *board[], int y, int x, Player *player);

/**
 * @brief Fonction retirant les reliques ou les tuiles de mana.
 * 
 * @param board 
 * @param y 
 * @param x 
 * @param player 
 * @param dirX 
 * @param dirY 
 */
void remove_relic_mana(Tile *board[], int y, int x, Player *player, int dirX, int dirY);

/**
 * @brief Fonction redistribuant les tuiles de mana sur le terrain.
 * 
 * @param board 
 * @param nbr 
 */
void redistribute_mana(Tile *board[], int nbr);

/**
 * @brief Fonction calculant l'utilisation du mana du joueur.
 * 
 * @param player 
 * @param board 
 */
void calcul_mana(Player *player, Tile *board[]);

/**
 * @brief Fonction calculant le mouvement du joueur.
 * 
 * @param player 
 * @param player_frame 
 * @param dirX 
 * @param dirY 
 * @param x 
 * @param y 
 * @return int 
 */
int calcul_move_player(Player *player, int *player_frame, int *dirX, int *dirY, int x, int y);

/**
 * @brief Fonction gérant les directions du joueur.
 * 
 * @param player 
 * @param board 
 * @param player_frame 
 * @param dirX 
 * @param dirY 
 * @return int 
 */
int direction(Player *player, Tile *board[], int *player_frame, int *dirX, int *dirY);

/**
 * @brief Fonction gérant l'utilisation des compétences du joueur.
 * 
 * @param player 
 * @param board 
 */
void skill_used(Player *player, Tile *board[]);



#endif