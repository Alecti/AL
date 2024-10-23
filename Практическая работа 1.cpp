#include <iostream>
#include <windows.h>
using namespace std;
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

void intRepresentation(int userIntNumber) {
    unsigned int mask;
    mask = 1 << 31;
    SetConsoleTextAttribute(handle, FOREGROUND_RED);
    for (int i = 0; i < sizeof(int) * 8; i++) {
        putchar(userIntNumber & mask ? '1' : '0');
        mask >>= 1;
        if (i % 8 == 0 || i == 31) {
            SetConsoleTextAttribute(handle, FOREGROUND_BLUE);
            putchar(' ');
        }
    }
    cout << endl;
    SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void floatRepresentation(int fNumber) {
    unsigned int mask;
    mask = 1 << 31;
    SetConsoleTextAttribute(handle, FOREGROUND_RED);
    for (int i = 0; i < sizeof(float) * 8; i++) {
        putchar(fNumber & mask ? '1' : '0');
        mask >>= 1;
        switch (i) {
        case 0:
            putchar(' ');
            SetConsoleTextAttribute(handle, FOREGROUND_BLUE);
            break;
        case 7:
            putchar(' ');
            SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_BLUE);
            break;
        }
    }
    cout << endl;
    SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void doubleRepresentation(int dNumber[]) {
    unsigned int mask;
    mask = 1 << 31;
    int ratio = sizeof(double) / sizeof(int);
    SetConsoleTextAttribute(handle, FOREGROUND_RED);
    for (int j = 0; j < ratio; j++) {
        mask = 1 << 31;
        for (int i = 0; i < sizeof(int) * 8; i++) {
            putchar(dNumber[ratio - 1 - j] & mask ? '1' : '0');
            mask >>= 1;
            if (j == 0) {
                switch (i) {
                case 0:
                    putchar(' ');
                    SetConsoleTextAttribute(handle, FOREGROUND_BLUE);
                    break;
                case 11:
                    putchar(' ');
                    SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_BLUE);
                    break;
                }
            }
        }
    }
    cout << endl;
    SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

int main() {

    setlocale(0, "");
    char input;
    int bitNumber, bitValue;

    // 1) memory in bytes
    cout << "int - " << sizeof(int) << endl;
    cout << "short int - " << sizeof(short int) << endl;
    cout << "long int - " << sizeof(long int) << endl;
    cout << "float - " << sizeof(float) << endl;
    cout << "double - " << sizeof(double) << endl;
    cout << "long double - " << sizeof(long double) << endl;
    cout << "char - " << sizeof(char) << endl;
    cout << "bool - " << sizeof(bool) << endl;

    cout << endl << endl;

    // 2) binary number representation int
    cout << "Введите число целого типа" << endl;
    int userIntNumber;
    cin >> userIntNumber;
    intRepresentation(userIntNumber);
    // change bit
    do {
        cout << "Вы хотите изменить какой-нибудь бит?" << endl;
        cout << "введите y/n" << endl;
        cin >> input;
        if (input == 'y' ) {
            cout << "Введите номер бита (биты считают справа налево и считать начинают с 0)" << endl;
            cin >> bitNumber;
            cout << "Введите значение бита (0 или 1)" << endl;
            cin >> bitValue;
            if (bitValue == 1) {
                userIntNumber = userIntNumber | (1 << bitNumber);
            }
            else {
                userIntNumber = userIntNumber & (~(1 << bitNumber));
            }
            intRepresentation(userIntNumber);
        }
        else if (input == 'n') {

        }
        else {
            cout << "Вы неправильно ввели ответ" << endl;
        }
    } while ( input != 'n');
   

    cout << endl << endl;
    

    // 3) binary number representation float
    cout << "Введите число типа float" << endl;
    union {
        float userFloatNumber;
        int fNumber;
    };
    cin >> userFloatNumber;
    floatRepresentation(fNumber);
    // change bit
    do {
        cout << "Вы хотите изменить какой-нибудь бит?" << endl;
        cout << "введите y/n" << endl;
        cin >> input;
        if (input == 'y') {
            cout << "Введите номер бита (биты считают справа налево и считать начинают с 0)" << endl;
            cin >> bitNumber;
            cout << "Введите значение бита (0 или 1)" << endl;
            cin >> bitValue;
            if (bitValue == 1) {
                fNumber = fNumber | (1 << (bitNumber));
            }
            else {
                fNumber = fNumber & (~(1 << bitNumber));
            }
            floatRepresentation(fNumber);
        }
        else if (input == 'n') {

        }
        else {
            cout << "Вы неправильно ввели ответ" << endl;
        }
    } while (input != 'n');


    cout << endl << endl;


    // 4)  binary number representation double
    cout << "Введите число типа double" << endl;
    union {
        double userDoubleNumber;
        int dNumber[sizeof(double) / sizeof(int)];
    };
    cin >> userDoubleNumber;
    doubleRepresentation(dNumber);
    // change bit
    do {
        cout << "Вы хотите изменить какой-нибудь бит?" << endl;
        cout << "введите y/n" << endl;
        cin >> input;
        if (input == 'y') {
            cout << "Введите номер бита (биты считают справа налево и считать начинают с 0)" << endl;
            cin >> bitNumber;
            cout << "Введите значение бита (0 или 1)" << endl;
            cin >> bitValue;
            if (bitNumber < 32) {
                if (bitValue == 1) {
                    dNumber[0] = dNumber[0] | (1 << (bitNumber));
                }
                else {
                    dNumber[0] = dNumber[0] & (~(1 << (bitNumber)));
                } 
                doubleRepresentation(dNumber);
            }
            else {
                if (bitValue == 1) {
                    dNumber[1] = dNumber[1] | (1 << (bitNumber));
                }
                else {
                    dNumber[1] = dNumber[1] & (~(1 << (bitNumber)));
                } 
                doubleRepresentation(dNumber);
            }
            
        }
        else if (input == 'n') {

        }
        else {
            cout << "Вы неправильно ввели ответ" << endl;
        }
    } while (input != 'n');
    
    cout << endl << endl;
}
