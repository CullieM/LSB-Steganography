// Steganography.cpp 
// author Cuchulainn McElduff
// 
// Least significant bit image steganography on bmp files.

#include <iostream>
#include <string>
#include <bitset>
#include "bitmap_image.hpp"
#include "Substitute.h"
#include "Shift.h"

/* Function for decoding the cipher text from a given image.
 * param image, The image to extract data from.
 * returns string, The string extracted from the image.
 */ 
std::string decode_image(bitmap_image* image)
{
    unsigned int width = image->width();
    unsigned int height = image->height();
    unsigned int current_bits = 0;
    
    std::string return_string;
    std::bitset<8> plain_text_bits[10000];           // Array for the plain text bits

    for (int y = 0; y < 1; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            //Create a temporary colour.
            rgb_t colour;
            colour = image->get_pixel(x, y);

            //Convert the unsigned char colour values to bitsets.
            std::bitset<8> blue_bits(colour.blue);
            std::bitset<8> red_bits(colour.red);
            std::bitset<8> green_bits(colour.green);

            //Retrieve the seventh and eighth bits of the colour value.
            plain_text_bits[current_bits / 4][(current_bits * 2) % 8] = blue_bits[0];
            plain_text_bits[current_bits / 4][(current_bits * 2) % 8 + 1] = blue_bits[1];
            current_bits++;

            plain_text_bits[current_bits / 4][(current_bits * 2) % 8] = red_bits[0];
            plain_text_bits[current_bits / 4][(current_bits * 2) % 8 + 1] = red_bits[1];
            current_bits++;
            
            plain_text_bits[current_bits / 4][(current_bits * 2) % 8] = green_bits[0];
            plain_text_bits[current_bits / 4][(current_bits * 2) % 8 + 1] = green_bits[1];
            current_bits++;
        }
    }

    for (int i = 0; i < width; ++i)
    {

        unsigned long interim_long = plain_text_bits[i].to_ulong();
        unsigned char temp_char = static_cast<unsigned char>(interim_long);

        return_string += temp_char;
    }

    return return_string;
}

/* Function for hiding text into an image.
 * param image, The image to extract data from.
 * returns string, The string extracted from the image.
 */
void encode_image(bitmap_image* image, std::string plain_text)
{
    unsigned int current_bits = 0;                   // To keep track of the string bits to store.
    unsigned int current_pixel = 0;                  // To track the pixel

    unsigned int width = image->width();             // Width of the image
    unsigned int height = image->height();           // Height of the image
    unsigned int string_length = plain_text.length();// Length of the plain text
    
    // Maximum length of string that can be stored if 6 bits can be stored in each pixel and there are 8 bits per string character.
    unsigned int max_string_length = (width * height * 6) / 8; 

    // If the string is too long to be stored in the image.
    if (string_length > max_string_length)  
    {
        std::cout << "String is too long!\n";
        return;
    }
    
    unsigned int pixels_required = (string_length * 8) / 6;  // Pixels required to store the entire string. 6 Bits can be stored in each pixel, and there are 8 bits per char.
    std::bitset<8> plain_text_bits[10000];                   // Array for the plain text bits
    
    // Initialise plain text bits from the string param.
    for (int i = 0; i < string_length; i++)
    {
        // Interim convert to uchar
        unsigned char temp_char = plain_text[i];
        // Initialise bitset from uchar
        std::bitset<8> temp_bits(temp_char);
        // Initialise array element from bitset
        plain_text_bits[i] = temp_bits;

    }
    
    //For every row in the image
    for (int y = 0; y < height; ++y)
    {
        //For every column in the image
        for (int x = 0; x < width; ++x)
        {
            // If we do not need to store any more data.
            if ((current_pixel) > pixels_required) return;
                
            //Current pixel data.
            rgb_t pixel;
            pixel = image->get_pixel(x, y);

            //Convert the unsigned char colour values to bitsets.
            std::bitset<8> blue_bits(pixel.blue);
            std::bitset<8> red_bits(pixel.red);
            std::bitset<8> green_bits(pixel.green);

            //Change the 7th and 8th bits of the colour value to the appropriate bits in the string. 
            blue_bits[0] = plain_text_bits[current_bits / 4][(current_bits * 2) % 8];
            blue_bits[1] = plain_text_bits[current_bits / 4][(current_bits * 2) % 8 + 1];
            current_bits++;
                
            red_bits[0] = plain_text_bits[current_bits / 4][(current_bits * 2) % 8];
            red_bits[1] = plain_text_bits[current_bits / 4][(current_bits * 2) % 8 + 1];
            current_bits++;
                
            green_bits[0] = plain_text_bits[current_bits / 4][(current_bits * 2) % 8];
            green_bits[1] = plain_text_bits[current_bits / 4][(current_bits * 2) % 8 + 1];
            current_bits++;

            //Interim conversion to ulong, then uchar
            unsigned long blue_ulong = blue_bits.to_ulong();
            unsigned long red_ulong = red_bits.to_ulong();
            unsigned long green_ulong = green_bits.to_ulong();
            unsigned char new_blue = static_cast<unsigned char>(blue_ulong);
            unsigned char new_red = static_cast<unsigned char>(red_ulong);
            unsigned char new_green = static_cast<unsigned char>(green_ulong);

            //Set the new pixel colour
            pixel.blue = new_blue;
            pixel.red = new_red;
            pixel.green = new_green;
            image->set_pixel(x, y, pixel);
            current_pixel++;
        }
    }
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
    

    bitmap_image* image = new bitmap_image(input_path);
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
    if (encrypt)
        std::cout << "encrypt with shift or substitute cipher?\n";
    else
        std::cout << "decrypt with the shift or substitute cipher?\n";
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
    }

    // If encrypting the image
    if (encrypt)
    { 
        //                    If shifting                          If substituting (placeholder)
        cipher_text = shift ? shift_encode(plain_text, shift_by) : substitute_encode(plain_text, sub_keyword);
        
        encode_image(image, cipher_text);

        image->save_image(output_path);
        std::cout << "Image successfully encoded at output.bmp!\n";
    }
    // If decrypting the image
    else
    {
        // Decode the string from the image.
        cipher_text = decode_image(image);
        //                    If deshifting                          If desubstituting (placeholder)
        plain_text = shift ? shift_decode(cipher_text, shift_by) : substitute_decode(cipher_text, sub_keyword);       

        std::cout << "The secret message hidden in the image was: \n\"" << plain_text << "\"\n";
    }

    std::cout << "Press any key to exit... \n";
    std::getchar();
}
