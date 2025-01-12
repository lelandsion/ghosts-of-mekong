//
// Created by Leland Sion on 2024-12-04.
//

#ifndef VIETNAMMARINE2_LEVEL1_H
#define VIETNAMMARINE2_LEVEL1_H

#include "Environment.h"


Environment createLevel1() {
    Environment level1;

    // Add platforms for Level 1
    level1.addPlatform({0.f, 550.f}, {800.f, 50.f}); // Ground
    level1.addPlatform({200.f, 400.f}, {150.f, 20.f}); // Mid-level platform
    level1.addPlatform({500.f, 300.f}, {100.f, 20.f}); // Higher platform
    level1.addPlatform({700.f, 200.f}, {50.f, 20.f});  // Small floating platform

    return level1;
}



#endif //VIETNAMMARINE2_LEVEL1_H
