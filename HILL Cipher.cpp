#include<iostream>
#include<cstdlib> 
#include<string>
using namespace std;

int main() {
    unsigned int a[3][3] = {{6, 24, 1}, {13, 16, 10}, {20, 17, 15}};
    unsigned int b[3][3] = {{8, 5, 10}, {21, 8, 21}, {21, 12, 8}};
    int i, j, t = 0;
    unsigned int c[20], d[20];
    string msg;

    system("cls"); 

    cout << "Enter plain text: ";
    cin >> msg;

    for (i = 0; i < msg.length(); i++) {
        msg[i] = toupper(msg[i]);
    }

  
    for (i = 0; i < 3; i++) {
        t = 0;
        for (j = 0; j < 3; j++) {
            t = t + (a[i][j] * (msg[j] - 'A'));
        }
        d[i] = t % 26;
    }

    cout << "Encrypted Cipher Text: ";
    for (i = 0; i < 3; i++) {
        cout << char(d[i] + 'A');
    }

    for (i = 0; i < 3; i++) {
        t = 0;
        for (j = 0; j < 3; j++) {
            t = t + (b[i][j] * d[j]);
        }
        c[i] = t % 26;
    }

    cout << "\nDecrypted Cipher Text: ";
    for (i = 0; i < 3; i++) {
        cout << char(c[i] + 'A');
    }

    cout << endl;

    return 0;
}
