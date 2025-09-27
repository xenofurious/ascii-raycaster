#include <ncurses.h>

#include "header.h"

int test_map_rows = 5;
int test_map_cols = 5;

map_object test_map[5][5] = {{wall, wall, wall, wall, wall},
                            {wall, empty, empty, empty, wall},
                            {wall, empty, wall, empty, wall},
                            {wall, empty, empty, empty, wall},
                            {wall, wall, wall, wall, wall}};

void gameloop () {
    

}
