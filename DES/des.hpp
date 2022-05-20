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
    int table_initial[64];
    int table_final[64];
    int table_p_box[48];
    int table_s_box[8][4][16];
    int table_simple[32];
    int table_parity_drop[56];
    int table_shift[16];
    int table_key_compress[48];
    string plain_text;
    string key;
    vector<string> round_key; // rkb for RoundKeys in binary
	string ciphertext;
public:
    Des();
    ~Des();
	// 기능 모듈
    string hex_to_bin(string);
    string bin_to_hex(string);
    string permute(string, int*, int);
    string shift_left(string, int);
    string exclusive_or(string, string);
	void mixer(string &, string &, int);
	void print_ciphertext() {cout << "\nCiphertext : " << ciphertext;}
	// 메인 로직
    void encrypt();
    void key_generate();
};

#endif