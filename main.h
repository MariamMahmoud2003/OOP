//
// Created by Lenovo on 11/11/2023.
//

#ifndef BIGREALNEWONE_MAIN_H
#define BIGREALNEWONE_MAIN_H

#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

class BigReal {
private:
    char s = '+';
    string bigreals, integer, fraction;

    static bool isValidReal( string realNumber);//done
public:

    BigReal(double realNumber = 0.0);//done
    BigReal(string realNumber);//done
    BigReal(const BigReal &other);//done
    BigReal &operator=(const BigReal &other);

    void setNum(string realNumber);//done

    int size();

    char sign();
    friend string removeLeadingZeros(string& number);




    BigReal operator+(BigReal &other);

    BigReal operator-(BigReal &other);

    bool operator==(BigReal &other);//done
    bool operator>(BigReal &other);//done
    bool operator<(BigReal &other);//done
    friend ostream &operator<<(ostream &out, BigReal &num);//done
};

#endif //BIGREALNEWONE_MAIN_H
