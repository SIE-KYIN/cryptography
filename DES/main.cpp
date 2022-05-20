#include "des.hpp"

int main()
{
	Des d;

	// round key 생성
	d.key_generate();

	// Des 암호 생성
	d.encrypt();

	d.print_ciphertext();
}
