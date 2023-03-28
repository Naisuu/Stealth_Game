#ifndef __GAME__
#define __GAME__

#include "Move.h"

/**
 * @brief Fonction qui permet de faire le tableau de classement.
 * 
 */
void read_file_player(void);

/**
 * @brief Fonction représentant la fin du jeu.
 * 
 * @param state 
 */
void end_game(int state);

/**
 * @brief Fonction calculant le temps d'attente pour atteindre
 * une fréquence de rafraîchissement de 60 FPS.
 * 
 * @param end_time 
 * @param extratime 
 * @param speed 
 */
void calcul_waiting_time(struct timespec end_time, double *extratime);

/**
 * @brief Fonction représentant le jeu.
 * 
 * @param guardian 
 * @param player 
 * @param board 
 * @param tab_relic 
 * @param name 
 */
void play(Guardian guardian[], Player *player, Tile *board[], TabRelic tab_relic[], char* name);

/**
 * @brief Fonction qui permet la saisie du nom du joueur.
 * 
 * @return char* 
 */
char* input_name(void);

/**
 * @brief Fonction gérant une nouvelle partie.
 * 
 * @param level 
 */
void new_part(int level);


#endif