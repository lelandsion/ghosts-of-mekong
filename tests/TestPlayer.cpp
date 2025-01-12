#include <catch2/catch_test_macros.hpp>
#include "../src/player/Player.h"

TEST_CASE("Player takes damage and loses health", "[Player]") {
// Initialize the player with example parameters
Player player("assets/player/player1.png", {100.f, 200.f}, 200.f, 100);

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