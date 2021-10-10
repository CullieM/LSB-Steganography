// Steganography.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <bitset>
#include "bitmap_image.hpp"

// Function for decoding the cipher text from a given image.
std::string decode_image(bitmap_image input)
{
    unsigned int width = input.width();
    unsigned int height = input.height();

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            
        }
    }

    return "not yet implemeneted";
}

//Function for hiding text into an image using least significant bit image steganography.
bitmap_image encode_image(bitmap_image input, std::string cipher_text)
{
    unsigned int width = input.width();
    unsigned int height = input.height();

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            rgb_t colour;
            colour = input.get_pixel(x, y);
            
            std::bitset<8> var(colour.blue);
            for (int k = 0; k < 8; k++)
            {
                var[k] = 0;
            }
            unsigned long temp_ulong = var.to_ulong();
            unsigned char new_blue = static_cast<unsigned char>(temp_ulong);
            colour.blue = new_blue;
            input.set_pixel(x, y, colour);
        }
    }
    return input;
}

int main()
{
    const int BUFFER_SIZE = 100;
    bool encrypt, shift;
    
    char user_input[BUFFER_SIZE * 10] = "";
    char sub_keyword[BUFFER_SIZE] = "";
    std::string plain_text;
    std::string cipher_text;

    const char* input_path = "input.bmp";
    const char* output_path = "output.bmp";
    

    int shift_by;
    
    bitmap_image image(input_path);
    std::cout << "Image read from input.bmp\n";

    //Prompt the user whether they want to encrypt or decrypt.
    std::cout << "Would you like to encrypt or decrypt an image?\n";
    fgets(user_input, BUFFER_SIZE, stdin);
    if (strcmp(user_input, "encrypt\n") == 0)
    {
        encrypt = true;
        std::cout << "you have selected encryption. \n";

        //Prompt the user for the plain text.
        std::cout << "what text would you like to encrypt in the image?\n";
        fgets(user_input, BUFFER_SIZE, stdin);
        plain_text = user_input;
    }
    else
    {
        encrypt = false;
        std::cout << "you have selected decryption. \n";
    }
    

    //Prompt the user whether they want to use the shift or substitution cipher.
    std::cout << "shift or substitute cipher?\n";
    fgets(user_input, BUFFER_SIZE, stdin);
    
    //Shift cipher
    if (strcmp(user_input, "shift\n") == 0)
    {
        shift = true;
        std::cout << "you have selected the shift cipher. \n";
        //Prompt the user either the value to shift by
        if (encrypt)
        {
            std::cout << "shift the text by how much?\n";
            fgets(user_input, BUFFER_SIZE, stdin);
            shift_by = atoi(user_input);
            std::cout << "You are shifting the text by " << shift_by << " characters\n";
        }   
        else
        {
            std::cout << "how much was the image shifted by?\n";
            fgets(user_input, BUFFER_SIZE, stdin);
            shift_by = atoi(user_input);
            std::cout << "You are decoding with a shift value of: " << shift_by << " characters\n";
        }
         
    }
    //Substitution Cipher
    else
    {
        shift = false;
        std::cout << "you have selected the substitution cipher. \n";
        //Prompt the user for  the keyword for the substitution cipher.
        if (encrypt)
        {
            std::cout << "what keyword do you want to seed the substitution cipher with?\n";
            fgets(sub_keyword, BUFFER_SIZE, stdin);
            std::cout << "You are seeding the sub cipher with keyword: " << sub_keyword << "\n";
        } 
        else
        {
            std::cout << "What keyword was used to seed the substitution cipher?\n";
            fgets(sub_keyword, BUFFER_SIZE, stdin);
            std::cout << "You are decoding with the sub cipher keyword: " << sub_keyword << "\n";
            
            
        }
        // cipher_text = 
    }

    if (encrypt)
    { 
        //cipher_text = shift ? shift_encode(plain_text) : substitute_encode(plain_text);
        cipher_text = (char*)"placeholder for above line";
        
        image = encode_image(image, cipher_text);

        image.save_image(output_path);
        std::cout << "Image successfully encoded at output.bmp!\n";
    }
    else
    {
        cipher_text = decode_image(image);
        //plain_text = shift ? shift_decode(cipher_text) : substitute_decode(cipher_text);
        plain_text = "placeholder for above line";

        std::cout << "The secret message hidden in the image was: \n\"" << plain_text << "\"\n";
    } 
}
