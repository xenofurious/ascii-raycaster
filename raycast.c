#include <math.h>
#include <stdbool.h>

#include "header.h"
#include "linalg.h"

// macros
#define ADD(a, b) sum_vectors(a, b)
#define SUB(a, b) subtract_vectors(a, b)


float_coord calculate_first_steps(float_coord start_pos, float_coord direction) {
    float_coord dist_to_wall;    
    dist_to_wall.x = floor(start_pos.x) - start_pos.x;
    dist_to_wall.y = floor(start_pos.y) - start_pos.y;
    if (direction.x>=0) {
        dist_to_wall.x++;
    }
    if (direction.y>=0) {
        dist_to_wall.y++;
    }
    return dist_to_wall;
}

float_coord normalise_vector_along_x_axis(float_coord vector) {
    vector.y = vector.y/fabs(vector.x);
    vector.x = vector.x/fabs(vector.x);
    return vector;
}

float_coord normalise_vector_along_y_axis(float_coord vector) {
    vector.x = vector.x/fabs(vector.y);
    vector.y = vector.y/fabs(vector.y);
    return vector;
}


float_coord get_first_grid_collision(float_coord start_pos, float_coord direction) {
    float_coord next_horizontal_collision = ADD(start_pos, multiply_vector(normalise_vector_along_x_axis(direction), fabs(calculate_first_steps(start_pos, direction).x)));
    float_coord next_vertical_collision = ADD(start_pos, multiply_vector(normalise_vector_along_y_axis(direction), fabs(calculate_first_steps(start_pos, direction).y)));

    return (magnitude(SUB(next_horizontal_collision, start_pos))<magnitude(SUB(next_vertical_collision, start_pos))) ? (next_horizontal_collision) : (next_vertical_collision);   
}

struct grid_collision_return get_next_grid_collision(float_coord pos, float_coord direction, dir prev_collision, float total_dist){
    switch (prev_collision) {
        case up:
            pos.y-=EPSILON; break;
        case right:
            pos.x+=EPSILON; break;
        case down:
            pos.y+=EPSILON; break;
        case left:
            pos.x-=EPSILON; break;
        case none:
            break;
    }

    float_coord next_horizontal_collision = ADD(pos, multiply_vector(normalise_vector_along_x_axis(direction), fabs(calculate_first_steps(pos, direction).x)));
    float_coord next_vertical_collision = ADD(pos, multiply_vector(normalise_vector_along_y_axis(direction), fabs(calculate_first_steps(pos, direction).y)));

    float dir1 = magnitude(SUB(next_horizontal_collision, pos));
    float dir2 = magnitude(SUB(next_vertical_collision, pos));
    bool dir_comp = dir1<dir2;    
    dir collision_dir;    

    float_coord collision_pos = dir_comp ? (next_horizontal_collision) : (next_vertical_collision);
    if (dir_comp) {
        if(next_horizontal_collision.x-pos.x>0) {
            collision_dir = right;
        } else {
            collision_dir = left;
        }
    } else {
        if(next_vertical_collision.y-pos.y>0){
            collision_dir = down;
        } else {
            collision_dir = up;
        }
    }
    total_dist += dir_comp ? dir1 : dir2;
    return (struct grid_collision_return) {collision_pos, collision_dir, total_dist};
}

bool check_collision(dir check_dir, float_coord pos, map_object **map_ptr) { // the fact that it explicitly points towards size 5 is bad and i need to fix this asap
    switch (check_dir){
        case up: pos.y-=EPSILON; break;
        case right: pos.x+=EPSILON; break;
        case down: pos.y+=EPSILON; break;
        case left: pos.x-=EPSILON; break;
        case none: break;
    }
    int_coord check_pos = {(int)pos.x, (int)pos.y};
    if (map_ptr[check_pos.x][check_pos.y] == wall) {
        return true;
    } else {
        return false;
    }
}

struct grid_collision_return perform_raycast(map_object **map_ptr, float_coord start_pos, float_coord direction, int rows, int cols) {
    struct grid_collision_return next_collision_data;
    float_coord pos = start_pos;
    dir collision_dir = none;
    float total_dist = 0;
    bool collided = false;

    int i = 0;
    while (pos.x >0 && pos.y > 0 && pos.x <rows+1 && pos.y<cols+1 && collided==false) { // i don't know if the +1 is useful but i'm not taking any chances
        // printf("\n%dth iteration!!!\n", i);
        next_collision_data = get_next_grid_collision(pos, direction, collision_dir, total_dist);
        pos = next_collision_data.collision_pos; 
        collision_dir = next_collision_data.collision_dir;
        total_dist = next_collision_data.total_dist;
        collided = check_collision(collision_dir, pos, map_ptr);
        
        // printf("coord of wall collision (x) = %f\n", pos.x);
        // printf("coord of wall collision (y) = %f\n", pos.y);
        // printf("direction of collision = %d\n", collision_dir);
        // printf("total distance travelled by the ray = %f\n", total_dist);
        
        i++;
    }
    if (!collided){
        total_dist = -1;
    }
    return (struct grid_collision_return) {pos, collision_dir, total_dist};
}



/*

int main() {
    float_coord test_start_pos = {1.5, 1.5};
    float_coord test_direction = {1.4, -3.6};

    struct file_parse_return map_data = init_map("test_map_1");
    map_object **map_ptr = map_data.map_ptr;
    int rows = map_data.rows;
    int cols = map_data.cols;

    struct grid_collision_return raycast_data = perform_raycast(map_ptr, test_start_pos, test_direction, rows, cols);
    printf("x: %f, y: %f, total dist = %f\n", raycast_data.collision_pos.x, raycast_data.collision_pos.y, raycast_data.total_dist);

    return 0;
}
*/
