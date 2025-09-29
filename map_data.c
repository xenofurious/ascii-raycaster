#include "header.h"
#include "map_data.h"


int test_map_rows = 5;
int test_map_cols = 5;

map_object test_map[5][5] = {{wall, wall, wall, wall, wall},
                            {wall, empty, empty, empty, wall},
                            {wall, empty, wall, empty, wall},
                            {wall, empty, empty, empty, wall},
                            {wall, wall, wall, wall, wall}};


map_object (*test_map_ptr)[5] = test_map;
