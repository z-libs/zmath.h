
#include <stdio.h>
#define ZMATH_IMPLEMENTATION
#define ZMATH_SHORT_NAMES 
#include "zmath.h"

int main(void) 
{
    printf("=> Projectile motion simulation:\n");

    float velocity = 50.0f; // m/s
    float angle_deg = 45.0f;
    float gravity = 9.81f;

    float theta = deg2rad(angle_deg);

    // Calculate time of flight: T = (2 * v * sin(theta)) / g
    float flight_time = (2.0f * velocity * sin(theta)) / gravity;

    // Calculate max height: H = (v^2 * sin^2(theta)) / 2g
    float max_height = (pow(velocity, 2.0f) * pow(sin(theta), 2.0f)) / (2.0f * gravity);

    printf("Velocity:   %.2f m/s\n", velocity);
    printf("Angle:      %.2f deg\n", angle_deg);
    printf("Flight Time: %.4f s\n", flight_time);
    printf("Max Height:  %.4f m\n", max_height);

    return 0;
}
