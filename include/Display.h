#ifndef __DISPLAY__
#define __DISPLAY__

#include "Check.h"

#define WIDTH 1080
#define HEIGHT 810

/**
 * @brief Fonction qui permet le clique de la souris.
 * 
 */
void clic(void);

/**
 * @brief Fonction affichant le score par meilleur temps et
 * cell par meilleure consommation de mana.
 * 
 * @param tab_t 
 * @param tab_m 
 * @param len 
 */
void display_score(Tab_time *tab_t, Tab_mana *tab_m, int len);

/**
 * @brief Fonction affichant les effets du mode panique.
 * 
 */
void display_alert(void);

/**
 * @brief Fonction affichant la victoire de la partie.
 * 
 */
void display_win(void);

/**
 * @brief Fonction affichant la défaite de la partie.
 * 
 */
void display_lost(void);

/**
 * @brief Fonction affichant le joueur.
 * 
 * @param player 
 */
void display_player(Player *player);

/**
 * @brief Fonction affichant le gardien.
 * 
 * @param guardian 
 * @param level 
 */
void display_guardian(Guardian guardian[], int level);

/**
 * @brief Fonction affichant le terrain du jeu.
 * 
 * @param board 
 */
void display_board(Tile *board[]);

/**
 * @brief Fonction affichant le mana et le temps de la partie.
 * 
 * @param mana 
 * @param start 
 * @param chrono 
 */
void display_mana_duration(int mana, struct timespec start, char* chrono);

/**
 * @brief Fonction affichant le guide.
 * 
 * @param text 
 */
void display_help(char* text);

/**
 * @brief Fonction affichant le choix de la difficulté.
 * 
 * @param font 
 * @return int 
 */
int display_choice(MLV_Font* font);

/**
 * @brief Fonction affichant le menu du jeu.
 * 
 * @param font 
 */
void display_menu(MLV_Font* font);


#endif