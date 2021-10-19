#include <string>

std::string substitute_encode(std::string plain_text, unsigned int key) {
	for (int i = 0; i < plain_text.length(); i++) {
		if (plain_text[i] == ' ')
			continue;

		char first_word = islower(plain_text[i]) ? 'a' : 'A';
		unsigned int operation = plain_text[i] - first_word,
			new_operation = operation + key;
		plain_text[i] = first_word + new_operation % 26;
	}
	return plain_text;
}



// for Decryption


std::string substitute_decode(std::string cipher_text, unsigned int key) {
	for (int i = 0; i < cipher_text.length(); i++) {
		if (cipher_text[i] == ' ')
			continue;

		char first_word = islower(cipher_text[i]) ? 'a' : 'A';
		unsigned int operation = cipher_text[i] - first_word;
		int new_operation = operation - key;

		if (new_operation < 0) {
			new_operation += 26;
		}

		cipher_text[i] = first_word + (new_operation % 26);
	}
	return cipher_text;
}