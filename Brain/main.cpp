//
//  main.cpp
//  Brain
//
//  Created by Djordje Jovic on 8/17/19.
//  Copyright © 2019 Backyard Brains. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "../Brain-Framework/BrainWorker.hpp"
#include "../Brain-Framework/AudioProcessing.cpp"

void testAudioProcessing() {
    std::vector<float> data = {1000, 2};
    float maxAmp = 0;
    float maxFreq = 0;
    
//    calculateMaxAmpAndFreq(data, &maxAmp, &maxFreq);
}

void testBrain() {
//    int error = 0;
//        Brain *brain = new Brain("/Data/Developing/BYB/rak-github/NeuroRobot/Matlab/Brains/Adan.mat", &error);
//
//        //////
//        // TEST 1
//    //    brain->rows = 3;
//    //    brain->cols = 4;
//    //    brain->rowsResized = 3;
//    //    brain->colsResized = 4;
//    //    std::ifstream bigFile("/Data/Developing/BYB/Neurorobot/Brain-Framework/Brain/test2.dat");
//
//        // TEST 2
//        std::ifstream bigFile("/Data/Developing/BYB/Neurorobot/Brain-Framework/Brain/test.dat");
//
//        //////
//
//        size_t videoFrameSize = (brain->rows * brain->cols * 3); //720 * 1280 * 3
//        uint8_t *videoFrame = new uint8_t[videoFrameSize + 1];
//        size_t bufferSize = videoFrameSize * 4;
//        std::unique_ptr<char[]> buffer(new char[bufferSize]);
//
//        while (bigFile)
//        {
//            bigFile.read(buffer.get(), bufferSize);
//
//            int number = 0;
//            int counter = 0;
//            for (int i = 0; i < bufferSize; i++) {
//
//                if (buffer.get()[i] == ',' || buffer.get()[i] == 10) {
//                    videoFrame[counter++] = number;
//                    number = 0;
//                } else {
//                    number = number * 10 + (int)buffer.get()[i] - 48;
//                }
//            }
//
//    //        for (int i = 0; i < videoFrameSize; i++) {
//    //            std::cout << (int)videoFrame[i] << std::endl;
//    //        }
//
//            brain->videoFrame = new uint8_t[videoFrameSize + 1];
//            memcpy(brain->videoFrame, videoFrame, counter);
//        }
//
//        if (error == 0) {
//            brain->start();
//            while(true) {}
//        }
}
int main(int argc, const char * argv[]) {
    testAudioProcessing();
    return 0;
}
