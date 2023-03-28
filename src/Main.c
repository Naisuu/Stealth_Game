#include "../include/Menu.h"

int main(int argc, char* argv[]) {
    srand(time(NULL));
    MLV_create_window("Stealth", "Stealth", WIDTH, HEIGHT + SIZE);
    menu();
    MLV_free_window();
    return 0;
}