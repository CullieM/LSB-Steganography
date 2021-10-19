#pragma once
#include <string>
std::string substitute_encode(std::string plaintext, std::string sub_keyword);
std::string substitute_decode(std::string ciphertext, std::string sub_keyword);