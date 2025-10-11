#include <unistd.h>
#include <time.h>
#include <ncurses.h>
#include <stdlib.h>

#include "header.h"
#include "map_data.h"

const int fps = 60;
const float delta_time = 1000000/(float)fps;
const float char_width_to_height = 1.85023686; // optimised specifically for my terminal font. i don't really care what you think tbh.
float fov;
struct player_stats player;


char **init_display(int_coord screen_dimensions) {
    char** arr;
    arr = (char**)malloc(screen_dimensions.x * sizeof(char*)); 
    for (int i = 0; i < screen_dimensions.x; i++)
        arr[i] = (char*)malloc(screen_dimensions.y * sizeof(char));

    for (int i = 0; i < screen_dimensions.x; i++) {
        for (int j = 0; j < screen_dimensions.y; j++) {
            arr[i][j] = ' '; 
        }
    }
    return arr;
}

void deinit_display(char **arr, int_coord screen_dimensions) {
    for (int i = 0; i < screen_dimensions.x; i++) {
        free(arr[i]); 
    }
    free(arr); 
}

void tick_loop(char **screen_ptr, int_coord screen_dimensions, float fov, struct player_stats *player, map_object **map_ptr) {
    int counter = 0;
    clock_t start, end;
    float compute_time;
    int bob = 1;

    while (bob == 1) {
        start = clock();

        counter++;
        
        // init map
        gameloop(player);
        render_to_buffer(player, fov, screen_dimensions, map_ptr, screen_ptr);
        refresh();

        end = clock();
        compute_time = 1000000*(float)(end-start)/CLOCKS_PER_SEC;

//        printf("%.7f\n", compute_time); // this is a very handy debug parameter for seeing how much compute time the program is taking.
        if (delta_time>compute_time) {
            usleep(delta_time - compute_time);
        }
    }
}

int_coord get_screen_dimensions() {
    int rows, cols;
    float float_rows, float_cols;
    getmaxyx(stdscr, rows, cols);
    float_rows = rows * char_width_to_height;
    float_cols = cols;
    
    if (float_cols > (float_rows * 16.0f / 9.0f)) {
        cols = (int)(float_rows * 16.0f / 9.0f);
    } else {
        rows = (int)(float_cols * 9.0f / 16.0f / char_width_to_height);
    }
    

    int_coord return_ints;
    return_ints.x = cols;
    return_ints.y = rows;
    return return_ints;
}

int main() {
    initscr();
    nodelay(stdscr, TRUE);
    struct file_parse_return map = init_map("test_map_1");
    map_object **map_ptr = map.map_ptr;
    int cols = map.cols;
    int rows = map.rows;
    
    int_coord screen_dimensions = get_screen_dimensions();
//    int_coord screen_dimensions = {205, 62};


    char **screen_ptr = init_display(screen_dimensions);

    player.player_coords = (float_coord){1.5, 1.5};
    player.direction_facing = 135;
    player.player_movement_state = is_not_walking;
    player.player_rotation_state = is_stationary;
    fov = 90;
        
    tick_loop(screen_ptr, screen_dimensions, fov, &player, map_ptr);

    endwin();
    deinit_display(screen_ptr, screen_dimensions);
    deinit_map(map_ptr, rows, cols);
    printf("rows: %d\n, cols: %d\n", screen_dimensions.x, screen_dimensions.y);
    return 0;
}

