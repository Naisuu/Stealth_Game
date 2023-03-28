#ifndef __SCORE__
#define __SCORE__

#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include <string.h>
#include "Skill.h"

typedef struct {
    char date[22];
    char name[21];
    char time[13];
} Tab_time;

typedef struct {
    char date[22];
    char name[21];
    int mana;
} Tab_mana;

/**
 * @brief Fonction triant les temps réalisés par les joueurs.
 * 
 * @param tab 
 * @param len 
 */
void sort_scoretime(Tab_time *tab, int len);

/**
 * @brief Fonction triant les quantités de mana dépensées par les joueurs.
 * 
 * @param tab 
 * @param len 
 */
void sort_scoremana(Tab_mana *tab, int len);

/**
 * @brief Fonction qui enregistre les informations du joueur
 * dans un fichier binaire.
 * 
 * @param name 
 * @param chrono 
 * @param mana 
 */
void save_file_score(char *name, char *chrono, int mana);

#endif