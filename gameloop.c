#include <ncurses.h>

#include "header.h"
#include "linalg.h"

void gameloop (struct player_stats *player) {

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
    if (player->direction_facing >360){
        player->direction_facing -=360;
    }


    // states
    if (player->player_movement_state == is_walking_forward) {
        float_coord direction_gain = convert_angle_to_normalised_vector(convert_degrees_to_radians(player->direction_facing));
        player->player_coords.x += direction_gain.x/100;
        player->player_coords.y += direction_gain.y/100;
    } else if (player->player_movement_state == is_walking_backwards) {
        float_coord direction_gain = convert_angle_to_normalised_vector(convert_degrees_to_radians(player->direction_facing));
        player->player_coords.x -= direction_gain.x/100;
        player->player_coords.y -= direction_gain.y/100;
    }


    if (player->player_rotation_state == is_turning_left) {
        player->direction_facing-=1; 
    } else if (player->player_rotation_state == is_turning_right) {
        player->direction_facing+=1; 
    }


}
