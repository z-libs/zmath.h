
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define ZMATH_IMPLEMENTATION
#define ZMATH_SHORT_NAMES
#include "zmath.h"

#define TEST(name) printf("[TEST] %-35s", name);
#define PASS() printf(" \033[0;32mPASS\033[0m\n")

void test_basic_arithmetic(void) 
{
    TEST("Abs, Min, Max, Clamp, Rounding");

    // Abs.
    assert(zmath_abs(-10.5f) == 10.5f);
    
    // Min/max.
    assert(min(1.0f, 2.0f) == 1.0f);
    assert(max(1.0f, 2.0f) == 2.0f);

    // Clamp.
    assert(clamp(5.0f, 0.0f, 10.0f) == 5.0f);
    assert(clamp(-5.0f, 0.0f, 10.0f) == 0.0f);
    assert(clamp(15.0f, 0.0f, 10.0f) == 10.0f);

    // Rounding.
    assert(floor(2.8f) == 2.0f);
    assert(ceil(2.2f) == 3.0f);
    assert(round(2.5f) == 3.0f);
    assert(round(2.4f) == 2.0f);

    // Fract.
    assert(is_near(fract(1.25f), 0.25f, 0.0001f));

    PASS();
}

void test_interpolation(void) 
{
    TEST("Lerp, InvLerp, Remap, Smooth");

    // Lerp.
    assert(lerp(0.0f, 100.0f, 0.5f) == 50.0f);
    
    // InvLerp.
    assert(inv_lerp(0.0f, 100.0f, 25.0f) == 0.25f);

    // Remap.
    // [0, 10] -> [0, 100]. Value 5 becomes 50.
    assert(remap(0.0f, 10.0f, 0.0f, 100.0f, 5.0f) == 50.0f);

    // Step.
    assert(step(0.5f, 0.4f) == 0.0f);
    assert(step(0.5f, 0.6f) == 1.0f);

    PASS();
}

void test_trigonometry(void) 
{
    TEST("Sin, Cos, Atan2 (Approx)");

    // NOTE: Using is_near with 0.001f tolerance for polynomial approximations.
    
    // Sin (Known values).
    assert(is_near(sin(0.0f), 0.0f, 0.001f));
    assert(is_near(sin(ZMATH_HALF_PI), 1.0f, 0.001f));
    assert(is_near(sin(ZMATH_PI), 0.0f, 0.001f)); 
    assert(is_near(sin(ZMATH_PI * 1.5f), -1.0f, 0.001f));

    // Cos.
    assert(is_near(cos(0.0f), 1.0f, 0.001f));
    assert(is_near(cos(ZMATH_PI), -1.0f, 0.001f));

    // Atan2.
    assert(is_near(atan2(0.0f, 1.0f), 0.0f, 0.001f)); // 0 deg.
    assert(is_near(atan2(1.0f, 0.0f), ZMATH_HALF_PI, 0.001f)); // 90 deg.

    PASS();
}

void test_vectors(void) 
{
    TEST("Vec2/Vec3 Add, Dot, Cross, Norm");

    // Vec2.
    vec2 v2a = {1.0f, 2.0f};
    vec2 v2b = {3.0f, 4.0f};
    vec2 v2sum = v2_add(v2a, v2b);
    assert(v2sum.x == 4.0f && v2sum.y == 6.0f);
    assert(v2_dot(v2a, v2b) == 11.0f); // 1*3 + 2*4 = 11.

    // Vec3.
    vec3 up = {0.0f, 1.0f, 0.0f};
    vec3 right = {1.0f, 0.0f, 0.0f};
    
    // Cross product (Right x Up = Forward/Z).
    vec3 fwd = v3_cross(right, up);
    assert(is_near(fwd.x, 0.0f, 0.001f));
    assert(is_near(fwd.y, 0.0f, 0.001f));
    assert(is_near(fwd.z, 1.0f, 0.001f));

    // Normalization.
    vec3 long_vec = {10.0f, 0.0f, 0.0f};
    vec3 n = v3_norm(long_vec);
    assert(is_near(n.x, 1.0f, 0.001f));
    
    // Do not check strict == 1.0f. Use is_near.
    assert(is_near(v3_len(n), 1.0f, 0.001f));

    PASS();
}

int main(void) 
{
    printf("=> Running tests (zmath.h, main).\n");

    test_basic_arithmetic();
    test_interpolation();
    test_trigonometry();
    test_vectors();

    printf("=> All tests passed successfully.\n");
    return 0;
}
