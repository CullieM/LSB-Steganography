#pragma once
#include <string>
std::string substitute_encode(std::string plain_text, unsigned int key);
std::string substitute_decode(std::string cipher_text, unsigned int key);