#include <string>
std::string shift_encode(std::string plain_text, unsigned int key)  // for encrypting string with shift cipher
{
    char ch;
    for (int i = 0; i < plain_text.length(); ++i) {
        ch = plain_text[i];

        if (ch >= 'a' && ch <= 'z') {   //  Add key to lower case plain text to convert it to cipher text
            ch = ch + key;
            if (ch > 'z') {
                ch = ch - 'z' + 'a' - 1;
            }
            plain_text[i] = ch;
        }


        else if (ch >= 'A' && ch <= 'Z') {   //  Add key to upper case plain text to convert it to cipher text
            ch = ch + key;
            if (ch > 'Z') {
                ch = ch - 'Z' + 'A' - 1;
            }
            plain_text[i] = ch;
        }
    }
    return plain_text;
}



std::string shift_decode(std::string cipher_text, unsigned int key) {  // for decrypting string with shift cipher
    char ch;
    for (int i = 0; i < cipher_text.length(); ++i) {
        ch = cipher_text[i];

        if (ch >= 'a' && ch <= 'z') {  //  Subtracting key from lower case cipher text to convert it to plain text
            ch = ch - key;
            if (ch < 'a') {
                ch = ch + 'z' - 'a' + 1;
            }
            cipher_text[i] = ch;
        }


        else if (ch >= 'A' && ch <= 'Z') {  //  Subtracting key from upper case cipher text to convert it to plain text
            ch = ch - key;
            if (ch < 'A') {
                ch = ch + 'Z' - 'A' + 1;
            }
            cipher_text[i] = ch;
        }
    }
    return cipher_text;
}