#include <ncurses.h>
#include <string.h>
#include <stdio.h>

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

// temporary data!!!
struct player_stats player;


float_coord test_start_pos = {1.5, 1.5};
float_coord test_direction = {1.4, -3.6};



// this function will NOT be void later on.
// god this is so complicated.
void render_to_buffer (struct player_stats player, float fov, map_object **map_ptr, char **screen_ptr) {

    int_coord screen_dimensions = (int_coord){205, 62}; // temporary code delete later

    float left_buffer = player.direction_facing-(fov/2);
    float right_buffer = player.direction_facing+(fov/2);
    float div = fov/screen_dimensions.x;
    float direction_rad;
    float_coord direction;
    
    struct grid_collision_return raycast_info;
    float raycast_dist;

    float line_height;
    int line_padding, line_height_str;
    int pixel_column_no = 0;
    printf("calling\n");
    char column_buffer[screen_dimensions.y];    

    for(direction_rad = left_buffer; direction_rad<right_buffer; direction_rad+=div, pixel_column_no++){
        direction = convert_angle_to_normalised_vector(convert_degrees_to_radians(direction_rad));
        raycast_info = perform_raycast(map_ptr, player.player_coords, direction, screen_dimensions.x, screen_dimensions.y);
        raycast_dist = raycast_info.total_dist;

        // need to write a function to convert the raycasted distance to perpendicular camera distance. will do in a bit.

        line_height = (screen_dimensions.y / raycast_dist /2);
        if (line_height<0) line_height = 0;
        else if (line_height>screen_dimensions.y) line_height = screen_dimensions.y;
        //printf("line height = %f\n", line_height);

        line_padding = (screen_dimensions.y - line_height)/2;
        line_height_str = screen_dimensions.y-2*line_padding;
        memset(column_buffer, ' ', line_padding);
        memset(column_buffer+line_padding, 'm', line_height_str);
        memset(column_buffer+line_padding + line_height_str, ' ', line_padding);
        column_buffer[screen_dimensions.y] = '\0';

        strncpy(screen_ptr[pixel_column_no], column_buffer, screen_dimensions.y-1);
//        printf("%s", screen_ptr[pixel_column_no]);
//        printf(", %d\n", pixel_column_no);
        
    }
    print_display_buffer(screen_ptr, screen_dimensions);
}


// x is the columns, y is the rows.
// it's weird, but it's because the array is stored like that.
// it makes everything easier

void print_display_buffer(char **screen_ptr, int_coord screen_dimensions) {
    for (int i = 0; i<screen_dimensions.x; i++) {
        for (int j = 0; j<screen_dimensions.y; j++){
            mvaddch(j, i, screen_ptr[i][j]);

        }

        //printf("%s\n", screen_ptr[i]);
    }
    //mvprintw(4, 4, "I LOVE MEN");
}


/*
int main() {
    struct file_parse_return mapdata = init_map("test_map_1");
    map_object **map_ptr = mapdata.map_ptr;
    int cols = mapdata.cols;
    int rows = mapdata.rows;
    float fov = 90;
    player.player_coords = (float_coord){1.5, 1.5};
    player.direction_facing = 180; // THIS IS IN DEGREES!! 

    
    render_to_buffer(player, fov, map_ptr);
    return 0;
}*/
