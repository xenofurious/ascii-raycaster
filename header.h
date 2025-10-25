#include <stdbool.h>

#pragma once


typedef enum {is_not, rot_left, rot_right} is_rotating;
typedef enum {none, up, right, down, left} dir;
typedef enum {wall, empty, red_wall, blue_wall, green_wall, yellow_wall, null} map_object;

// structs
typedef struct {
    float x;
    float y;
} float_coord;

typedef struct {
    int x;
    int y;
} int_coord;

enum player_movement_state{is_walking_forward, is_not_walking, is_walking_backwards};
enum player_rotation_state{is_turning_left, is_stationary, is_turning_right};

struct player_stats {
    float_coord player_coords;
    float direction_facing;
    enum player_movement_state player_movement_state;
    enum player_rotation_state player_rotation_state;
    float walking_speed;
};

struct grid_collision_return {float_coord collision_pos; dir collision_dir; map_object collision_type; float total_dist;};
struct grid_collision_return perform_raycast(map_object **map_ptr, float_coord start_pos, float_coord direction, int rows, int cols);

// externs
extern float fov;
extern struct player_stats player;
extern int_coord screen_dimensions;

// functions
int gameloop(struct player_stats *player, map_object **map_ptr);
int_coord get_screen_dimensions();
char **init_display(int_coord screen_dimensions);
void deinit_display(char **arr, int_coord screen_dimensions);
void print_display_buffer(char **screen_ptr, map_object *colour_ptr, int_coord screen_dimensions);
void render_to_buffer (struct player_stats *player, float fov, int_coord screen_dimensions, map_object **map_ptr, char **screen_ptr, map_object *colour_ptr);
