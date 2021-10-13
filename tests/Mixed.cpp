/**
 * @file Mixed.cpp
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

class MixedError : public CharDictionaryFixture { };

TEST_F(MixedError, BasicMixed) {
    // - 1 char
    // substitution
    EXPECT_EQ(this->dictionary.hasWord("Hlla", 1), false);
    EXPECT_EQ(this->dictionary.hasWord("Hlla", 2), true);

    // +1 char
    // -1 char
    EXPECT_EQ(this->dictionary.hasWord("Hllop", 1), false);
    EXPECT_EQ(this->dictionary.hasWord("Hllop", 2), true);

    // +1 char
    // substitution
    EXPECT_EQ(this->dictionary.hasWord("HealXo", 1), false);
    EXPECT_EQ(this->dictionary.hasWord("HealXo", 2), true);

    // All
    EXPECT_EQ(this->dictionary.hasWord("ealXo", 2), false);
    EXPECT_EQ(this->dictionary.hasWord("ealXo", 3), true);
}

TEST_F(MixedError, ComplexTests) {
    // Triple substitution
    EXPECT_EQ(this->dictionary.hasWord("Babcoir", 2), false);
    EXPECT_EQ(this->dictionary.hasWord("Babcoir", 3), true);

    // 2 substitution, -1 char, +2 char
    EXPECT_EQ(this->dictionary.hasWord("ZonFFoiZ", 3), false);
    EXPECT_EQ(this->dictionary.hasWord("ZonFFoiZ", 4), true); // +2 cancel the -1
    EXPECT_EQ(this->dictionary.hasWord("ZonFFoiZ", 5), true);

    // -3 char, 1 substitution
    EXPECT_EQ(this->dictionary.hasWord("NeueprroqisquamesMquidoloremipsumquiadolorsitametconsecteturadipiscivelit", 3), false);
    EXPECT_EQ(this->dictionary.hasWord("NeueprroqisquamesMquidoloremipsumquiadolorsitametconsecteturadipiscivelit", 4), true);
}
