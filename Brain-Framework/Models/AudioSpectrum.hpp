//
//  AudioSpectrum.hpp
//  iOS_Brain-Framework
//
//  Created by Djordje Jovic on 12.2.21..
//  Copyright © 2021 Backyard Brains. All rights reserved.
//

#ifndef AudioSpectrum_hpp
#define AudioSpectrum_hpp

#include <iostream>
#include <vector>

class AudioSpectrum {

private:

    /// Obtain index of  given frequency in spectrum
    /// @param value Choosen frequency
    long closestIndex(float value);

public:
    std::vector<float> amplitude;
    std::vector<float> frequency;

    /// Calculate amplitude for given frequency in spectrum
    /// @param frequency Choosen frequency
    float closestAmplitudeForFrequency(float frequency);

    /// Return whether the data is empty
    bool isEmpty();
};

#endif /* AudioSpectrum_hpp */
