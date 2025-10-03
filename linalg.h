#include "header.h"

#pragma once

#define EPSILON 0.0001

float_coord multiply_vector(float_coord vector, float factor);
float magnitude(float_coord vector);
float_coord sum_vectors(float_coord vector1, float_coord vector2);
float_coord subtract_vectors(float_coord vector1, float_coord vector2);
float_coord convert_angle_to_normalised_vector(float direction);
float convert_degrees_to_radians(float degrees);
float reset_rad(float rad);
