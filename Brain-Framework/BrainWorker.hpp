//
//  BrainWorker.hpp
//  Brain-Framework
//
//  Created by Djordje Jovic on 14/04/2020.
//  Copyright © 2020 Backyard Brains. All rights reserved.
//

#ifndef BrainWorker_hpp
#define BrainWorker_hpp

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#include "Models/Brain.hpp"
#include "Models/Score.hpp"
#include "Models/ColorType.hpp"
#include "Models/CameraType.hpp"
#include "Models/AudioSpectrum.hpp"
#include "Models/ColorSpace.h"
#include "Core/Semaphore.h"

class BrainWorker {
    
private:
    
    Brain brain;
    Semaphore semaphore;
    
    /// Settings data
    static const int rowsResized = 227;
    static const int colsResized = 227;
    const double pulsePeriod = 0.125;
    const double nStepsPerLoop = 100;
    const double msPerStep = round(pulsePeriod * 1000);

    // Audio spectrum data
    AudioSpectrum spectrum;
    
    /// Simulation functions
    void simulateNextIteration();
    void updateBrain();
    void processVisualInput();
    void processAudioInput();
    void updateMotors();
    
public:

// MARK: - Data
    /// IN data
    int cols = 1920;
    int rows = 1080;
    int distance = 4000;
    uint8_t *videoFrame = NULL;
    std::vector<float> audioData;
    int audioSampleRate = 0;
    ColorSpace colorSpace;
    
    /// OUT data
    double leftTorque = 0;
    double rightTorque = 0;
    float speakerTone = 0;
    
    /// Other data
    bool isRunning = false;
    bool whileLoopIsRunning = false;

// MARK: - Functions interface
    
    ~BrainWorker();
    
    /// Starts brain.
    void start();
    
    /// Stops brain.
    void stop();
    
    /// Set video size parameters.
    /// @param width_ Width of video
    /// @param height_ Height of video
    void setVideoSize(int width_, int height_);
    
    /// Set video color space
    /// @param colorSpace_ Color space of video frames, see `ColorSpace.h`
    void setColorSpace(ColorSpace colorSpace_);
    
    /// Loads and parse brain file.
    /// @param filePath Path to the *.mat file
    /// @return Non zero value indicates to occurred error
    int load(std::string filePath);
    
    /// Calculates score for video input based on selected color.
    /// @param color Red, green or blue color
    /// @param frame Video frame
    /// @param camera Left or right camera
    Score calculateScore(ColorType color, cv::Mat frame, CameraType camera);
    
// MARK: - Out functions
    
    /// Returns neuron `v` values.
    std::vector<double> getNeuronValues();
    
    /// Returns `connectome` values of neurons.
    std::vector<std::vector<double>> getConnectToMe();
    
    /// Returns `da_connectome` values of neurons.
    std::vector<std::vector<std::vector<double>>> getDaConnectToMe();
    
    /// Returns `neuron_contacts` values of neurons.
    std::vector<std::vector<double>> getContacts();
    
    /// Returns x of `neuron_xys` values of neurons.
    std::vector<double> getX();
    
    /// Returns y of `neuron_xys` values of neurons.
    std::vector<double> getY();
    
    /// Returns firing neurons.
    std::vector<bool> getFiringNeurons();
    
    /// Returns `neuron_cols` values of neurons
    std::vector<std::vector<double>> getColors();
    
    /// Returns `vis_prefs` values of neurons
    std::vector<std::vector<std::vector<bool>>> getVisPrefs();
};

#endif /* BrainWorker_hpp */
