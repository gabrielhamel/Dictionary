/**
 * @file RemovedChar.cpp
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

class RemovedCharError : public CharDictionaryFixture { };

TEST_F(RemovedCharError, BasicTest) {
    EXPECT_EQ(this->dictionary.hasWord("Hllo"), false);
    EXPECT_EQ(this->dictionary.hasWord("Hllo", 1), true);
}

TEST_F(RemovedCharError, MultipleDeletion) {
    EXPECT_EQ(this->dictionary.hasWord("Bnsor", 1), false);
    EXPECT_EQ(this->dictionary.hasWord("Bnsor", 2), true);

    EXPECT_EQ(this->dictionary.hasWord("nsor", 2), false);
    EXPECT_EQ(this->dictionary.hasWord("nsor", 3), true);

    EXPECT_EQ(this->dictionary.hasWord("Hllo", 1), true);
    EXPECT_EQ(this->dictionary.hasWord("Hell", 1), true);
}
