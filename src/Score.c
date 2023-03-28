#include "../include/Score.h"

void sort_scoretime(Tab_time *tab, int len) {
    int i, j;
    Tab_time tmp;
    for (i = 0; i < len - 1; i++) {
        for (j = 0; j < len - i - 1; j++) {
            if (strcmp(tab[j].time, tab[j + 1].time) > 0) {
                strcpy(tmp.date, tab[j].date);
                strcpy(tmp.name, tab[j].name);
                strcpy(tmp.time, tab[j].time);

                strcpy(tab[j].date, tab[j+1].date);
                strcpy(tab[j].name, tab[j+1].name);
                strcpy(tab[j].time, tab[j+1].time);

                strcpy(tab[j+1].date, tmp.date);
                strcpy(tab[j+1].name, tmp.name);
                strcpy( tab[j+1].time, tmp.time);
            }
        }
    }
}

void sort_scoremana(Tab_mana *tab, int len) {
    int i, j;
    Tab_mana tmp;
    for (i = 0; i < len - 1; i++) {
        for (j = 0; j < len - i - 1; j++) {
            if (tab[j].mana > tab[j + 1].mana) {
                strcpy(tmp.date, tab[j].date);
                strcpy(tmp.name, tab[j].name);
                tmp.mana = tab[j].mana;

                strcpy(tab[j].date, tab[j+1].date);
                strcpy(tab[j].name, tab[j+1].name);
                tab[j].mana = tab[j+1].mana;

                strcpy(tab[j+1].date, tmp.date);
                strcpy(tab[j+1].name, tmp.name);
                tab[j+1].mana = tmp.mana;
            }
        }
    }
}

void save_file_score(char *name, char *chrono, int mana) {
    time_t rawtime;
    struct tm* timeinfo;
    char date[22];
    FILE* f;
    f = fopen("score.bin","ab+");
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(date, 22,"%d/%m/%Y, %H:%M:%S", timeinfo);

    fwrite(&date, 22, 1, f);
    fwrite(name, 21, 1, f);
    fwrite(chrono, 13, 1, f);
    fwrite(&mana, sizeof(int), 1, f);
    fclose(f);
}