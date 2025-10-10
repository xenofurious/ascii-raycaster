#include <ncurses.h>

#include "header.h"

void gameloop (struct player_stats player, float fov, map_object **map_ptr, char **screen_ptr) {
    printf("gameloop\n");
    render_to_buffer(player, fov, map_ptr, screen_ptr);
}
