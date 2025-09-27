#include <unistd.h>
#include <time.h>
#include <ncurses.h>
#include <stdlib.h>

#include "header.h"

const int fps = 60;
const float delta_time = 1000000/(float)fps;
const float char_width_to_height = 1.85023686; // optimised specifically for my terminal font. i don't really care what you think tbh.


char *init_display(struct int_coord screen_dimensions) {
    char (*screen)[screen_dimensions.x] = malloc((screen_dimensions.x * screen_dimensions.y) * sizeof(char));
    return *screen;
}

void deinit_display(char *screen_ptr) {
    free(screen_ptr);    
}

void tick_loop(char **screen_ptr, struct int_coord screen_dimensions, struct player_stats player) {
    int counter = 0;
    clock_t start, end;
    float compute_time;

    while (1) {
        start = clock();

        counter++;
        
        gameloop();
        print_display_buffer(screen_ptr, screen_dimensions);
        refresh();

        end = clock();
        compute_time = (float)(end-start)/CLOCKS_PER_SEC;

//        printf("%.7f\n", compute_time); // this is a very handy debug parameter for seeing how much compute time the program is taking.
        if (delta_time>compute_time) {
            usleep(delta_time - (1000000*compute_time));
        }
    }
}

struct int_coord get_screen_dimensions() {
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
    

    struct int_coord return_ints;
    return_ints.x = cols;
    return_ints.y = rows;
    return return_ints;
}

int main() {
    initscr();
    struct int_coord screen_dimensions = get_screen_dimensions();
    char *screen_ptr = init_display(screen_dimensions);

    player.player_coords = (float_coord){1.5, 1.5};
    player.direction_facing = 0; 
    fov = 90;
        
    tick_loop(&screen_ptr, screen_dimensions, player);
    endwin();
    deinit_display(screen_ptr);
    return 0;
}
