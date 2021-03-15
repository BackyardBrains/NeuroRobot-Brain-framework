//
//  AudioProcessing.cpp
//  iOS_Brain-Framework
//
//  Created by Djordje Jovic on 17/11/2019.
//  Copyright © 2019 Backyard Brains. All rights reserved.
//

#ifndef AudioProcessing_cpp
#define AudioProcessing_cpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "Math/MathFunctions.hpp"
#include "Models/AudioSpectrum.hpp"

/// Obtains audio spectrum.
/// @param audioData Have to have 2^b samples
/// @param sampleRate Sample rate
static AudioSpectrum getSpectrum(std::vector<float> audioData, int sampleRate)
{
    AudioSpectrum spectrum;

    int log2n = log2f((float)audioData.size());
    int limit = pow(2, log2n);

    if (limit > 0) {
        float fs = (float)sampleRate;

        // Get first 1024 samples, it has to be 2^n.
        std::vector<float> x(audioData.begin(), audioData.begin() + limit);

        // Get spectrum
        std::vector<float> y = MathFunctions::fft(x);
        float n = y.size() / 2 + 1;
        if (y.size()) {

            std::vector<float> pw(n);
            std::vector<float> fx(n);
            float fs_n = fs / n;
            for (int i = 0; i < n; i++) {
                float pw_ = pow(y[i], 2) / n;
                pw[i] = pw_;
                fx[i] = i * fs_n;
            }

            // Convert to Z scores
            float meanPW = MathFunctions::mean(pw);
            float standardDeviation = MathFunctions::calculateSD(pw);
            for (int i = 0; i < n; i++) {
                pw[i] = (pw[i] - meanPW) / standardDeviation;
            }

            spectrum.frequency = fx;
            spectrum.amplitude = pw;
        }
    }
    return spectrum;
}

#endif /* AudioProcessing_cpp */
