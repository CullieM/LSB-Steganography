#include <string>

std::string shift_encode(std::string plain_text, unsigned int key)
{
    char ch;
    for (int i = 0; i < plain_text.length(); ++i) {
        ch = plain_text[i];
        //  for lower case
        if (ch >= 'a' && ch <= 'z') {
            ch = ch + key;
            if (ch > 'z') {
                ch = ch - 'z' + 'a' - 1;
            }
            plain_text[i] = ch;
        }
        //  for upper case
        else if (ch >= 'A' && ch <= 'Z') {
            ch = ch + key;
            if (ch > 'Z') {
                ch = ch - 'Z' + 'A' - 1;
            }
            plain_text[i] = ch;
        }
    }
    return plain_text;
}


// for Decryption


std::string shift_decode(std::string cipher_text, unsigned int key) {
    char ch;
    for (int i = 0; i < cipher_text.length(); ++i) {
        ch = cipher_text[i];
        //  for lower case
        if (ch >= 'a' && ch <= 'z') {
            ch = ch - key;
            if (ch < 'a') {
                ch = ch + 'z' - 'a' + 1;
            }
            cipher_text[i] = ch;
        }
        //  for upper case
        else if (ch >= 'A' && ch <= 'Z') {
            ch = ch - key;
            if (ch < 'A') {
                ch = ch + 'Z' - 'A' + 1;
            }
            cipher_text[i] = ch;
        }
    }
    return cipher_text;
}