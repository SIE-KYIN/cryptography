#ifndef DES_HPP
#define DES_HPP

//라이브러리
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip> 


using std::map; using std::string; using std::vector;
using std::cout; using std::endl;

class Des 
{
private:
    const int table_initial[64];
    const int table_final[64];
    const int table_p_box[48];
    const int table_s_box[8][4][16];
    const int table_simple[32];
    const int table_parity_drop[56];
    const int table_shift[16];
    const int table_key_compress[48];
    string plain_text;
    string key;
    vector<string> round_key; // rkb for RoundKeys in binary
	string ciphertext;
public:
    Des();
    ~Des();
	// 기능 모듈
    string hex_to_bin(const string);
    string bin_to_hex(const string);
    string permute(const string, const int*, const int);
    string shift_left(string, const int);
    string exclusive_or(const string, const string);
	void mixer(string &, string &, const int);
	void print_ciphertext() {cout << "\nCiphertext : " << ciphertext;}
	// 메인 로직
    void encrypt();
    void key_generate();
};

#endif