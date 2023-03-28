#ifndef __INITIALIZATION__
#define __INITIALIZATION__

#include <stdio.h>
#include <stdlib.h>

#define SIZE 18
#define V 3
#define SPEED_NORMAL 0.3
#define SPEED_PANIC 1.0
#define SPEED_PLAYER 0.9
#define SPEED_PLAYER_ACCEL 1.2

typedef struct {
    int x;
    int y;
} Coor;

typedef struct {
    Coor position;
    double speed;
    int mana;
    int mana_used;
    int acceleration;
    int invisibility;
    int relic;
    int level;
} Player;

typedef enum {
    NORMAL,
    PANIC
} Mode;

typedef struct {
    Coor position;
    int dirX;
    int dirY;
    double speed;
    Mode mode;
    int relic;
    int radius;
} Guardian;

typedef struct {
    Coor position;
    int state;
} TabRelic;

typedef struct {
    int line;
    int column;
    int height;
    int width;
} Area;

typedef enum {
    TILE,
    WALL,
    RELIC,
    MANA,
    HALL
} Tile;

/**
 * @brief Fonction initialisant le joueur.
 * 
 * @param player 
 * @param level 
 */
void initialize_player(Player *player, int level);

/**
 * @brief Fonction initialisant les gardiens.
 * 
 * @param board 
 * @param guardian 
 * @param level 
 */
void initialize_guardian(Tile *board[], Guardian guardian[], int level);

/**
 * @brief Fonction initialisant les reliques.
 * 
 * @param board 
 * @param tab_relic 
 */
void initialize_relic(Tile *board[], TabRelic tab_relic[]);

/**
 * @brief Fonction créant les murs sur le terrain.
 * 
 * @param board 
 * @param area 
 */
void create_wall(Tile *board[], Area area);

/**
 * @brief Mis à jour des zones.
 * 
 * @param area 
 * @param area1 
 * @param area2 
 * @param wall 
 * @param inv 
 */
void update_area(Area area, Area * area1, Area * area2, int wall, int inv);

/**
 * @brief Fonction générant une zone.
 * 
 * @param board 
 * @param area 
 * @param minside 
 */
void generate_area(Tile *board[], Area area, int minside);

/**
 * @brief Fonction initialisant le terrain.
 * 
 * @param board 
 * @param tab_relic 
 */
void initialize_board(Tile *board[], TabRelic tab_relic[]);

#endif