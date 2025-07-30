// Copyright 2025 Danny Nguyen
#define BOOST_TEST_MODULE SokobanTests
#include <boost/test/included/unit_test.hpp>
#include "Sokoban.hpp"

BOOST_AUTO_TEST_CASE(test_load_level) {
    SB::Sokoban sokoban("sokoban/level1.lvl");
    BOOST_CHECK_EQUAL(sokoban.width(), 10);
    BOOST_CHECK_EQUAL(sokoban.height(), 10);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().x, 3);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().y, 6);
}

BOOST_AUTO_TEST_CASE(test_move_player) {
    SB::Sokoban sokoban("sokoban/level2.lvl");
    sokoban.movePlayer(SB::Direction::Down);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().y, 6);

    sokoban.movePlayer(SB::Direction::Right);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().x, 9);

    sokoban.movePlayer(SB::Direction::Left);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().x, 8);
}

BOOST_AUTO_TEST_CASE(test_reset_game) {
    SB::Sokoban sokoban("sokoban/level3.lvl");
    sokoban.movePlayer(SB::Direction::Right);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().x, 4);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().y, 8);

    sokoban.reset();
    BOOST_CHECK_EQUAL(sokoban.playerLoc().x, 3);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().y, 8);
}

BOOST_AUTO_TEST_CASE(test_game_win_condition) {
    SB::Sokoban sokoban("sokoban/level1.lvl");
    sokoban.movePlayer(SB::Direction::Right);
    sokoban.movePlayer(SB::Direction::Right);
    sokoban.movePlayer(SB::Direction::Right);
    sokoban.movePlayer(SB::Direction::Right);
    sokoban.movePlayer(SB::Direction::Up);
    sokoban.movePlayer(SB::Direction::Right);
    sokoban.movePlayer(SB::Direction::Down);
    sokoban.movePlayer(SB::Direction::Up);
    sokoban.movePlayer(SB::Direction::Up);
    sokoban.movePlayer(SB::Direction::Up);
    sokoban.movePlayer(SB::Direction::Left);
    sokoban.movePlayer(SB::Direction::Left);
    sokoban.movePlayer(SB::Direction::Left);
    sokoban.movePlayer(SB::Direction::Up);
    BOOST_CHECK(sokoban.isWon());
}

BOOST_AUTO_TEST_CASE(test_invalid_moves) {
    SB::Sokoban sokoban("sokoban/level5.lvl");
    BOOST_CHECK_EQUAL(sokoban.playerLoc().x, 1);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().y, 6);
    sokoban.movePlayer(SB::Direction::Down);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().x, 1);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().y, 6);
}
