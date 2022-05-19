#include "des.hpp"



string Des::hex2bin(string s)
{
	map<char, string> mp;
	mp['0'] = "0000";
	mp['1'] = "0001";
	mp['2'] = "0010";
	mp['3'] = "0011";
	mp['4'] = "0100";
	mp['5'] = "0101";
	mp['6'] = "0110";
	mp['7'] = "0111";
	mp['8'] = "1000";
	mp['9'] = "1001";
	mp['A'] = "1010";
	mp['B'] = "1011";
	mp['C'] = "1100";
	mp['D'] = "1101";
	mp['E'] = "1110";
	mp['F'] = "1111";
	string bin = "";
	for (int i = 0; i < s.size(); i++) {
		bin += mp[s[i]];
	}
	return bin;
}

string Des::bin2hex(string s)
{
	// binary to hexadecimal conversion
	map<string, char> mp;
	mp["0000"] = '0';
	mp["0001"] = '1';
	mp["0010"] = '2';
	mp["0011"] = '3';
	mp["0100"] = '4';
	mp["0101"] = '5';
	mp["0110"] = '6';
	mp["0111"] = '7';
	mp["1000"] = '8';
	mp["1001"] = '9';
	mp["1010"] = 'A';
	mp["1011"] = 'B';
	mp["1100"] = 'C';
	mp["1101"] = 'D';
	mp["1110"] = 'E';
	mp["1111"] = 'F';
	string hex = "";
	for (int i = 0; i < s.length(); i += 4) {
		string ch = "";
		ch += s[i];
		ch += s[i + 1];
		ch += s[i + 2];
		ch += s[i + 3];
		hex += mp[ch];
	}
	return hex;
}

string Des::permute(string k, int* arr, int n)
{
	string per = "";
	for (int i = 0; i < n; i++) {
		per += k[arr[i] - 1];
	}
	return per;
}

string Des::shift_left(string k, int shifts)
{
	string s = "";
	for (int i = 0; i < shifts; i++) {
		for (int j = 1; j < 28; j++) {
			s += k[j];
		}
		s += k[0];
		k = s;
		s = "";
	}
	return k;
}

string Des::xor_(string a, string b)
{
	string ans = "";
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == b[i]) {
			ans += "0";
		}
		else {
			ans += "1";
		}
	}
	return ans;
}

string Des::encrypt()
{
	// Hexadecimal to binary
	pt = hex2bin(pt);

	// Initial Permutation Table
	
	// Initial Permutation
	pt = permute(pt, initial_perm, 64);
	cout << "After initial permutation: " << bin2hex(pt) << endl;

	// Splitting
	string left = pt.substr(0, 32);
	string right = pt.substr(32, 32);
	cout << "After splitting: L0=" << bin2hex(left)
		<< " R0=" << bin2hex(right) << endl;


	cout << endl;
	for (int i = 0; i < 16; i++) {
		// Expansion D-box
		string right_expanded = permute(right, this->exp_d, 48);

		// XOR RoundKey[i] and right_expanded
		string x = xor_(rkb[i], right_expanded);

		// S-boxes
		string op = "";
		for (int i = 0; i < 8; i++) {
			int row = 2 * int(x[i * 6] - '0') + int(x[i * 6 + 5] - '0');
			int col = 8 * int(x[i * 6 + 1] - '0') + 4 * int(x[i * 6 + 2] - '0') + 2 * int(x[i * 6 + 3] - '0') + int(x[i * 6 + 4] - '0');
			int val = s[i][row][col];
			op += char(val / 8 + '0');
			val = val % 8;
			op += char(val / 4 + '0');
			val = val % 4;
			op += char(val / 2 + '0');
			val = val % 2;
			op += char(val + '0');
		}
		// Straight D-box
		op = permute(op, per, 32);

		// XOR left and op
		x = xor_(op, left);

		left = x;

		// Swapper
		if (i != 15) {
			swap(left, right);
		}
		cout << "Round " << i + 1 << " " << bin2hex(left) << " "
			<< bin2hex(right) << " " << rk[i] << endl;
	}

	// Combination
	string combine = left + right;

	// Final Permutation
	string cipher = bin2hex(permute(combine, final_perm, 64));
	return cipher;
}

void Des::key_generate()
{
	key = hex2bin(key);
	// getting 56 bit key from 64 bit using the parity bits
	key = permute(key, keyp, 56); // key without parity
	// Splitting
	left = key.substr(0, 28);
	right = key.substr(28, 28);

	for (int i = 0; i < 16; i++) {
		// Shifting
		left = shift_left(left, shift_table[i]);
		right = shift_left(right, shift_table[i]);

		// Combining
		string combine = left + right;

		// Key Compression
		string RoundKey = permute(combine, key_comp, 48);

		rkb.push_back(RoundKey);
		rk.push_back(bin2hex(RoundKey));
	}
}