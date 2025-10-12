#include <ncurses.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "header.h"
#include "linalg.h"

#define ASCII_PALETTE_SIZE 256

const int max_brightness = 256;
const float max_visible_distance = 3;

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


char ascii_palette[ASCII_PALETTE_SIZE + 1] = "   ...',;:clodxkO0KXNWM"; // this is 23 characters
int ascii_palette_size = 23;


// this function will NOT be void later on.
// god this is so complicated.
void render_to_buffer (struct player_stats *player, float fov, int_coord screen_dimensions, map_object **map_ptr,  char **screen_ptr) {

    float left_buffer = player->direction_facing-(fov/2);
    float right_buffer = player->direction_facing+(fov/2);
    float div = fov/screen_dimensions.x;
    float direction_rad, direction_rad_diff;
    float_coord direction;
    
    struct grid_collision_return raycast_info;
    float raycast_dist, screen_dist;

    float line_height;
    int line_padding, line_height_str;
    int pixel_column_no = 0;
    char column_buffer[screen_dimensions.y];    

    for(direction_rad = left_buffer; pixel_column_no<screen_dimensions.x; direction_rad+=div, pixel_column_no++){
        direction = convert_angle_to_normalised_vector(convert_degrees_to_radians(direction_rad));
        raycast_info = perform_raycast(map_ptr, player->player_coords, direction, screen_dimensions.x, screen_dimensions.y);
        raycast_dist = raycast_info.total_dist;

        // "fisheye lens" correction
        direction_rad_diff = player->direction_facing-direction_rad;
        screen_dist = raycast_dist * cos(convert_degrees_to_radians(direction_rad_diff));

        line_height = (screen_dimensions.y / screen_dist /2);
        if (line_height<0) line_height = 0;
        else if (line_height>screen_dimensions.y) line_height = screen_dimensions.y;
        //printf("line height = %f\n", line_height);

        line_padding = (screen_dimensions.y - line_height)/2;
        line_height_str = screen_dimensions.y-2*line_padding;

        float frac_dist = screen_dist/max_visible_distance;
        if (frac_dist>1) frac_dist=1; if (frac_dist<0) frac_dist=0;
        int char_select = ascii_palette_size-frac_dist*ascii_palette_size;

        memset(column_buffer, ' ', line_padding);
        memset(column_buffer+line_padding, ascii_palette[char_select],line_height_str);
        memset(column_buffer+line_padding + line_height_str, ' ', line_padding);
        column_buffer[screen_dimensions.y] = '\0';

        strncpy(screen_ptr[pixel_column_no], column_buffer, screen_dimensions.y-1);
//        printf("%s", screen_ptr[pixel_column_no]);
//        printf(", %d\n", pixel_column_no);
        
    }
    print_display_buffer(screen_ptr, screen_dimensions);
    //mvprintw(65, 0, "%f", player->direction_facing);
}


// x is the columns, y is the rows.
// it's weird, but it's because the array is stored like that.
// it makes everything easier

void print_display_buffer(char **screen_ptr, int_coord screen_dimensions) {
    for (int i = 0; i<screen_dimensions.x; i++) {
        for (int j = 0; j<screen_dimensions.y; j++){
            mvaddch(j, i, screen_ptr[i][j]);
        }
    }
}
