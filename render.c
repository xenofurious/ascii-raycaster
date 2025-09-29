#include <ncurses.h>

#include "header.h"


quadrant_dir return_direction(float_coord direction) {
    if (direction.x>=0){
        if (direction.y>=0) {
            return bottom_right;
        } else {
            return top_right;
        }
    } else {
        if (direction.y>=0) {
            return bottom_left; 
        } else {
            return top_left;
        }
    }
}

void calculate_first_step_perpendicular(float_coord start_pos, float_coord direction) {
    float dist_to_wall_x, dist_to_wall_y;    
    dist_to_wall_x = (int)start_pos.x - start_pos.x;
    dist_to_wall_y = (int)start_pos.y - start_pos.y;
    if (direction.x>=0) {
        dist_to_wall_x++;
    }
    if (direction.y>=0) {
        dist_to_wall_y++;
    }
    printf("position to wall (x) = %f\n", dist_to_wall_x);
    printf("position to wall (y) = %f\n", dist_to_wall_y);
}

float raycast(float_coord start_pos, float_coord direction) {
    quadrant_dir raycast_quadrant = return_direction(direction);
    // first pass - reach the first grid
    

    // second pass - from a grid point, calculate consecutive jumps and jump until a wall is reached or X jumps are made.
    return 2.0f;    
}



// this function will NOT be void later on.
// god this is so complicated.
void render_to_buffer (struct player_stats player, float fov, char *map_ptr) {
    

}


// x is the columns, y is the rows.
// it's weird, but it's because the array is stored like that.
// it makes everything easier

void print_display_buffer(char **screen_ptr, int_coord screen_dimensions) {
    for (int i = 0; i<screen_dimensions.x; i++) {
        mvprintw(4, i, "%d", i%10);
    }
    mvprintw(1, 1, "%d", screen_dimensions.x);
    mvprintw(2, 1, "%d", screen_dimensions.y);
}


