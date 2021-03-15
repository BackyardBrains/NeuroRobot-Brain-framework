//
//  MathFunctions.hpp
//  Brain-Framework
//
//  Created by Djordje Jovic on 23/12/2019.
//  Copyright © 2019 Backyard Brains. All rights reserved.
//

#ifndef MathFunctions_hpp
#define MathFunctions_hpp

#include <vector>

class MathFunctions {
public:
    static float calculateSD(std::vector<float> v);
    static float mean(std::vector<float> v);
    static double sigmoid(double x, double c, double a);
    
    static int sign(double val);
    
    static std::vector<float> fft(std::vector<float> x);
};

#endif /* MathFunctions_hpp */
