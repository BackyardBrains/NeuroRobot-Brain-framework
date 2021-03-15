//
//  Semaphore.cpp
//  NeuroRobot-Framework
//
//  Created by Djordje Jovic on 14/04/2020.
//  Copyright © 2020 Backyard Brains. All rights reserved.
//

#include "Semaphore.h"

#ifdef __APPLE__

    Semaphore::Semaphore() {
        semaphoreMutex = dispatch_semaphore_create(0);
    }

    Semaphore::~Semaphore() {
        dispatch_release(semaphoreMutex);
    }
    void Semaphore::wait() {
        dispatch_semaphore_wait(semaphoreMutex, DISPATCH_TIME_FOREVER);
    }

    void Semaphore::signal() {
        dispatch_semaphore_signal(semaphoreMutex);
    }

#else

    Semaphore::Semaphore() {
        sem_init(&semaphoreMutex, 0, 1);
    }

    Semaphore::~Semaphore() {
        sem_destroy(&semaphoreMutex);
    }

    void Semaphore::wait() {
        sem_wait(&semaphoreMutex);
    }

    void Semaphore::signal() {
        sem_post(&semaphoreMutex);
    }

#endif
