
#include <stdio.h>
#define ZMATH_IMPLEMENTATION
#define ZMATH_SHORT_NAMES
#include "zmath.h"

#define N 16 // Number of samples (Must be small for O(N^2) DFT demo).

int main(void) 
{
    float signal[N];
    float sample_rate = 16.0f; // Hz

    printf("=> Signal Analysis (DFT)\n");

    // We generate the signal: 
    // A mix of 1 Hz wave + 4 Hz wave + constant DC offset.
    printf("Input Signal (Time Domain):\n");
    for (int i = 0; i < N; i++) 
    {
        float t = (float)i / sample_rate;
        signal[i] = 2.0f * sin(TAU * 1.0f * t) + 1.0f * cos(TAU * 4.0f * t);
        printf("  t=%.2fs: %.2f\n", t, signal[i]);
    }

    // We perform the DFT (Discrete Fourier Transform).
    // We calculate Real (re) and Imaginary (im) components for each frequency bin.
    float re_out[N/2 + 1];
    float im_out[N/2 + 1];

    for (int k = 0; k <= N/2; k++) 
    {
        float re = 0.0f;
        float im = 0.0f;
        
        for (int n = 0; n < N; n++) 
        {
            // Euler's Formula: e^(-i*2*pi*k*n/N) = cos(...) - i*sin(...).
            float angle = -TAU * (float)k * (float)n / (float)N;
            re += signal[n] * cos(angle);
            im += signal[n] * sin(angle);
        }

        re_out[k] = re;
        im_out[k] = im;
    }

    // Time to analyze the results (Frequency Domain).
    printf("\nOutput (Frequency Domain):\n");
    printf("Freq(Hz) | Mag   | Phase(rad) | dB\n");
    printf("---------|-------|------------|------\n");

    for (int k = 0; k <= N/2; k++) 
    {
        float freq = (float)k * sample_rate / (float)N;

        // Magnitude = sqrt(re^2 + im^2).
        // We normalize magnitude by dividing by N/2 (except DC).
        float magnitude = sqrt(re_out[k] * re_out[k] + im_out[k] * im_out[k]);
        if (k == 0 || k == N/2) magnitude /= (float)N; 
        else magnitude /= (float)(N/2);

        // Phase = atan2(im, re)
        float phase = atan2(im_out[k], re_out[k]);

        // Decibels = 20 * log10(magnitude).
        // Avoid log(0) with a tiny epsilon.
        float db = 20.0f * log(magnitude + 1e-9f);

        // Filter out near-zero noise for cleaner printing.
        if (magnitude < 0.01f) magnitude = 0.0f;

        printf("%4.1f Hz  | %5.2f | %10.2f | %5.1f\n", freq, magnitude, phase, db);
    }
    
    // Expected Output:
    // 1.0 Hz should have Magnitude approx 2.0
    // 4.0 Hz should have Magnitude approx 1.0
    
    return 0;
}
