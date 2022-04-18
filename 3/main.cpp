#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int select_type();
bool gostop();
void type_handler(int);
void additive(string);
void multiple(string);
void affine(string);
void autokey(string);
void vigenere(string);


int main()
{
    int type;

    do
    {
        type = select_type();
        type_handler(type);
    }while (gostop());
}

int select_type()
{
    int ret;

    ret = 0;
    cout << "--------------------" << endl;
    cout << "1) 덧셈암호" << endl;
    cout << "2) 곱셈암호" << endl;
    cout << "3) 아핀암호" << endl;
    cout << "4) 자동키암호" << endl;
    cout << "5) vinegere암호" << endl;
    cout << "--------------------" << endl;
    cout << "문제유형을 고르시오 : ";
    cin >> ret;

    return (ret);
}

bool gostop()
{
    int b;

    cout << "1) Go\n2) Stop\n";
    cout << ">> ";
    cin >> b;
    cout << "\n\n";
    if (b == 1)
        return true;
    else
        return false;
}

void type_handler(int type)
{
    string message;

    cout << "\n\n암호화 할 메시지를 입력하시오" << endl;
    cout << "--------------------" << endl;
    cout << "메시지 : ";
    cin >> message;
    
    transform(message.begin(), message.end(), message.begin(), ::toupper);

    if (type == 1)
        additive(message);
    else if (type == 2)
        multiple(message);
    else if (type == 3)
        affine(message);
    else if (type == 4)
        autokey(message);
    else if (type == 5)
        vigenere(message);
    else
        cout << "해당 타입 없음" << endl;
}

void additive(string message)
{
    int key, extra;

    cout << "\n\n키값과 추가 키 개수를 입력하시오" << endl;
    cout << "--------------------" << endl;
    cout << "키값 : ";
    cin >> key;
    cout << "추가 키 개수 : ";
    cin >> extra;

    for (int i = 0; i < message.length(); i++)
        message[i] = (message[i] - 65 + key) % (26 + extra) + 65;
    cout << "\n답 : " <<  message << "\n\n";
}

void multiple(string message)
{
    int key, extra;

    cout << "\n\n키값과 추가 키 개수를 입력하시오" << endl;
    cout << "--------------------" << endl;
    cout << "키값 : ";
    cin >> key;
    cout << "추가 키 개수 : ";
    cin >> extra;

    for (int i = 0; i < message.length(); i++)
        message[i] = ((message[i] - 65) * key) % (26 + extra) + 65;
    cout << "\n답 : " <<  message << "\n\n";
}

void affine(string message)
{
    int a_key, m_key, extra;

    cout << "\n\n덧셈 키값과 곱셈 키값,  추가 키 개수를 입력하시오" << endl;
    cout << "--------------------" << endl;
    cout << "덧셈 키값 : ";
    cin >> a_key;
    cout << "곱셈 키값 : ";
    cin >> m_key;
    cout << "추가 키 개수 : ";
    cin >> extra;

    for (int i = 0; i < message.length(); i++)
        message[i] = ((message[i] - 65) * m_key + a_key) % (26 + extra) + 65;
    cout << "\n답 : " <<  message << "\n\n";
}

void autokey(string message)
{
    int key, extra;

    cout << "\n\n키값과 추가 키 개수를 입력하시오" << endl;
    cout << "--------------------" << endl;
    cout << "키값 : ";
    cin >> key;
    cout << "추가 키 개수 : ";
    cin >> extra;

    string message2;
    for (int i = 0; i < message.length(); i++)
        message2 += ((message[i] - 65 + ((i == 0) ? key : (message[i - 1] - 65))) % (26 + extra)) + 65;
    cout << "\n답 : " <<  message2 << "\n\n";
}

void vigenere(string message)
{
    int extra;
    string key;

    cout << "\n\n키 문자열과 추가 키 개수를 입력하시오" << endl;
    cout << "--------------------" << endl;
    cout << "키문자열 : ";
    cin >> key;
    cout << "추가 키 개수 : ";
    cin >> extra;

    transform(key.begin(), key.end(), key.begin(), ::toupper);
    int i = 0;
    int j = 0;
    while (i < message.length())
    {
        message[i] = ((message[i] - 65 + key[j] - 65) % (26 + extra)) + 65;
        i++;
        if (j < key.length() - 1)
            j++;
        else
            j = 0;
    }
    cout << "\n답 : " <<  message << "\n\n";
}