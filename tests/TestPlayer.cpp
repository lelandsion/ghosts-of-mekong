//
// Created by Leland Sion on 2024-10-16.
//


#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/player/Player.h"

TEST_CASE("Player takes damage and loses health", "[Player]") {
Player player;
player.setHealth(100);

SECTION("Taking damage reduces health") {
player.applyDamage(30);
REQUIRE(player.getHealth() == 70);
}

SECTION("Player health cannot go below zero") {
player.applyDamage(150);
REQUIRE(player.getHealth() == 0);
}

SECTION("Player can be healed back to max health") {
player.applyDamage(50);
player.setHealth(100);
REQUIRE(player.getHealth() == 100);
}
}
