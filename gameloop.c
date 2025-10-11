#include <ncurses.h>

#include "header.h"

void gameloop (struct player_stats *player) {

    player->direction_facing +=1;
    if (player->direction_facing >360){
        player->direction_facing -=360;
    }
}
