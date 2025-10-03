#include <stdbool.h>

#pragma once


typedef enum {is_not, rot_left, rot_right} is_rotating;
typedef enum {top_right, bottom_right, bottom_left, top_left} quadrant_dir;
typedef enum {none, up, right, down, left} dir;
typedef enum {wall, empty, null} map_object;

// structs
typedef struct {
    float x;
    float y;
} float_coord;

typedef struct {
    int x;
    int y;
} int_coord;

struct player_stats {
    float_coord player_coords;
    float direction_facing;
    bool is_walking;
};

struct grid_collision_return {float_coord collision_pos; dir collision_dir; float total_dist;};
struct grid_collision_return perform_raycast(map_object **map_ptr, float_coord start_pos, float_coord direction, int rows, int cols);

// externs
extern float fov;
extern struct player_stats player;
extern int_coord screen_dimensions;


// functions
void gameloop();
int_coord get_screen_dimensions();
char **init_display(int_coord screen_dimensions);
void deinit_display(char **arr, int_coord screen_dimensions);
void print_display_buffer(char **screen_ptr, int_coord screen_dimensions);
