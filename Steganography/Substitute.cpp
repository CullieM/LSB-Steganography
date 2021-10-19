#include <string>
std::string cipherText(std::string cipheralpha) {
    for (int i = 0; cipheralpha[i] != '\0'; i++)
    {
        if (cipheralpha[i] >= 'a' && cipheralpha[i] <= 'z')
            cipheralpha[i] = cipheralpha[i] - 32;
    }

    std::string ciphertext = "";
    ciphertext = ciphertext + cipheralpha;
    bool ch[26] = { false };
    for (int i = 0; cipheralpha[i] != '\0'; i++)
    {
        int diff = cipheralpha[i] - 65;
        ch[diff] = true;
    }
    for (int i = 0; i < 26; i++)
    {
        if (ch[i] == false)
        {
            char c = char(i + 65);
            ciphertext = ciphertext + c;
        }
    }
    return ciphertext;
}
std::string substitute_encode(std::string plaintext, std::string sub_keyword) {
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string ciphertext = cipherText(sub_keyword);
    for (int i = 0; plaintext[i] != '\0'; i++)
    {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
            plaintext[i] = plaintext[i] - 32;
    }
    std::string encryption;
    for (char character : plaintext) {
        size_t position = alphabet.find(character);
        if (position != std::string::npos) {
            char new_char{ ciphertext.at(position) };
            encryption += new_char;
        }
        else {
            encryption += character;
        }
    }
    return encryption;
}

std::string substitute_decode(std::string ciphertext, std::string sub_keyword)
{
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string cipher_text = cipherText(sub_keyword);
    for (int i = 0; ciphertext[i] != '\0'; i++)
    {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z')
            ciphertext[i] = ciphertext[i] - 32;
    }
    std::string decryption;
    for (char character : ciphertext) {
        size_t position = cipher_text.find(character);
        if (position != std::string::npos) {
            char new_char{ alphabet.at(position) };
            decryption += new_char;
        }
        else
            decryption += character;
    }
    return decryption;
}