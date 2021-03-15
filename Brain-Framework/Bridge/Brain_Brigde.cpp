//
//  Brain_Brigde.cpp
//  Brain-Framework
//
//  Created by Djordje Jovic on 8/27/19.
//  Copyright © 2019 Backyard Brains. All rights reserved.
//

#include "Brain_Brigde.hpp"
#include "../BrainWorker.hpp"
#include "../AudioProcessing.cpp"
#include "../Models/ColorSpace.h"
#include <thread>

#ifdef __cplusplus
extern "C" {
#endif

const void* brain_Init(int colorSpace)
{
    BrainWorker* brain = new BrainWorker();
    brain->setColorSpace(ColorSpace(colorSpace));
    return brain;
}

const void brain_setVideoSize(const void* object, int width_, int height_)
{
    BrainWorker* brainObject = (BrainWorker*)object;
    brainObject->setVideoSize(width_, height_);
}

const int brain_load(const void* object, char* pathToMatFile_)
{
    BrainWorker* brainObject = (BrainWorker*)object;
    return brainObject->load(std::string(pathToMatFile_));
}

const void brain_start(const void* object)
{
    BrainWorker* brainObject = (BrainWorker*)object;
    brainObject->start();
}

const void brain_stop(const void* object)
{
    BrainWorker* brainObject = (BrainWorker*)object;
    brainObject->stop();
}

const void brain_deinit(const void* object)
{
    BrainWorker* brainObject = (BrainWorker*)object;
    if (brainObject->isRunning) {
        brainObject->stop();
    }
    
    delete brainObject;
}

const void brain_setDistance(const void* object, int distance)
{
    BrainWorker* brainObject = (BrainWorker*)object;
    brainObject->distance = distance;
}

const void brain_setVideo(const void* object, const uint8_t* videoFrame)
{
    BrainWorker* brainObject = (BrainWorker*)object;
    memcpy(brainObject->videoFrame, videoFrame, brainObject->cols * brainObject->rows * 3);
}

const void brain_setAudio(const void* object, const float* audioData, const int numberOfSamples, const int sampleRate)
{
    BrainWorker* brainObject = (BrainWorker*)object;
    brainObject->audioSampleRate = sampleRate;
    brainObject->audioData = std::vector<float>(audioData, audioData + numberOfSamples);
}

const double brain_getRightTorque(const void* object)
{
    BrainWorker* brainObject = (BrainWorker*)object;
    return brainObject->rightTorque;
}

const double brain_getLeftTorque(const void* object)
{
    BrainWorker* brainObject = (BrainWorker*)object;
    return brainObject->leftTorque;
}

const float brain_getSpeakerTone(const void* object)
{
    BrainWorker* brainObject = (BrainWorker*)object;
    return brainObject->speakerTone;
}

const double* brain_getNeuronValues(const void* object, size_t *numberOfNeurons)
{
    BrainWorker* brainObject = (BrainWorker*)object;
    
    auto neuronValuesVector = brainObject->getNeuronValues();
    
    *numberOfNeurons = neuronValuesVector.size();
    double* neuronValues = new double[*numberOfNeurons];
    
    for (int i = 0; i < *numberOfNeurons; i++) {
        neuronValues[i] = neuronValuesVector[i];
    }
    
    return neuronValues;
}

const double** brain_getConnectToMe(const void* object, size_t *numberOfNeurons)
{
    BrainWorker* brainObject = (BrainWorker*)object;
    
    auto connectToMeVector = brainObject->getConnectToMe();
    
    *numberOfNeurons = connectToMeVector.size();
    const double** connectToMe = new const double*[*numberOfNeurons];
    
    for (int i = 0; i < *numberOfNeurons; i++) {
        auto neuron = connectToMeVector[i];
        auto foo = new double[neuron.size()];
        
        for (int j = 0; j < neuron.size(); j++) {
            auto value = neuron[j];
            foo[j] = value;
        }
        connectToMe[i] = foo;
    }
    
    return connectToMe;
}

const double*** brain_getDaConnectToMe(const void* object, size_t *numberOfNeurons, size_t *numberOfParams1, size_t *numberOfParams2)
{
    BrainWorker* brainObject = (BrainWorker*)object;
    
    auto valuesVector = brainObject->getDaConnectToMe();
    
    *numberOfNeurons = valuesVector.size();
    *numberOfParams1 = valuesVector.front().size();
    *numberOfParams2 = valuesVector.front().front().size();
    const double*** valuesMatrix = new const double**[*numberOfNeurons];
    
    for (int i = 0; i < *numberOfNeurons; i++) {
        auto neuron = valuesVector[i];
        const double** foo1 = new const double*[neuron.size()];
        
        for (int j = 0; j < neuron.size(); j++) {
            auto visPref = neuron[j];
            auto foo2 = new double[visPref.size()];
            
            for (int k = 0; k < visPref.size(); k++) {
                auto value = visPref[k];
                foo2[k] = value;
            }
            foo1[j] = foo2;
        }
        valuesMatrix[i] = foo1;
    }
    
    return valuesMatrix;
}

const double** brain_getContacts(const void* object, size_t *numberOfNeurons, size_t *numberOfConnections)
{
    BrainWorker* brainObject = (BrainWorker*)object;
    
    auto contactsVector = brainObject->getContacts();
    
    *numberOfNeurons = contactsVector.size();
    *numberOfConnections = contactsVector.front().size();
    const double** contacts = new const double*[*numberOfNeurons];
    
    for (int i = 0; i < *numberOfNeurons; i++) {
        auto neuron = contactsVector[i];
        auto foo = new double[neuron.size()];
        
        for (int j = 0; j < neuron.size(); j++) {
            auto value = neuron[j];
            foo[j] = value;
        }
        contacts[i] = foo;
    }
    
    return contacts;
}

const double* brain_getX(const void* object, size_t *numberOfNeurons)
{
    BrainWorker* brainObject = (BrainWorker*)object;
    
    auto neuronValuesVector = brainObject->getX();
    
    *numberOfNeurons = neuronValuesVector.size();
    double* neuronValues = new double[*numberOfNeurons];
    
    for (int i = 0; i < *numberOfNeurons; i++) {
        neuronValues[i] = neuronValuesVector[i];
    }
    
    return neuronValues;
}

const double* brain_getY(const void* object, size_t *numberOfNeurons)
{
    BrainWorker* brainObject = (BrainWorker*)object;
    
    auto neuronValuesVector = brainObject->getY();
    
    *numberOfNeurons = neuronValuesVector.size();
    double* neuronValues = new double[*numberOfNeurons];
    
    for (int i = 0; i < *numberOfNeurons; i++) {
        neuronValues[i] = neuronValuesVector[i];
    }
    
    return neuronValues;
}

const bool* brain_getFiringNeurons(const void* object, size_t *numberOfNeurons)
{
    BrainWorker* brainObject = (BrainWorker*)object;
    
    auto neuronValuesVector = brainObject->getFiringNeurons();
    
    *numberOfNeurons = neuronValuesVector.size();
    bool* neuronValues = new bool[*numberOfNeurons];
    
    for (int i = 0; i < *numberOfNeurons; i++) {
        neuronValues[i] = neuronValuesVector[i];
    }
    
    return neuronValues;
}

const double** brain_getColors(const void* object, size_t *numberOfNeurons, size_t *numberOfColors)
{
    BrainWorker* brainObject = (BrainWorker*)object;
    
    auto valuesVector = brainObject->getColors();
    
    *numberOfNeurons = valuesVector.size();
    *numberOfColors = valuesVector.front().size();
    const double** colors = new const double*[*numberOfNeurons];
    
    for (int i = 0; i < *numberOfNeurons; i++) {
        auto neuron = valuesVector[i];
        auto foo = new double[neuron.size()];
        
        for (int j = 0; j < neuron.size(); j++) {
            auto value = neuron[j];
            foo[j] = value;
        }
        colors[i] = foo;
    }
    
    return colors;
}

const bool*** brain_getVisPrefs(const void* object, size_t *numberOfNeurons, size_t *numberOfParams, size_t *numberOfCams)
{
    BrainWorker* brainObject = (BrainWorker*)object;
    
    auto valuesVector = brainObject->getVisPrefs();
    
    *numberOfNeurons = valuesVector.size();
    *numberOfParams = valuesVector.front().size();
    *numberOfCams = valuesVector.front().front().size();
    const bool*** visPrefs = new const bool**[*numberOfNeurons];
    
    for (int i = 0; i < *numberOfNeurons; i++) {
        auto neuron = valuesVector[i];
        const bool** foo1 = new const bool*[neuron.size()];
        
        for (int j = 0; j < neuron.size(); j++) {
            auto visPref = neuron[j];
            auto foo2 = new bool[visPref.size()];
            
            for (int k = 0; k < visPref.size(); k++) {
                auto value = visPref[k];
                foo2[k] = value;
            }
            foo1[j] = foo2;
        }
        visPrefs[i] = foo1;
    }
    
    return visPrefs;
}

/// Helpers
const void brain_getSpectrum(const int16_t* audioData, const int numberOfSamples, int sampleRate, float *amplitude, float *frequency, int *count) {

    AudioSpectrum spectrum = getSpectrum(std::vector<float>(audioData, audioData + numberOfSamples), sampleRate);

    *count = (int)spectrum.amplitude.size();
    std::memcpy(amplitude, spectrum.amplitude.data(), *count * sizeof(float));
    std::memcpy(frequency, spectrum.frequency.data(), *count * sizeof(float));
}

#ifdef __cplusplus
}
#endif
