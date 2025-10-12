#include <ncurses.h>

#include "header.h"
#include "linalg.h"

float_coord direction_gain;
int_coord current_cell;

void update_position(struct player_stats *player, float_coord direction_gain);

int gameloop (struct player_stats *player, map_object **map_ptr) {
    char c = getch();
    if (c == 'w'){
        if (player->player_movement_state != is_walking_forward) player->player_movement_state = is_walking_forward;
        else player->player_movement_state = is_not_walking;
    }
    if (c == 's'){
        if (player->player_movement_state != is_walking_backwards) player->player_movement_state = is_walking_backwards;
        else player->player_movement_state = is_not_walking;
    }
    

    if (c == 'a'){
        if (player->player_rotation_state != is_turning_left) player->player_rotation_state = is_turning_left;
        else player->player_rotation_state = is_stationary;
    }
    if (c == 'd'){
        if (player->player_rotation_state != is_turning_right) player->player_rotation_state = is_turning_right;
        else player->player_rotation_state = is_stationary;
    }

    if (c == 'q'){
        return 1;
    }
    if (player->direction_facing >360){
        player->direction_facing -=360;
    }


    // states
    if (player->player_movement_state == is_walking_forward) {
        direction_gain = convert_angle_to_normalised_vector(convert_degrees_to_radians(player->direction_facing));
    } else if (player->player_movement_state == is_walking_backwards) {
        direction_gain = convert_angle_to_normalised_vector(convert_degrees_to_radians(player->direction_facing+180));
    } else {
        direction_gain = (float_coord){0, 0};
    }
    update_position(player, direction_gain);
    current_cell = (int_coord) {(int)player->player_coords.x, (int)player->player_coords.y};
    if (map_ptr[current_cell.x][current_cell.y] != empty) {
        update_position(player, multiply_vector(direction_gain, -1.0)); 
    }

    if (player->player_rotation_state == is_turning_left) {
        player->direction_facing-=1; 
    } else if (player->player_rotation_state == is_turning_right) {
        player->direction_facing+=1; 
    }

    return 0;

}

void update_position(struct player_stats *player, float_coord direction_gain){
    player->player_coords.x += direction_gain.x * player->walking_speed / 100;
    player->player_coords.y += direction_gain.y * player->walking_speed / 100;
}

// get current cell
// get future cell
// either you're moving UP one cell, left one cell, down one cell, right one cell or diagonal
// if it's diagonal, we may simply ignore
// if it's up or down, we remove the y direction from direction_gain component
// if it's left or right, we remove the x direction from direction_gain component

