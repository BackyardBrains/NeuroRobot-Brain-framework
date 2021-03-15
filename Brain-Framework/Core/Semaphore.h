//
//  Semaphore.hpp
//  NeuroRobot-Framework
//
//  Created by Djordje Jovic on 14/04/2020.
//  Copyright © 2020 Backyard Brains. All rights reserved.
//

#ifndef Semaphore_hpp
#define Semaphore_hpp

#include <iostream>

#ifdef __APPLE__
    #include <dispatch/dispatch.h>
#else
    #include <semaphore.h>
#endif

class Semaphore {
    
private:
    
    #ifdef __APPLE__
        dispatch_semaphore_t semaphoreMutex;
    #else
        sem_t semaphoreMutex;
    #endif
    
public:
    
    Semaphore();
    ~Semaphore();
    
    /// Block current thread until signal is called.
    void wait();
    
    /// Inform that signal happened.
    void signal();
    
};

#endif /* Semaphore_hpp */
