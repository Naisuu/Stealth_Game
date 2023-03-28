#ifndef __UTIL__
#define __UTIL__

#include "Initialization.h"

/**
 * @brief Fonction calculant la distance euclidienne.
 * 
 * @param x0 
 * @param y0 
 * @param x1 
 * @param y1 
 * @return double 
 */
double calcul_distance(int x0, int y0, int x1, int y1);

/**
 * @brief Fonction exponentielle.
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int expo(int a, int b);

/**
 * @brief Fonction racine.
 * 
 * @param x 
 * @return double 
 */
double racine(double x);

/**
 * @brief Fonction d'arrondissement.
 * 
 * @param value 
 * @return int 
 */
int round(double value);

#endif