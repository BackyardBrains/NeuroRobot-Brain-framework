//
//  AudioSpectrum.cpp
//  Brain-Framework
//
//  Created by Djordje Jovic on 12.2.21..
//  Copyright © 2021 Backyard Brains. All rights reserved.
//

#include "AudioSpectrum.hpp"

long AudioSpectrum::closestIndex(float value) {
    auto const it = std::lower_bound(frequency.begin(), frequency.end(), value) - frequency.begin();
    
    // Take 5 values around current index and do fine tuning
    long index = it;
    long lowerIndex = index - 2;
    long upperIndex = index + 2;
    
    // If the lowerIndex is negative
    while (lowerIndex < 0) {
        lowerIndex = it + 1;
    }
    
    // If the upperIndex is beyond array's size
    while (upperIndex > frequency.size() - 1) {
        upperIndex = it - 1;
    }
    
    // Do fine tuning
    // Start with lowerIndex + 1 and do 4 compares with 5 numbers
    float lastValue = std::numeric_limits<float>::max();
    for (long i = lowerIndex + 1; i < upperIndex; i++) {
        
        float valueBehind = abs(frequency[i - 1] - value);
        float valueCurrent = abs(frequency[1] - value);
        
        if (valueBehind < valueCurrent && valueBehind < lastValue) {
            index = i - 1;
            lastValue = valueBehind;
        }
    }

    return index;
}

float AudioSpectrum::closestAmplitudeForFrequency(float frequency) {
    if (isEmpty()) { return -1; }

    long indexOfNearest = closestIndex(frequency);
    float amplitudeForIndex = amplitude[indexOfNearest];
    return amplitudeForIndex;
}

bool AudioSpectrum::isEmpty() {
    if (amplitude.size() > 0 && frequency.size() > 0) {
        return false;
    } else {
        return true;
    }
}
