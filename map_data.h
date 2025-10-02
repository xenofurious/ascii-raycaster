#include "header.h"

#pragma once

typedef enum {
    wall,
    empty,
    null
} map_object;

struct file_parse_return {map_object **map_ptr; int rows; int cols;};
struct file_parse_return init_map(char *filename);
void deinit_map(map_object **map_ptr, int map_rows, int map_cols);

