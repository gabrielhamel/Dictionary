/**
 * @file Fixtures.hpp
 * @author Gabriel Hamel (gabriel.hamel.pro@gmail.com)
 * @brief
 * @version 1.0
 * @date 2021-06-13
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "Dictionary.hpp"

class CharDictionaryFixture : public ::testing::Test {

    protected:
        Dictionary<char> dictionary;

    protected:
        CharDictionaryFixture() {
            // Some words
            this->dictionary.addWord("Hello");
            this->dictionary.addWord("Bonjour");
            this->dictionary.addWord("Bonsoir");

            // Tricky words
            this->dictionary.addWord("W");
            this->dictionary.addWord("Nequeporroquisquamestquidoloremipsumquiadolorsitametconsecteturadipiscivelit");
        }
};
