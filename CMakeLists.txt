cmake_minimum_required(VERSION 3.14)

# Set project name and C++ standard
project(VietnamMarine2)
set(CMAKE_CXX_STANDARD 17)

# Specify SFML directory (update this path if necessary)
set(SFML_DIR "/opt/homebrew/Cellar/sfml/2.6.2/lib/cmake/SFML")

# Add vcpkg toolchain
set(CMAKE_TOOLCHAIN_FILE "/Users/lelandsion/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Find SFML package
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

# Find Catch2
find_package(Catch2 REQUIRED)

# Include directories for SFML and your project
include_directories(
        "/opt/homebrew/include"  # Homebrew symlinked include path
        ${CMAKE_SOURCE_DIR}/src  # Include your source files
        ${CMAKE_SOURCE_DIR}/include  # Include headers
)

# Add project source files
file(GLOB_RECURSE PROJECT_SOURCES
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/src/*.h
        ${CMAKE_SOURCE_DIR}/include/*.cpp
        ${CMAKE_SOURCE_DIR}/include/*.h
)

# Main executable
add_executable(VietnamMarine2 ${PROJECT_SOURCES}
        include/Environment.cpp
        include/Environment.h
        include/Platform.cpp
        include/Platform.h)
target_link_libraries(VietnamMarine2 sfml-graphics sfml-audio sfml-system)

# Add test files
set(TEST_SOURCES ${CMAKE_SOURCE_DIR}/tests/TestPlayer.cpp
        tests/TestLevel.h
        tests/test_main.cpp
        levels/Level1.h)

# Create test executable
add_executable(VietnamMarine2Tests ${TEST_SOURCES})
target_link_libraries(VietnamMarine2Tests PRIVATE Catch2::Catch2 Catch2::Catch2WithMain sfml-graphics sfml-audio sfml-system)
add_executable(TestEnvironment
        # Test files
        tests/test_main.cpp

        # Player-related files
        src/player/Player.cpp
        src/player/PlayerEnums.h

        # Enemy-related files
        src/enemy/Enemy.cpp

        # Environment and platform
        include/Environment.cpp
        include/Environment.h
        include/Platform.cpp
        include/Platform.h

        # Weapon-related files
        src/weapon/Weapon.cpp
        src/weapon/Weapon.h
        src/weapon/WeaponEnums.h
        src/weapon/Projectile.cpp
        src/weapon/Projectile.h
        src/weapon/MeleeWeapon.cpp
        src/weapon/MeleeWeapon.h
        src/weapon/LaserWeapon.cpp
        src/weapon/LaserWeapon.h
        src/weapon/SniperWeapon.cpp
        src/weapon/SniperWeapon.h
        src/weapon/ShotgunWeapon.cpp
        src/weapon/ShotgunWeapon.h

        # Status effects
        src/status_effect/StatusEffect.cpp
        src/status_effect/StatusEffect.h


        # GameObject base
        include/GameObject.cpp
        include/GameObject.h

        # Levels
        levels/Level1.h

        # Utilities or additional files
        src/powerup/PowerUpTypeEnums.h
        include/DeathType.h
        include/CollisionManager.cpp
        include/CollisionManager.h
        include/Animation.cpp
        include/Animation.h
)
target_link_libraries(TestEnvironment sfml-graphics sfml-audio sfml-system)


# Enable testing
enable_testing()