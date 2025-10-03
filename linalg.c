#include <math.h>
#include "header.h"
#include "linalg.h"

float_coord multiply_vector(float_coord vector, float factor) {
    vector.x *= factor;
    vector.y *= factor;
    return vector;
}

float magnitude(float_coord vector) {
    return sqrt(vector.x*vector.x + vector.y*vector.y);    
}

float_coord sum_vectors(float_coord vector1, float_coord vector2){
    float_coord new_vector;
    new_vector.x = vector1.x + vector2.x;
    new_vector.y = vector1.y + vector2.y;
    return new_vector;
}

float_coord subtract_vectors(float_coord vector1, float_coord vector2){
    float_coord new_vector;
    new_vector.x = vector1.x - vector2.x;
    new_vector.y = vector1.y - vector2.y;
    return new_vector;
}

float_coord convert_angle_to_normalised_vector(float direction) {
    return (float_coord){sin(direction), -cos(direction)};
}

float convert_degrees_to_radians(float degrees) {
    return degrees*M_PI/180;
}
