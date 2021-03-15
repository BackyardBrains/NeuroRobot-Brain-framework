//
//  Brain.cpp
//  Brain-Framework
//
//  Created by Djordje Jovic on 8/17/19.
//  Copyright © 2019 Backyard Brains. All rights reserved.
//

#include "Brain.hpp"

#include <random>

// MARK:- Implementation

int Brain::load(std::string filePath_, double msPerStep_, double nStepsPerLoop_)
{
    mat_t* matfp = Mat_Open(filePath_.c_str(), MAT_ACC_RDONLY);

    matvar_t* matvar = Mat_VarReadNextInfo(matfp);
    int readError = Mat_VarReadDataAll(matfp, matvar);
    if (readError != 0) { return readError; }
    
    std::cout << "loaded brain: " + filePath_ << std::endl;
    matvar_t* fooMatvar;
    
    // Parse brain data
    fooMatvar = Mat_VarGetStructFieldByName(matvar, "nneurons", 0);
    numberOfNeurons = ((double*)fooMatvar->data)[0];
    fooMatvar = Mat_VarGetStructFieldByName(matvar, "a_init", 0);
    aInit = ((double*)fooMatvar->data)[0];
    fooMatvar = Mat_VarGetStructFieldByName(matvar, "b_init", 0);
    bInit = ((double*)fooMatvar->data)[0];
    fooMatvar = Mat_VarGetStructFieldByName(matvar, "c_init", 0);
    cInit = ((double*)fooMatvar->data)[0];
    fooMatvar = Mat_VarGetStructFieldByName(matvar, "d_init", 0);
    dInit = ((double*)fooMatvar->data)[0];
    fooMatvar = Mat_VarGetStructFieldByName(matvar, "w_init", 0);
    wInit = ((double*)fooMatvar->data)[0];
    
    // Parse neuron data
    neurons = parseNeurons(matvar);
    
    Mat_Close(matfp);
    
    std::random_device rd{};
    std::mt19937 gen{ rd() };
    std::normal_distribution<double> distribution(0.0, 1.0);
    
    for (int i = 0; i < numberOfNeurons; ++i) {
        double randomNumber = distribution(gen);
        
        neurons[i].v = neurons[i].c + 5 * randomNumber;
        neurons[i].u = neurons[i].b * neurons[i].v;
        
        neurons[i].spikesStep = std::vector<double>(msPerStep_, 0);
        neurons[i].iStep = std::vector<double>(msPerStep_, 0);
    }
    
    spikesLoop = std::vector<std::vector<double> >(numberOfNeurons, std::vector<double>(msPerStep_ * nStepsPerLoop_, 0));
    visPrefVals = std::vector<std::vector<double> >(neurons.front().visPref.size(), std::vector<double>(2, 0));
    
    return 0;
}

std::vector<Neuron> Brain::parseNeurons(matvar_t* brainStruct)
{
    std::vector<Neuron> neurons;
    matvar_t* fooMatvar;
    fooMatvar = Mat_VarGetStructFieldByName(brainStruct, "nneurons", 0);
    
    if (fooMatvar != NULL) {
        double numberOfNeurons = ((double*)fooMatvar->data)[0];

        for (int i = 0; i < numberOfNeurons; i++) {
            Neuron neuron;

            fooMatvar = Mat_VarGetStructFieldByName(brainStruct, "a", 0);
            neuron.a = ((double*)fooMatvar->data)[i];

            fooMatvar = Mat_VarGetStructFieldByName(brainStruct, "b", 0);
            neuron.b = ((double*)fooMatvar->data)[i];

            fooMatvar = Mat_VarGetStructFieldByName(brainStruct, "c", 0);
            neuron.c = ((double*)fooMatvar->data)[i];

            fooMatvar = Mat_VarGetStructFieldByName(brainStruct, "d", 0);
            neuron.d = ((double*)fooMatvar->data)[i];

            fooMatvar = Mat_VarGetStructFieldByName(brainStruct, "neuron_xys", 0);
            size_t nRow = fooMatvar->dims[0];
            neuron.x = ((double*)fooMatvar->data)[i];
            neuron.y = ((double*)fooMatvar->data)[nRow + i];

            fooMatvar = Mat_VarGetStructFieldByName(brainStruct, "neuron_contacts", 0);
            for (int j = i; j < fooMatvar->dims[1] * numberOfNeurons; j = j + numberOfNeurons) {
                neuron.contacts.push_back(((double*)fooMatvar->data)[j]);
            }

            fooMatvar = Mat_VarGetStructFieldByName(brainStruct, "connectome", 0);
            for (int j = i; j < fooMatvar->dims[1] * numberOfNeurons; j = j + numberOfNeurons) {
                neuron.connectToMe.push_back(((double*)fooMatvar->data)[j]);
            }

            fooMatvar = Mat_VarGetStructFieldByName(brainStruct, "neuron_cols", 0);
            for (int j = i; j < fooMatvar->dims[1] * numberOfNeurons; j = j + numberOfNeurons) {
                neuron.color.push_back(((double*)fooMatvar->data)[j]);
            }

            fooMatvar = Mat_VarGetStructFieldByName(brainStruct, "audio_prefs", 0);
            if (fooMatvar != NULL) {
                neuron.audioPref = ((double*)fooMatvar->data)[i];
            }

            fooMatvar = Mat_VarGetStructFieldByName(brainStruct, "neuron_tones", 0);
            if (fooMatvar != NULL) {
                neuron.tone = ((double*)fooMatvar->data)[i];
            }

            fooMatvar = Mat_VarGetStructFieldByName(brainStruct, "da_connectome", 0);
            for (int k = i; k < numberOfNeurons * fooMatvar->dims[1]; k = k + numberOfNeurons) {
                std::vector<double> connectToMeVector;
                for (int j = k; j < numberOfNeurons * fooMatvar->dims[1] * fooMatvar->dims[2]; j = j + numberOfNeurons * fooMatvar->dims[1]) {
                    connectToMeVector.push_back(((double*)fooMatvar->data)[j]);
                }
                neuron.daConnecToMe.push_back(connectToMeVector);
            }

            fooMatvar = Mat_VarGetStructFieldByName(brainStruct, "vis_prefs", 0);
            for (int k = i; k < numberOfNeurons * fooMatvar->dims[1]; k = k + numberOfNeurons) {
                std::vector<bool> visPrefsVector;
                for (int j = k; j < numberOfNeurons * fooMatvar->dims[1] * fooMatvar->dims[2]; j = j + numberOfNeurons * fooMatvar->dims[1]) {
                    visPrefsVector.push_back(((bool*)fooMatvar->data)[j]);
                }
                neuron.visPref.push_back(visPrefsVector);
            }

            fooMatvar = Mat_VarGetStructFieldByName(brainStruct, "dist_prefs", 0);
            neuron.distPref = ((double*)fooMatvar->data)[i];

            fooMatvar = Mat_VarGetStructFieldByName(brainStruct, "network_ids", 0);
            neuron.networkId = ((double*)fooMatvar->data)[i];

            fooMatvar = Mat_VarGetStructFieldByName(brainStruct, "da_rew_neurons", 0);
            neuron.daRewNeuron = ((double*)fooMatvar->data)[i];

            fooMatvar = Mat_VarGetStructFieldByName(brainStruct, "bg_neurons", 0);
            neuron.bgNeuron = ((double*)fooMatvar->data)[i];

            neurons.push_back(neuron);
        }
    }

    return neurons;
}
