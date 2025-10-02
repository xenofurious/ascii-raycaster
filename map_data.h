#include "header.h"

#pragma once

typedef enum {
    wall,
    empty,
    null
} map_object;

extern int test_map_rows;
extern int test_map_cols;

map_object **malloc_map(int map_rows, int map_cols);
void deinit_map(map_object **map_ptr, int map_rows, int map_cols);

