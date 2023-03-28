#include "../include/Util.h"

double calcul_distance(int x0, int y0, int x1, int y1) {
    int dx, dy;
    dx = x1 - x0;
    dy = y1 - y0;
    return racine((double)(dx * dx + dy * dy));
}

int expo(int a, int b) {
    int i, n;
    n = a;
    if (b < 0) a = 0; 
    else if (b == 0) a = 1;
    else for (i = 0; i < b - 1; a = a * n, i++);
    return a;
}

double racine(double x) {
    int j;
    double i;
    if (x == 0) return 0;
    for (i = x, j = 1 ; j <= 50 ; j++)
        i = (i + x/i) / 2;
    return i;
}

int round(double value) {
    value = (value * 10) + 4;
    value = (int)value;
    value /= 10;
    return (int)value;
}