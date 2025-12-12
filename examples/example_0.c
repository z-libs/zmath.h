
#include <stdio.h>
#define ZMATH_IMPLEMENTATION
#define ZMATH_SHORT_NAMES
#include "zmath.h"

int main(void) 
{
    printf("=> Hypotenuse calculator:\n");

    float a = 3.0f;
    float b = 4.0f;

    float c = hypot(a, b);

    printf("Triangle sides: %.2f, %.2f\n", a, b);
    printf("Hypotenuse:     %.5f\n", c); // Should be exactly 5.00000
    
    // We test the fast inverse square root (1/sqrt(x))
    float inv = invsqrt(25.0f);
    printf("1/sqrt(25):     %.5f\n", inv); // Should be approx 0.2

    return 0;
}
