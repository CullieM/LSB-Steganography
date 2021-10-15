## Least Significant Bit Image Steganography 
  
### Description
  
Command-line tool for hiding plain text using least-significant-bit image steganography. Caesar Shift Cipher and Substitution Cipher [as per this spec](https://en.wikipedia.org/wiki/Substitution_cipher#Simple_substitution) implemented for further obstruction. For KIT325: Advanced Cybersecurity &amp; eForensics at the University of Tasmania.
  
### Usage
Download Steganography.exe from releases, place in a folder with an image to encode titled "input.bmp", which at this stage must be 24 bit depth bmp.
  
1.  Select either encrypt or decrypt
2.  (if encrypting) select the text to encrypt.
3.  Select **shift** or **substitute** cipher.
4.  Select what **value** to shift by or what **key** to subsitute with
5.  See output.bmp for encoded image. Change this file to be input.bmp to decode the text.
  

  
### Acknowledgements
Uses [ArashPartow/bitmap](https://github.com/ArashPartow/bitmap). 
