#include "main.h"


BigReal::BigReal(double realNumber) {
    // take double number and turn it to string
    bigreals = to_string(realNumber);
    // divide string to integer and fraction depend on before and after '.'
    for (long long i = 0; i < bigreals.size(); ++i) {
        if (bigreals[i] != '.')
            integer += bigreals[i];
        else if (bigreals[i] == '.') {
            for (long long j = i + 1; j < bigreals.size(); ++j)
                fraction += bigreals[j];
            break;
        }
    }
}

BigReal::BigReal(string realNumber) {
    bigreals = realNumber;
    if (isValidReal(bigreals)) {
        // check if there is sign or not
        if (realNumber[0] == '+') {
            // divide string to integer and fraction depend on before and after '.'
            for (long long i = 1; i < bigreals.size(); ++i) {
                if (bigreals[i] != '.')
                    integer += bigreals[i];
                else if (bigreals[i] == '.') {
                    for (long long j = i + 1; j < bigreals.size(); ++j)
                        fraction += bigreals[j];
                    break;
                }
            }
            // check if there is sign or not
        } else if (realNumber[0] == '-') {
            s = '-';
            // divide string to integer and fraction depend on before and after '.'
            for (long long i = 1; i < bigreals.size(); ++i) {
                if (bigreals[i] != '.')
                    integer += bigreals[i];
                else if (bigreals[i] == '.') {
                    for (long long j = i + 1; j < bigreals.size(); ++j)
                        fraction += bigreals[j];
                    break;
                }
            }
            // if there is no sign i will begin to divide string from first character
        } else {
            for (long long i = 0; i < bigreals.size(); ++i) {
                if (bigreals[i] != '.')
                    integer += bigreals[i];
                else if (bigreals[i] == '.') {
                    for (long long j = i + 1; j < bigreals.size(); ++j)
                        fraction += bigreals[j];
                    break;
                }
            }
        }
        // if no integer as .23456789
        if (integer.size() == 0)
            integer = "0";
        // if no decimal as 1234567
        if (fraction.size() == 0)
            fraction = "0";
    }
}
// copy attributes to another object
BigReal::BigReal(const BigReal &other) {
    bigreals = other.bigreals;
    integer = other.integer;
    fraction = other.fraction;
}
// make operations as parameterize constructor
void BigReal::setNum(string realNumber) {
    bigreals = realNumber;
    if (isValidReal(bigreals)) {
        // check if there is sign or not
        if (realNumber[0] == '+') {
            // divide string to integer and fraction depend on before and after '.'
            for (long long i = 1; i < bigreals.size(); ++i) {
                if (bigreals[i] != '.')
                    integer += bigreals[i];
                else if (bigreals[i] == '.') {
                    for (long long j = i + 1; j < bigreals.size(); ++j)
                        fraction += bigreals[j];
                    break;
                }
            }
            // check if there is sign or not
        } else if (realNumber[0] == '-') {
            s = '-';
            // divide string to integer and fraction depend on before and after '.'
            for (long long i = 1; i < bigreals.size(); ++i) {
                if (bigreals[i] != '.')
                    integer += bigreals[i];
                else if (bigreals[i] == '.') {
                    for (long long j = i + 1; j < bigreals.size(); ++j)
                        fraction += bigreals[j];
                    break;
                }
            }
            // if there is no sign i will begin to divide string from first character
        } else {
            for (long long i = 0; i < bigreals.size(); ++i) {
                if (bigreals[i] != '.')
                    integer += bigreals[i];
                else if (bigreals[i] == '.') {
                    for (long long j = i + 1; j < bigreals.size(); ++j)
                        fraction += bigreals[j];
                    break;
                }
            }
        }
        // if no integer as .23456789
        if (integer.size() == 0)
            integer = "0";
        // if no decimal as 1234567
        if (fraction.size() == 0)
            fraction = "0";
    }
}

bool BigReal:: isValidReal (string realNumber) {
    // check code validation
    int signs = 0, dot = 0; // counters to check number of sign and dots
    for (long long i = 0; i < realNumber.size(); ++i) {
        // if there is a sign increase sign to 1
        if ((realNumber[i] == '-' || realNumber[i] == '+') && i == 0 && signs == 0) {
            signs = 1;
            // if there is another sign return false
        } else if (((realNumber[i] == '-' || realNumber[i] == '+') && i != 0 && signs == 0) ||
                   ((realNumber[i] == '-' || realNumber[i] == '+') && i != 0 && signs != 0))
            return false;
        // if it's the first dot increase dot to 1
        else if (((realNumber[i] == '.') && dot == 0 && i == 0) || ((realNumber[i] == '.') && dot == 0 && i != 0))
            dot = 1;
        // if there ia another dot return false
        else if (((realNumber[i] == '.') && dot != 0) || (((realNumber.back() == '.') && dot == 0)))
            return false;
            /*if (isdigit(realNumber[i]))
                continue;
            else
                return false;*/
            // if there is any letter return false
        else if ((realNumber[i] >= 'a' && realNumber[i] <= 'z' || realNumber[i] >= 'A' && realNumber[i] <= 'Z'))
            return false;
    }
    // if nothing of this return true
    return true;
}


// check if both are equal or not
bool BigReal::operator==(BigReal &other) {
    if (other.integer == integer && other.fraction == fraction && other.s == s)
        return true;
    return false;
}
// check if first is greater than second
bool BigReal::operator>(BigReal &other) {
    // check validity
    if (other.isValidReal(other.bigreals) && isValidReal(bigreals)) {
        // check sign first
        if (s == '-' && other.s == '-') {
            // if second greater than first return true
            if (stoll(other.integer) > stoll(integer))
                return true;
            // if both integers are same we will check fraction if fraction second is greater return true
            else if ((stoll(other.integer) == stoll(integer)) &&
                     (((stoll(fraction) < stoll(other.fraction) && fraction[0] < other.fraction[0]) ||
                       ((stoll(fraction) > stoll(other.fraction) && fraction[0] < other.fraction[0])))))
                return true;
            else
                return false;
            // check sign
        } else if (s == '+' && other.s == '+') {
            // if second is greater return false
            if (stoll(other.integer) > stoll(integer))
                return false;
            // if first are greater return true
            else if (stoll(other.integer) < stoll(integer))
                return true;
            // if both integers equal but fraction first is larger return true
            else if ((stoll(other.integer) == stoll(integer)) &&
                     (((stoll(fraction) > stoll(other.fraction) && fraction[0] > other.fraction[0]) ||
                       ((stoll(fraction) < stoll(other.fraction) && fraction[0] > other.fraction[0])))))
                return true;
            else
                return false;
            // if different signs
        } else if (s == '-' && other.s == '+')
            return false;
        else if (s == '+' && other.s == '-')
            return true;
    } else
        throw ("INVALID\n");
}
// check if first is less than second
bool BigReal::operator<(BigReal &other) {
    // check validity
    if (other.isValidReal(other.bigreals) && isValidReal(bigreals)) {
        // check sign first
        if (s == '-' && other.s == '-') {
            // if second less than first return true
            if (stoll(other.integer) < stoll(integer))
                return true;
            // if both integers are same we will check fraction if fraction second is less return true
            else if ((stoll(other.integer) == stoll(integer)) && ((stoll(fraction) > stoll(other.fraction) ||
                                                                   ((stoll(fraction) < stoll(other.fraction) &&
                                                                     fraction[0] > other.fraction[0])))))
                return true;
            else
                return false;
            // check sign first
        } else if (s == '+' && other.s == '+') {
            // if second is less return false
            if (stoll(other.integer) < stoll(integer))
                return false;
            // if both integers equal but fraction second is greater return true
            else if ((stoll(other.integer) == stoll(integer)) &&
                     (((stoll(fraction) < stoll(other.fraction) && fraction[0] < other.fraction[0]) ||
                       ((stoll(fraction) > stoll(other.fraction) && fraction[0] < other.fraction[0])))))
                return true;
            else
                return false;
            // if different signs
        } else if (s == '-' && other.s == '+')
            return true;
        else if (s == '+' && other.s == '-')
            return false;
    } else
        throw ("INVALID\n");
}

int BigReal::size() {
    return bigreals.size();
}

char BigReal::sign() {
    if(bigreals.front()=='+' || bigreals.front()=='-')
        return bigreals.front();
    else
        return '+' ;
}

string removeLeadingZeros(string& number){
    int i = 0;
    while(number[i]=='0' && i<number.length())
        ++i;
    return (i==number.length()? "0" :number.substr(i));
}

BigReal &BigReal::operator=(const BigReal &other) {
    integer = other.integer;
    fraction = other.fraction;
    s = other.s;
    return *this;
}

BigReal BigReal::operator+(BigReal &other) {
    if (isValidReal(other.bigreals)) {
        BigReal result ;
        result.integer="";
        int carry = 0;
        if (s == other.s) {
            if (other.fraction.size() > fraction.size()) {
                result.fraction = other.fraction.substr(fraction.size(), other.fraction.size() - 1);
            } else {
                result.fraction = fraction.substr(other.fraction.size(), fraction.size() - 1);
            }
            int between = min(fraction.size(), other.fraction.size());
            for (int i = between - 1; i >= 0; i--) {
                int su = carry + (fraction[i] - '0') + (other.fraction[i] - '0');
                string t = to_string(su);
                if (t.size() > 1) {
                    carry = 1;
                } else
                    carry = 0;
                result.fraction = t[t.size() - 1] + result.fraction;
            }
            if (other.integer.size() > integer.size()) {
                integer = string(other.integer.size() - integer.size(), '0') + integer;
            } else
                other.integer = string(integer.size() - other.integer.size(),'0') + other.integer;

            int between1 = min(integer.size(), other.integer.size());
            for (int i = between1 - 1; i >= 0; i--) {
                int ss = carry + (integer[i] - '0') + (other.integer[i] - '0');
                string tt = to_string(ss);
                if (tt.size() > 1) {
                    carry = 1;
                } else
                    carry = 0;
                result.integer = tt[tt.size() - 1] + result.integer;
                if (carry == 1 && i == 0)
                    result.integer = '1' + result.integer;
            }
            if (other.s == s && s == '-')
                result.s = '-';

        }else {
            int carry = 0, change = 0;
            removeLeadingZeros(this->integer);
            removeLeadingZeros(other.integer);
            string num1 = this->integer, frac1 = this->fraction, num2 = other.integer, frac2 = other.fraction;
            while (frac1.length() < frac2.length()) {
                frac1 += '0';
            }
            while (frac2.length() < frac1.length()) {
                frac2 += '0';
            }
            result.fraction.clear(),result.integer.clear();
            string fractionalResult;
            int a = frac1.size()-1, b = frac2.size()-1;
            while(a>=0 || b>=0){
                int digit = (a >= 0 ? frac1[a] - '0' : 0) - (b >= 0 ? frac2[b] - '0' : 0) - carry;
                if (digit < 0) {
                    carry = 1;
                    digit += 10;
                } else {
                    carry = 0;
                }
                result.fraction = to_string(digit) + result.fraction;
                a--;
                b--;
                if (carry == 1) change = 1;
            }
            removeLeadingZeros(fractionalResult);


            bool neg = false;
            if(num1.length() < num2.length() || (num1.length() == num2.length() && num1 < num2)) {
                swap(num1, num2);
                neg = true;
            }

            int i = num1.length()-1, j = num2.length()-1;
            while(i>=0 || j>=0){
                int digit = (i >= 0 ? num1[i] - '0' : 0) - (j >= 0 ? num2[j] - '0' : 0) - carry;
                if(digit == 0 && change == 1){
                    i--;
                    j--;
                    continue;
                }
                if (change == 1) {
                    digit--;
                    change = 0;
                }
                if (digit < 0) {
                    carry = 1;
                    digit += 10;

                } else {
                    carry = 0;
                }

                result.integer = to_string(digit) + result.integer;
                i--;
                j--;
            }
            removeLeadingZeros(result.integer);
            if(neg){
                result.integer = '-' + result.integer;
            }
            return BigReal(result.integer+'.'+result.fraction);

        }


        return result;
    } else
        throw ("INVALID");
}

BigReal BigReal::operator-(BigReal& other) {
    if (isValidReal(other.bigreals)) {
        BigReal result;
        if (s == other.s) {
            int carry = 0, change = 0;
            removeLeadingZeros(this->integer);
            removeLeadingZeros(other.integer);
            string num1 = this->integer, frac1 = this->fraction, num2 = other.integer, frac2 = other.fraction;
            while (frac1.length() < frac2.length()) {
                frac1 += '0';
            }
            while (frac2.length() < frac1.length()) {
                frac2 += '0';
            }
            result.fraction.clear(),result.integer.clear();
            string fractionalResult;
            int a = frac1.size()-1, b = frac2.size()-1;
            while(a>=0 || b>=0){
                int digit = (a >= 0 ? frac1[a] - '0' : 0) - (b >= 0 ? frac2[b] - '0' : 0) - carry;
                if (digit < 0) {
                    carry = 1;
                    digit += 10;
                } else {
                    carry = 0;
                }
                result.fraction = to_string(digit) + result.fraction;
                a--;
                b--;
                if (carry == 1) change = 1;
            }
            removeLeadingZeros(fractionalResult);


            bool neg = false;
            if(num1.length() < num2.length() || (num1.length() == num2.length() && num1 < num2)) {
                swap(num1, num2);
                neg = true;
            }

            int i = num1.length()-1, j = num2.length()-1;
            while(i>=0 || j>=0){
                int digit = (i >= 0 ? num1[i] - '0' : 0) - (j >= 0 ? num2[j] - '0' : 0) - carry;
                if(digit == 0 && change == 1){
                    i--;
                    j--;
                    continue;
                }
                if (change == 1) {
                    digit--;
                    change = 0;
                }
                if (digit < 0) {
                    carry = 1;
                    digit += 10;

                } else {
                    carry = 0;
                }

                result.integer = to_string(digit) + result.integer;
                i--;
                j--;
            }
            removeLeadingZeros(result.integer);
            if(neg){
                result.integer = '-' + result.integer;
            }
            return BigReal(result.integer+'.'+result.fraction);

        }
    }
    else {
        BigReal result;
        result.integer="";
        int carry = 0;
        if (other.fraction.size() > fraction.size()) {
            result.fraction = other.fraction.substr(fraction.size(), other.fraction.size() - 1);
        } else {
            result.fraction = fraction.substr(other.fraction.size(), fraction.size() - 1);
        }
        int between = min(fraction.size(), other.fraction.size());
        for (int i = between - 1; i >= 0; i--) {
            int su = carry + (fraction[i] - '0') + (other.fraction[i] - '0');
            string t = to_string(su);
            if (t.size() > 1) {
                carry = 1;
            } else
                carry = 0;
            result.fraction = t[t.size() - 1] + result.fraction;
        }
        if (other.integer.size() > integer.size()) {
            integer = string(other.integer.size() - integer.size(), '0') + integer;
        } else
            other.integer = string(integer.size() - other.integer.size(), '0') + other.integer;

        int between1 = min(integer.size(), other.integer.size());
        for (int i = between1 - 1; i >= 0; i--) {
            int ss = carry + (integer[i] - '0') + (other.integer[i] - '0');
            string tt = to_string(ss);
            if (tt.size() > 1) {
                carry = 1;
            } else
                carry = 0;
            result.integer = tt[tt.size() - 1] + result.integer;
            if (carry == 1 && i == 0)
                result.integer = '1' + result.integer;
        }
        if (other.s == s && s == '-')
            result.s = '-';

    }
}

ostream &operator<<(ostream &out, BigReal &num) {
    if (num.isValidReal(num.bigreals)) {
        if (num.bigreals[0] == '-')
            num.bigreals = num.bigreals[0] + num.integer + "." + num.fraction;
        else
            num.bigreals = num.integer + "." + num.fraction;
        out << num.bigreals << endl;
        out << num.s << endl;
        out << num.integer << endl << num.fraction << endl;
        return out;
    } else {
        out << "wrong real number\n+0.0\n";
        return out;
    }
}