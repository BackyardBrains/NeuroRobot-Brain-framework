//
//  MathFunctions.cpp
//  Brain-Framework
//
//  Created by Djordje Jovic on 23/12/2019.
//  Copyright © 2019 Backyard Brains. All rights reserved.
//

#include "MathFunctions.hpp"

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <numeric>

#ifdef __APPLE__
    #include "FFT_Apple.mm"
#endif

float MathFunctions::calculateSD(std::vector<float> v) {
    float mean = MathFunctions::mean(v);
    
    std::vector<float> diff(v.size());
    std::transform(v.begin(), v.end(), diff.begin(), [mean](float x) { return x - mean; });
    float sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    float stdev = sqrt(sq_sum / v.size());
    return stdev;
}

float MathFunctions::mean(std::vector<float> v) {
    float sum = std::accumulate(v.begin(), v.end(), 0.0f);
    if (sum == 0) { return 0; }
    
    float mean = sum / v.size();
    return mean;
}

double MathFunctions::sigmoid(double x, double c, double a) {
    double y = 1 / (1 + exp(-a * (x - c)));
    return y;
}

int MathFunctions::sign(double val) {
    return (0 < val) - (val < 0);
}

std::vector<float> MathFunctions::fft(std::vector<float> x) {
#ifdef __APPLE__
    auto fooData = calculateFFT(x);
    std::vector<float> y = std::vector<float>(fooData, fooData + x.size());
    delete [] fooData;
    return y;
#else
    printf("fft() not implemented for other OS than Apple's");
    return nullptr;
#endif
}
