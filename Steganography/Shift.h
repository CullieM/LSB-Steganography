#pragma once
#include <string>
std::string shift_encode(std::string plain_text, unsigned int key);
std::string shift_decode(std::string cipher_text, unsigned int key);