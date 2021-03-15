//
//  Brain_Bridge_Tests.cpp
//  iOS_Brain-Framework
//
//  Created by Djordje Jovic on 17/11/2019.
//  Copyright © 2019 Backyard Brains. All rights reserved.
//

#include "Brain_Bridge_Tests.hpp"

#include "../AudioProcessing.cpp"

#ifdef __cplusplus
extern "C" {
#endif

const void brain_test_processAudio(const int16_t* audioData, const int numberOfSamples, const int sampleRate, float *maxAmp, float *maxFreq)
{
//    calculateMaxAmpAndFreq(std::vector<float>(audioData, audioData + numberOfSamples), sampleRate, maxAmp, maxFreq);
}
const void brain_test_processAudio2(const float* audioData, const int numberOfSamples, const int sampleRate, float *maxAmp, float *maxFreq)
{
//    calculateMaxAmpAndFreq(std::vector<float>(audioData, audioData + numberOfSamples), sampleRate, maxAmp, maxFreq);
}

#ifdef __cplusplus
}
#endif
