
#include <stdio.h>
#define ZMATH_IMPLEMENTATION
#define ZMATH_SHORT_NAMES
#include "zmath.h"

int main(void) 
{
    // Basic Math.
    float angle = 45.0f;
    float rad = deg2rad(angle);
    printf("Sin(45 deg): %.4f\n", sin(rad));
    
    // Vector math.
    vec2 player_pos = {10.0f, 5.0f};
    vec2 velocity   = {1.0f, 0.0f};
    
    // Move player.
    player_pos = v2_add(player_pos, velocity);
    printf("New Pos: {%.1f, %.1f}\n", player_pos.x, player_pos.y);
    
    // Remap / interpolation.
    float hp = 50.0f;
    float max_hp = 100.0f;
    // Remap 0-100 HP to a 0.0-1.0 opacity value.
    float opacity = remap(0.0f, max_hp, 0.0f, 1.0f, hp);
    printf("HP Opacity: %.2f\n", opacity);

    // Distance.
    vec3 a = {0, 0, 0};
    vec3 b = {3, 4, 0};
    vec3 diff = v3_sub(b, a);
    float dist = v3_len(diff);
    printf("Distance: %.1f\n", dist);

    return 0;
}
