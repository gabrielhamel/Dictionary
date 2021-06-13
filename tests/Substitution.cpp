/**
 * @file Substitution.cpp
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

class SubsitutionError : public CharDictionaryFixture { };

TEST_F(SubsitutionError, BasicTest) {
    EXPECT_EQ(this->dictionary.hasWord("Hallo"), false); // Hello, no errors allowed

    EXPECT_EQ(this->dictionary.hasWord("Hallo", 1), true); // Hello, one error allowed
}

TEST_F(SubsitutionError, MultipleSubstitution) {
    EXPECT_EQ(this->dictionary.hasWord("Halla", 1), false);
    EXPECT_EQ(this->dictionary.hasWord("Halla", 2), true);

    EXPECT_EQ(this->dictionary.hasWord("Aello", 1), true);
    EXPECT_EQ(this->dictionary.hasWord("ABllo", 2), true);

    EXPECT_EQ(this->dictionary.hasWord("ABllo", 1), false);
}
