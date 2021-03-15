//
//  Neuron.hpp
//  Brain-Framework
//
//  Created by Djordje Jovic on 8/17/19.
//  Copyright © 2019 Backyard Brains. All rights reserved.
//

#ifndef Neuron_hpp
#define Neuron_hpp

#include <stdio.h>
#include <vector>

class Neuron
{
public:
    
    double a;
    double b;
    double c;
    double d;
    double v;
    double u;
    
    double x;
    double y;
    
    std::vector<double> contacts;
    std::vector<double> connectToMe;
    std::vector<double> color;
    std::vector<std::vector<double>> daConnecToMe;
    std::vector<std::vector<bool>> visPref;
    
    double distPref;
    double networkId;
    double daRewNeuron;
    double bgNeuron;
    double tone;
    double audioPref;
    
    std::vector<double> spikesStep;
    std::vector<double> iStep;
    double visI = 0;
    double distI = 0;
    double audioI = 0;
    double I = 0;
    
    bool firing = false;
};

#endif /* Neuron_hpp */
