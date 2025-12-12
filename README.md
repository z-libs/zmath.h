# zmath.h

`zmath.h` is a zero-dependency, header-only math library for C and C++ projects. Unlike the standard `<math.h>`, which relies on linking against the system's `libm` and varies in implementation across platforms, `zmath.h` provides a consistent, software-based implementation of essential mathematical functions.

It is designed for **Game Development**, **Embedded Systems**, and **OS Development** where standard libraries might be heavy, unavailable, or slow (also for the rest of my libraries, I dislike dependencies). It includes built-in support for vector math (`vec2`, `vec3`) and fast approximate trigonometry.

## Features

* **Zero Dependencies**: Does not require `libc`, `libm`, or `<math.h>`. Pure C code.
* **Deterministic**: Software implementations ensure consistent results across different compilers and architectures.
* **Game Ready**: Includes vector math (`vec2`, `vec3`, dot, cross, normalization) out of the box.
* **Fast Approximations**: Uses Minimax polynomials for Trigonometry and fast bit-hacks for inverse square roots.
* **Type Safe**: Standard `float` interfaces compatible with C and C++.
* **Header Only**: No linking required. Just drop it in.
* **Short Names**: Optional shorthand macros (e.g., `sin`, `lerp`, `vec3`) to make code readable.

## Installation

1.  Copy `zmath.h` to your project's include folder.
2.  Define `ZMATH_IMPLEMENTATION` in **one** C or C++ file to instantiate the functions.

## Usage: C

To use the library, simply include it. If you want a cleaner API (without the `zmath_` prefix), define `ZMATH_SHORT_NAMES`.

```c
#include <stdio.h>

#define ZMATH_IMPLEMENTATION
#define ZMATH_SHORT_NAMES
#include "zmath.h"

int main(void) 
{
    // Basic arithmetic.
    float val = -50.5f;
    printf("Abs: %.2f\n", abs(val)); // zmath_abs

    // Trigonometry (minimax approximation).
    float rad = deg2rad(45.0f);
    printf("Sin(45): %.4f\n", sin(rad));

    // Vector math.
    vec2 pos = {10.0f, 20.0f};
    vec2 dir = {1.0f, 0.0f};
    
    // pos + dir * 5.0
    vec2 final_pos = v2_add(pos, v2_scale(dir, 5.0f));
    
    printf("New Pos: {%.1f, %.1f}\n", final_pos.x, final_pos.y);

    return 0;
}
```

## Usage: C++

`zmath.h` is fully compatible with C++. It uses `extern "C"` internally to ensure proper linkage. It does not introduce a wrapper class like other libraries such as `zvec.h` (yet), but it works seamlessly as a global utility library.

```cpp
#include <iostream>

#define ZMATH_IMPLEMENTATION
#define ZMATH_SHORT_NAMES
#include "zmath.h"

int main() 
{
    // Linear interpolation.
    float start = 0.0f;
    float end = 100.0f;
    float val = lerp(start, end, 0.5f); // Result: 50.0

    // Vector logic.
    vec3 forward = {0, 0, 1};
    vec3 up = {0, 1, 0};
    vec3 right = v3_cross(up, forward);

    std::cout << "Right Vector X: " << right.x << "\n";
    
    // Remapping values.
    float opacity = remap(0.0f, 255.0f, 0.0f, 1.0f, 128.0f);
    
    return 0;
}
```

## Configuration

You can configure the library behavior by defining specific macros **before** including the header.

| Macro | Description |
| :--- | :--- |
| `ZMATH_IMPLEMENTATION` | Instantiates the function definitions. Must be done in exactly one file. |
| `ZMATH_STATIC` | Marks all functions as `static`, making them private to the translation unit. |
| `ZMATH_SHORT_NAMES` | Aliases functions like `zmath_sin` to `sin`, `zmath_lerp` to `lerp`, etc. |

## API Reference

The library is organized into "Tiers" of complexity. By default, all functions are prefixed with `zmath_` to avoid namespace pollution. If `ZMATH_SHORT_NAMES` is defined, the aliases in parentheses are available.

**Logic & Comparison**

| Function | Short Name | Description |
| :--- | :--- | :--- |
| `zmath_is_near(a, b, tol)` | `is_near` | Returns true if `abs(a-b) <= tol`. |
| `zmath_isnan(x)` | `isnan` | Checks if `x` is NaN using bitwise comparison. |
| `zmath_isinf(x)` | `isinf` | Checks if `x` is Infinity using bitwise comparison. |

**Interpolation**

| Function | Short Name | Description |
| :--- | :--- | :--- |
| `zmath_lerp(a, b, t)` | `lerp` | Linear interpolation: `(1-t)*a + t*b`. |
| `zmath_inv_lerp(a, b, v)` | `inv_lerp` | Returns the `t` value that produces `v` between `a` and `b`. |
| `zmath_remap(...)` | `remap` | Remaps a value from one range `[iMin, iMax]` to another `[oMin, oMax]`. |
| `zmath_step(edge, x)` | `step` | Returns 0.0 if `x < edge`, else 1.0. |
| `zmath_smoothstep(e0, e1, x)` | `smoothstep` | Hermite interpolation between edges (standard GLSL implementation). |
| `zmath_smootherstep(e0, e1, x)`| `smootherstep`| Improved Perlin interpolation (C2 continuous). |

**Basic Arithmetic**

| Function | Short Name | Description |
| :--- | :--- | :--- |
| `zmath_abs(x)` | `abs` | Absolute value (bitwise, clears sign bit). |
| `zmath_min(a, b)` | `min` | Returns the smaller of two floats. |
| `zmath_max(a, b)` | `max` | Returns the larger of two floats. |
| `zmath_clamp(x, min, max)` | `clamp` | Constrains `x` between `min` and `max`. |
| `zmath_sign(x)` | `sign` | Returns 1.0, -1.0, or 0.0 based on sign. |
| `zmath_copysign(x, y)` | `copysign` | Returns `x` with the sign bit of `y`. |

**Rounding & Modulo**

| Function | Short Name | Description |
| :--- | :--- | :--- |
| `zmath_floor(x)` | `floor` | Rounds down to nearest integer. |
| `zmath_ceil(x)` | `ceil` | Rounds up to nearest integer. |
| `zmath_round(x)` | `round` | Rounds to nearest integer (0.5 rounds away from zero). |
| `zmath_fract(x)` | `fract` | Returns the fractional part: `x - floor(x)`. |
| `zmath_fmod(x, y)` | `fmod` | Standard C modulo (truncates, sign follows dividend). |
| `zmath_mod(x, y)` | `mod` | Euclidean modulo (wraps, sign follows divisor). Best for games. |

**Power & Roots**

| Function | Short Name | Description |
| :--- | :--- | :--- |
| `zmath_sqrt(x)` | `sqrt` | Square root (Newton-Raphson refinement of invsqrt). |
| `zmath_invsqrt(x)` | `invsqrt` | Fast Inverse Square Root (Quake III algorithm). |
| `zmath_hypot(x, y)` | `hypot` | Robust calculation of `sqrt(x*x + y*y)` avoiding overflow. |
| `zmath_log(x)` | `log` | Natural logarithm (Pade approximation). |
| `zmath_log2(x)` | `log2` | Base-2 logarithm. |
| `zmath_pow(x, y)` | `pow` | Power function: `exp(y * log(x))`. |
| `zmath_exp(x)` | `exp` | Base-e exponential function. |

**Trigonometry**

| Function | Short Name | Description |
| :--- | :--- | :--- |
| `zmath_sin(x)` | `sin` | Sine (Minimax polynomial, valid for full range). |
| `zmath_cos(x)` | `cos` | Cosine. |
| `zmath_tan(x)` | `tan` | Tangent (`sin/cos`). |
| `zmath_atan(x)` | `atan` | Arctangent. |
| `zmath_atan2(y, x)` | `atan2` | 2-argument Arctangent (handles quadrants). |
| `zmath_asin(x)` | `asin` | Arcsine. |
| `zmath_acos(x)` | `acos` | Arccosine. |
| `zmath_deg2rad(deg)` | `deg2rad` | Converts degrees to radians. |
| `zmath_rad2deg(rad)` | `rad2deg` | Converts radians to degrees. |

**Vector Math**

Included structs: `zvec2` (`{x,y}`), `zvec3` (`{x,y,z}`).

| Function | Short Name | Description |
| :--- | :--- | :--- |
| `zmath_v2_add(a, b)` | `v2_add` | Adds two 2D vectors. |
| `zmath_v2_sub(a, b)` | `v2_sub` | Subtracts vector `b` from `a`. |
| `zmath_v2_scale(v, s)` | `v2_scale` | Multiplies vector components by scalar `s`. |
| `zmath_v2_dot(a, b)` | `v2_dot` | Dot product. |
| `zmath_v2_len(v)` | `v2_len` | Magnitude (length) of the vector. |
| `zmath_v2_norm(v)` | `v2_norm` | Returns a normalized (unit length) vector. |
| `zmath_v3_cross(a, b)` | `v3_cross` | Cross product of two 3D vectors. |

*(Note: `zvec3` functions follow the same naming convention: `v3_add`, `v3_dot`, etc.)*

## Notes on Short Names

When `ZMATH_SHORT_NAMES` is defined, `zmath.h` exposes common names like `sin`, `cos`, `floor`, and `sqrt`. 

* **Conflict Warning**: These names will conflict if you also include `<math.h>` in the same file. 
* **Resolution**: Either do not include `<math.h>`, or do not define `ZMATH_SHORT_NAMES` and use the prefixed versions (`zmath_sin`, etc.).
