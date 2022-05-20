#include "des.hpp"

Des::Des() : 
		// 초기 치환 표
		table_initial{58, 50, 42, 34, 26, 18, 10, 2,
							60, 52, 44, 36, 28, 20, 12, 4,
							62, 54, 46, 38, 30, 22, 14, 6,
							64, 56, 48, 40, 32, 24, 16, 8,
							57, 49, 41, 33, 25, 17, 9, 1,
							59, 51, 43, 35, 27, 19, 11, 3,
							61, 53, 45, 37, 29, 21, 13, 5,
							63, 55, 47, 39, 31, 23, 15, 7} ,
		// 최종 치환 표
		table_final { 40, 8, 48, 16, 56, 24, 64, 32,
						39, 7, 47, 15, 55, 23, 63, 31,
						38, 6, 46, 14, 54, 22, 62, 30,
						37, 5, 45, 13, 53, 21, 61, 29,
						36, 4, 44, 12, 52, 20, 60, 28,
						35, 3, 43, 11, 51, 19, 59, 27,
						34, 2, 42, 10, 50, 18, 58, 26,
						33, 1, 41, 9, 49, 17, 57, 25 },
		// 확장 P-박스 표
		table_p_box { 32, 1, 2, 3, 4, 5, 4, 5,
					6, 7, 8, 9, 8, 9, 10, 11,
					12, 13, 12, 13, 14, 15, 16, 17,
					16, 17, 18, 19, 20, 21, 20, 21,
					22, 23, 24, 25, 24, 25, 26, 27,
					28, 29, 28, 29, 30, 31, 32, 1 },
		// S-박스
    	table_s_box			{ // S-박스 1
                        { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
						0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
						4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
						15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 },
                        // S-박스 2
						{ 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
						3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
						0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
						13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 },
                        // S-박스 3
						{ 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
						13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
						13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
						1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 },
                        // S-박스 4
						{ 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
						13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
						10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
						3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 },
                        // S-박스 5
						{ 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
						14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
						4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
						11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 },
                        // S-박스 6
						{ 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
						10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
						9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
						4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 },
                        // S-박스 7
						{ 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
						13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
						1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
						6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 },
                        // S-박스 8
						{ 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
						1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
						7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
						2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 } },
		// 단순 치환 표
    	table_simple { 16, 7, 20, 21, 29, 12, 28, 17,
					1, 15, 23, 26, 5, 18, 31, 10,
					2, 8, 24, 14, 32, 27, 3, 9,
					19, 13, 30, 6, 22, 11, 4, 25 },
		// 패리티 비트 제거 표
    	table_parity_drop { 57, 49, 41, 33, 25, 17, 9, 1, 
                     58, 50, 42, 34, 26, 18, 10, 2, 
                     59, 51, 43, 35, 27, 19, 11, 3, 
                     60, 52, 44, 36, 63, 55, 47, 39, 
                     31, 23, 15, 7, 62, 54, 46, 38, 
                     30, 22, 14, 6, 61, 53, 45, 37, 
                     29, 21, 13, 5, 28, 20, 12, 4 },
    	// 시프트 테이블 - 1, 2, 9, 16번째만 1
    	table_shift { 1, 1, 2, 2, 2, 2, 2, 2,
							1, 2, 2, 2, 2, 2, 2, 1 },
    	// 키 축소표
    	table_key_compress { 14, 17, 11, 24, 1, 5, 3, 28, 
                         15, 6, 21, 10, 23, 19, 12, 4, 
                         26, 8, 16, 7, 27, 20, 13, 2,
						 41, 52, 31, 37, 47, 55, 30, 40, 
                         51, 45, 33, 48, 44, 49, 39, 56, 
                         34, 53, 46, 42, 50, 36, 29, 32 }
{
	//평문
	plain_text = "123456ABCD132536";

	// 키
	key = "AABB09182736CCDD";
}

Des::~Des()
{
	return ;
}

string Des::hex_to_bin(const string s)
{
	using std::map; 
	map<char, string> m;
	string ret = "";

	m['0'] = "0000";
	m['1'] = "0001";
	m['2'] = "0010";
	m['3'] = "0011";
	m['4'] = "0100";
	m['5'] = "0101";
	m['6'] = "0110";
	m['7'] = "0111";
	m['8'] = "1000";
	m['9'] = "1001";
	m['A'] = "1010";
	m['B'] = "1011";
	m['C'] = "1100";
	m['D'] = "1101";
	m['E'] = "1110";
	m['F'] = "1111";

	for (int i = 0; i < s.size(); i++)
		ret += m[s[i]];

	return ret;
}

string Des::bin_to_hex(const string s)
{
	map<string, char> m;
	string ret = "";
	string tmp;

	m["0000"] = '0';
	m["0001"] = '1';
	m["0010"] = '2';
	m["0011"] = '3';
	m["0100"] = '4';
	m["0101"] = '5';
	m["0110"] = '6';
	m["0111"] = '7';
	m["1000"] = '8';
	m["1001"] = '9';
	m["1010"] = 'A';
	m["1011"] = 'B';
	m["1100"] = 'C';
	m["1101"] = 'D';
	m["1110"] = 'E';
	m["1111"] = 'F';
	
	for (int i = 0; i < s.length(); i += 4) 
	{
		tmp = "";
		tmp += s[i];
		tmp += s[i + 1];
		tmp += s[i + 2];
		tmp += s[i + 3];
		ret += m[tmp];
	}

	return ret;
}

string Des::permute(const string before, const int* table, const int n)
{
	string after = "";
	
	for (int i = 0; i < n; i++)
		after += before[table[i] - 1];
	
	return after;
}

string Des::shift_left(string s, const int n)
{
	string tmp;

	for (int i = 0; i < n; i++) {
		tmp = "";
		for (int j = 1; j < 28; j++)
			tmp += s[j];
		tmp += s[0];
		s = tmp;
	}

	return s;
}

string Des::exclusive_or(const string s1, const string s2)
{
	string ret = "";

	for (int i = 0; i < s1.size(); i++)
		(s1[i] == s2[i]) ? (ret += "0") : (ret += "1");

	return ret ;
}

void Des::mixer(string &left, string &right, const int n)
{
	string expand = permute(right, table_p_box, 48);

	// 화이트너(Whitener: XOR)
	string in_block = exclusive_or(round_key[n], expand);

	// Substitute
	string out_block = "";
	for (int i = 0; i < 8; i++) {
		int row = 2 * int(in_block[i * 6] - 48) + int(in_block[i * 6 + 5] - 48);
		int col = 8 * int(in_block[i * 6 + 1] - 48) + 4 * int(in_block[i * 6 + 2] - 48) 
							+ 2 * int(in_block[i * 6 + 3] - 48) + int(in_block[i * 6 + 4] - 48);
		int value = table_s_box[i][row][col];
		out_block += char(value / 8 + 48); value = value % 8;
		out_block += char(value / 4 + 48); value = value % 4;
		out_block += char(value / 2 + 48); value = value % 2;
		out_block += char(value + 48);
	}
	// Straight D-box
	out_block = permute(out_block, table_simple, 32);

	// XOR left and out_block
	left = exclusive_or(out_block, left);
}

void Des::encrypt()
{
	// 초기 치환
	plain_text = hex_to_bin(plain_text);
	plain_text = permute(plain_text, table_initial, 64);

	// 스플릿
	string left = plain_text.substr(0, 32);
	string right = plain_text.substr(32, 32);

	// DES
	for (int i = 0; i < 16; i++) {
		// Mixer
		mixer(left, right, i);
		// Swapper
		if (i != 15) {
			swap(left, right);
		}

		cout << "Round "
			 << std::setfill('0') << std::setw(2) << std::right 
			 << i + 1 << "\t"
			 << bin_to_hex(left) << "\t"
			 << bin_to_hex(right) << "\t" 
			 << bin_to_hex(round_key[i]) << endl;
	}

	string combine = left + right;

	// 최종 치환
	ciphertext = bin_to_hex(permute(combine, table_final, 64));

	
}

void Des::key_generate()
{
	key = hex_to_bin(key);

	//패리티 비트 제거
	key = permute(key, table_parity_drop, 56); 

	// 스플릿
	string left = key.substr(0, 28);
	string right = key.substr(28, 28);

	// round key 생성
	for (int i = 0; i < 16; i++) {
		// 왼쪽 이동
		left = shift_left(left, table_shift[i]);
		right = shift_left(right, table_shift[i]);

		string combine = left + right;
		
		// 축소치환
		string RoundKey = permute(combine, table_key_compress, 48);

		round_key.push_back(RoundKey);
	}
}