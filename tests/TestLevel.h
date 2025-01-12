//
// Created by Leland Sion on 2024-12-04.
//

// TODO:
// implement the cpp file to include special behavior for ceratin levels
// maybe after completing the game create a bonus gamemode where your goal is to survive as long as possible and a
// random enemy from any part of the game will spawn every 20 seconds or smth maybe also a random benefit and
// a random map and random weapon

#ifndef VIETNAMMARINE2_TESTLEVEL_H
#define VIETNAMMARINE2_TESTLEVEL_H

#include "../include/Environment.h"

Environment createTestLevel() {
    Environment testLevel;

    // Add platforms for Level 1
    testLevel.addPlatform({0.f, 400.f}, "../assets/level/test_platform.png", {0.f, 400.f, 1000.f, 100.f}); // Ground
    testLevel.addPlatform({1.f, 50.f}, "../assets/level/test_platform.png", {1.f, 80.f, 576.f, 12.f}); // Small platform
    testLevel.addPlatform({580.f, 360.f}, "../assets/level/test_platform.png", {600.f, 370.f, 500.f, 12.f}); // Another platform
    testLevel.addPlatform({1000.f, 300.f}, "../assets/level/test_platform.png", {1000.f, 320.f, 500.f, 12.f}); // Another platform
    testLevel.addPlatform({1500.f, 230.f}, "../assets/level/test_platform.png", {1500.f, 260.f, 1000.f, 12.f}); // Another platform
    testLevel.addPlatform({800.f, 230.f}, "../assets/level/smaller_test_platform.png", {800.f, 260.f, 190.f, 12.f}); // Another platform
    testLevel.addPlatform({700.f, 160.f}, "../assets/level/smaller_test_platform.png", {700.f, 200.f, 190.f, 12.f}); // Another platform
    testLevel.addPlatform({600.f, 100.f}, "../assets/level/smaller_test_platform.png", {600.f, 140.f, 190.f, 12.f}); // Another platform
    testLevel.addPlatform({2000.f, 230.f}, "../assets/level/test_platform.png", {2000.f, 260.f, 1000.f, 12.f}); // Another platform
    testLevel.addPlatform({2500.f, 160.f}, "../assets/level/test_platform.png", {2500.f, 200.f, 1000.f, 12.f}); // Another platform
    testLevel.addPlatform({3000.f, 100.f}, "../assets/level/test_platform.png", {3000.f, 140.f, 1000.f, 12.f}); // Another platform

    return testLevel;
}



#endif //VIETNAMMARINE2_TESTLEVEL_H
