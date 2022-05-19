#include "des.hpp"

int main()
{
	Des d;

	d.key_generate();	

	cout << "\nEncryption:\n\n";
	string cipher = d.encrypt();
	cout << "\nCipher Text: " << cipher << endl;
}
