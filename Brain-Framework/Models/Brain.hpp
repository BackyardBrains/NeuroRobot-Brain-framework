//
//  Brain.hpp
//  Brain-Framework
//
//  Created by Djordje Jovic on 8/17/19.
//  Copyright © 2019 Backyard Brains. All rights reserved.
//

#ifndef Brain_hpp
#define Brain_hpp

#include <iostream>
#include <vector>
#include <matio.h>

#include "Neuron.hpp"

class Brain {
private:
    
    std::vector<Neuron> parseNeurons(matvar_t* brainStruct);
    
public:
    
    double numberOfNeurons;
    double aInit;
    double bInit;
    double cInit;
    double dInit;
    double wInit;
    
    std::vector<std::vector<double>> spikesLoop;
    std::vector<std::vector<double>> visPrefVals;

    std::vector<Neuron> neurons;
    
    /// Loads brain data from given path
    /// @param filePath_ Path to *.mat file
    /// @param msPerStep msPerStep
    /// @param nStepsPerLoop nStepsPerLoop
    /// @return Non zero value indicates to occurred error
    int load(std::string filePath_, double msPerStep, double nStepsPerLoop);
};

#endif /* Brain_hpp */
