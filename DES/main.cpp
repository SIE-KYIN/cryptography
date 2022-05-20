#include "des.hpp"

int main()
{
	Des d;

	d.key_generate();

	d.encrypt();

	d.print_ciphertext();
}
