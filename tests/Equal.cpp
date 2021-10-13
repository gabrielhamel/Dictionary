/**
 * @file Equal.cpp
 * @author Gabriel Hamel (gabriel.hamel.pro@gmail.com)
 * @brief
 * @version 1.0
 * @date 2021-06-13
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <gtest/gtest.h>

#include "Fixtures.hpp"

class SearchWithoutError : public CharDictionaryFixture { };

TEST_F(SearchWithoutError, BasicTest) {

    // Valid words
    EXPECT_EQ(this->dictionary.hasWord("Hello"), true);
    EXPECT_EQ(this->dictionary.hasWord("Hell"), false);

    EXPECT_EQ(this->dictionary.hasWord("Bonjour"), true);
    EXPECT_EQ(this->dictionary.hasWord("Bonsoir"), true);

    // Invalid words
    EXPECT_EQ(this->dictionary.hasWord("Test"), false);
}

TEST_F(SearchWithoutError, TrickyTest) {
    // Two branching
    EXPECT_EQ(this->dictionary.hasWord("Bon"), false);

    EXPECT_EQ(this->dictionary.hasWord("W"), true);
    EXPECT_EQ(this->dictionary.hasWord("Z"), false);

    // Long
    EXPECT_EQ(this->dictionary.hasWord("Nequeporroquisquamestquidoloremipsumquiadolorsitametconsecteturadipiscivelit"), true);
}
