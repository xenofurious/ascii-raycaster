#include <ncurses.h>
#include <math.h>
#include <string.h>

#include "header.h"
#include "linalg.h"
#include "map_data.h"

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
void render_to_buffer (struct player_stats player, float fov, map_object **map_ptr/*,char **screen_ptr*/) {

    int_coord screen_dimensions = (int_coord){140, 90}; // TEMPORARY CODE DELETE LATER

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
    char column_buffer[screen_dimensions.y];    

    for(direction_rad = left_buffer; direction_rad<right_buffer; direction_rad+=div, pixel_column_no++){
        direction = convert_angle_to_normalised_vector(convert_degrees_to_radians(direction_rad));
        raycast_info = perform_raycast(map_ptr, player.player_coords, direction, screen_dimensions.x, screen_dimensions.y);
        raycast_dist = raycast_info.total_dist;
        //printf("raycast distance = %f, ", raycast_dist);
        //printf("raycast direction = %f\n", direction_rad);

        // need to write a function to convert the raycasted distance to perpendicular camera distance. will do in a bit.

        line_height = (screen_dimensions.y / raycast_dist /2);
        if (line_height<0) line_height = 0;
        else if (line_height>screen_dimensions.y) line_height = screen_dimensions.y;
        //printf("line height = %f\n", line_height);

        line_padding = (screen_dimensions.y - line_height)/2;
        line_height_str = screen_dimensions.y-2*line_padding;
        memset(column_buffer, ' ', line_padding);
        memset(column_buffer+line_padding, 'M', line_height_str);
        memset(column_buffer+line_padding + line_height_str, ' ', line_padding);
        column_buffer[screen_dimensions.y-1] = '\0';
        printf("%s\n", column_buffer);
    //    printf("raycast distance = %f, ", raycast_dist);
    //    printf("  line_height =  %d", line_height_str);
    //    printf("  direction xy =  %f, %f", direction.x, direction.y);
    //    printf("  direction rad =  %f\n", direction_rad);

        //strncpy(screen_ptr[pixel_column_no], column_buffer, screen_dimensions.y);
    }
}


// x is the columns, y is the rows.
// it's weird, but it's because the array is stored like that.
// it makes everything easier
/*
void print_display_buffer(char **screen_ptr, int_coord screen_dimensions) {
    for (int i = 0; i<screen_dimensions.x; i++) {
        mvprintw(4, i, "%d", i%10);
    }
    mvprintw(1, 1, "%d", screen_dimensions.x);
    mvprintw(2, 1, "%d", screen_dimensions.y);
}
*/


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
}
