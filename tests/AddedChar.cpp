/**
 * @file AddedChar.cpp
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

class AddedCharError : public CharDictionaryFixture { };

TEST_F(AddedCharError, BasicTest) {
    EXPECT_EQ(this->dictionary.hasWord("Heallo"), false);
    EXPECT_EQ(this->dictionary.hasWord("Heallo", 1), true);
}

TEST_F(AddedCharError, MultipleAddition) {
    EXPECT_EQ(this->dictionary.hasWord("Heabllo", 1), false);
    EXPECT_EQ(this->dictionary.hasWord("Heabllo", 2), true);


    EXPECT_EQ(this->dictionary.hasWord("Heallpo", 1), false);
    EXPECT_EQ(this->dictionary.hasWord("Heallpo", 2), true);

    EXPECT_EQ(this->dictionary.hasWord("CHeallpo", 2), false);
    EXPECT_EQ(this->dictionary.hasWord("CHeallpo", 3), true);
}

TEST_F(AddedCharError, Tricky) {
    EXPECT_EQ(this->dictionary.hasWord("Helloa", 0), false);
    EXPECT_EQ(this->dictionary.hasWord("Helloa", 1), true);

    EXPECT_EQ(this->dictionary.hasWord("Helloab", 1), false);
    EXPECT_EQ(this->dictionary.hasWord("Helloab", 2), true);
}
