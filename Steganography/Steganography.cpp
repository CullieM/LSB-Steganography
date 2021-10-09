// Steganography.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "bitmap_image.hpp"


int main()
{
   
    char* inputFilePath;
    char* outputFilePath;
    inputFilePath = (char*)"./input.bmp";
    outputFilePath = (char*)"./output.bmp";

    bitmap_image image(inputFilePath);

    image.save_image(outputFilePath); 

    std::cout << "Image created at output.bmp!\n";
}
