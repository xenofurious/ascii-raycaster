#include <stdbool.h>

#pragma once

// enums
typedef enum {
    wall,
    empty
} map_object;

typedef enum {is_not, rot_left, rot_right} is_rotating;
typedef enum {top_right, bottom_right, bottom_left, top_left} quadrant_dir;
typedef enum {none, up, right, down, left} dir;

// structs
typedef struct {
    float x;
    float y;
} float_coord;

struct int_coord {
    int x;
    int y;
};

struct player_stats {
    float_coord player_coords;
    float direction_facing;
    bool is_walking;
};

// externs
extern float fov;
extern struct player_stats player;
extern struct int_coord screen_dimensions;


// functions
void gameloop();
struct int_coord get_screen_dimensions();
char *init_display(struct int_coord screen_dimensions);
void deinit_display(char *screen_ptr);
void print_display_buffer(char **screen_ptr, struct int_coord screen_dimensions);
