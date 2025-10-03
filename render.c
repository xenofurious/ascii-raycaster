#include <ncurses.h>

#include "header.h"
#include "linalg.h"
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




// this function will NOT be void later on.
// god this is so complicated.
void render_to_buffer (struct player_stats player, float fov, char *map_ptr) {
    float_coord direction = convert_angle_to_normalised_vector(player.direction_facing);
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


