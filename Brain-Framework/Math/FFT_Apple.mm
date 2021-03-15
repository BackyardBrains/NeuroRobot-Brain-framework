//
//  FFT_Apple.m
//  iOS_Brain-Framework
//
//  Created by Djordje Jovic on 16/11/2019.
//  Copyright © 2019 Backyard Brains. All rights reserved.
//

#ifndef FFT_Apple_m
#define FFT_Apple_m

#ifdef __APPLE__

#import <Accelerate/Accelerate.h>
#include <iostream>
#include <vector>

#include <math.h>
#include <float.h>

/// Calculate FFT for one channel and put result in FFTMagnitude array. We take input signal from mExternalRingBuffer it calculates FFT for last arrived signal data.
/// @param x_ audio data
static float * calculateFFT(std::vector<float> x_)
{
    uint32_t log2n = log2f((float)x_.size() * 2);
    if (pow(2, log2n) < x_.size() * 2) {
        log2n++;
    }
    UInt32 lengthOfWindow = pow(2, log2n);
    
    std::vector<float> x = std::vector<float>(lengthOfWindow, 0);
    
    // Make gap for imag numbers
    for (int i = 0; i < x_.size(); i++) {
        x[i * 2] = x_[i];
    }
    
    float * data = x.data();
    COMPLEX_SPLIT AComplexSplit;
    UInt32 dLengthOfFFTData = lengthOfWindow / 2;

    // Allocate memory
    float * FFTMagnitude = new float[dLengthOfFFTData];
    AComplexSplit.realp = (float*) malloc(sizeof(float) * dLengthOfFFTData);
    AComplexSplit.imagp = (float*) malloc(sizeof(float) * dLengthOfFFTData);

    // Make fft setup
    FFTSetup fftSetup = vDSP_create_fftsetup(log2n, FFT_RADIX2);

    // Carry out a Forward FFT transform
    vDSP_ctoz((COMPLEX *) data, 2, &AComplexSplit, 1, dLengthOfFFTData);
    vDSP_fft_zrip(fftSetup, &AComplexSplit, 1, log2n, FFT_FORWARD);

    // Calculate DC component
    FFTMagnitude[0] = sqrtf(AComplexSplit.realp[0] * AComplexSplit.realp[0]);

    // Calculate magnitude for all freq.
    for (int i = 1; i < dLengthOfFFTData; i++){
        FFTMagnitude[i] = sqrtf(AComplexSplit.realp[i] * AComplexSplit.realp[i] + AComplexSplit.imagp[i] * AComplexSplit.imagp[i]);
        if (isnan(FFTMagnitude[i])) {
            printf("NaN");
        }
        if (FFTMagnitude[i] != FFTMagnitude[i]) {
            printf("NaN");
        }
        if (FFTMagnitude[i] == INFINITY) {
            printf("INFINITY");
        }
        if (FFTMagnitude[i] > FLT_MAX) {
            printf("INFINITY");
        }
    }

    // Release memory
    vDSP_destroy_fftsetup(fftSetup);
    free(AComplexSplit.realp);
    free(AComplexSplit.imagp);
    
    return FFTMagnitude;
}
#endif

#endif /* FFT_Apple_m */
