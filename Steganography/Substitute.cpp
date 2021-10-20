#include <string>
std::string cipherText(std::string cipheralpha) { //Converting string to uppercase
    for (int i = 0; cipheralpha[i] != '\0'; i++)
    {
        if (cipheralpha[i] >= 'a' && cipheralpha[i] <= 'z')
            cipheralpha[i] = cipheralpha[i] - 32;
    }

    std::string ciphertext = "";
    ciphertext = ciphertext + cipheralpha; // Appending sub_keyword before any other alphabet addition
    bool ch[26] = { false };
    for (int i = 0; cipheralpha[i] != '\0'; i++) // Marking all positions of sub_keyword in boolean array
    {
        int diff = cipheralpha[i] - 65; // Calculate position of alphabet in array
        ch[diff] = true;
    }
    for (int i = 0; i < 26; i++) // Appending all other alphabets not present in sub_keyword
    {
        if (ch[i] == false)
        {
            char c = char(i + 65);
            ciphertext = ciphertext + c;
        }
    }
    return ciphertext;
}
std::string substitute_encode(std::string plaintext, std::string sub_keyword) { // For encrypting string with substitute cipher
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // alphabet string to match against

    std::string ciphertext = cipherText(sub_keyword); // Call cipherText to get string of cipheralphabets

    for (int i = 0; plaintext[i] != '\0'; i++) // Convert plaintext to uppercase
    {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
            plaintext[i] = plaintext[i] - 32;
    }
    std::string encryption;
    for (char character : plaintext) { // Obtain characters in plaintext and find corresponding character in ciphertext string
        size_t position = alphabet.find(character);
        if (position != std::string::npos) {
            char new_char{ ciphertext.at(position) };
            encryption += new_char; // Appending cipher characters to create cipher text
        }
        else {
            encryption += character;
        }
    }
    return encryption;
}

std::string substitute_decode(std::string ciphertext, std::string sub_keyword) // For decryption of string with substitute cipher
{
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // alphabet string to match against

    std::string cipher_text = cipherText(sub_keyword);  // Call cipherText to get string of cipheralphabets

    for (int i = 0; ciphertext[i] != '\0'; i++) // Convert ciphertext to uppercase
    {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z')
            ciphertext[i] = ciphertext[i] - 32;
    }
    std::string decryption;
    for (char character : ciphertext) {  // Obtain characters in ciphertext and find corresponding character in alphabet string
        size_t position = cipher_text.find(character);
        if (position != std::string::npos) {
            char new_char{ alphabet.at(position) };
            decryption += new_char; // Appending alphabets characters to create plain text
        }
        else
            decryption += character;
    }
    return decryption;
}