//
//  Brain_Bridge_Tests.hpp
//  iOS_Brain-Framework
//
//  Created by Djordje Jovic on 17/11/2019.
//  Copyright © 2019 Backyard Brains. All rights reserved.
//

#ifndef Brain_Bridge_Tests_hpp
#define Brain_Bridge_Tests_hpp

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

const void brain_test_processAudio(const int16_t* audioData, const int numberOfSamples, const int sampleRate, float *maxAmp, float *maxFreq);
const void brain_test_processAudio2(const float* audioData, const int numberOfSamples, const int sampleRate, float *maxAmp, float *maxFreq);

#ifdef __cplusplus
}
#endif

#endif /* Brain_Bridge_Tests_hpp */
