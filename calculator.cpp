#include "calculator.hpp"
#include <cctype>
#include <algorithm>
using namespace std;

// function to remove the sign from the string and return just the number 
string stripSign(const string &s, char &sign) {
    // check if there is a sign 
    if (s[0] == '+' || s[0] == '-') {
        sign = s[0];
        // store the sign 
        return s.substr(1);
    }
    // if there is no sign, make the sign positive
    sign = '+';
    // return the string without the sign 
    return s;
}
// function to add zeros to the front or end of a string
// allows the int and dec to be the same length for easier calculations
void addZeros(string &a, string &b) {
    // find decimal point in a and b
    auto pointA = a.find('.');
    auto pointB = b.find('.');
    // add '.0' if the string doesn't have a decimal point 
    if (pointA == string::npos) {
        a += ".0";
        pointA = a.find('.');
    }
    if (pointB == string::npos) {
        b += ".0";
        pointB = b.find('.');
    }
    // find the lengths of the int and dec
    int lengthAInt = pointA;
    int lengthBInt = pointB;
    int lengthADec = a.size() - pointA - 1;
    int lengthBDec = b.size() - pointB - 1;
    // add zeros to match the length of integers
    if (lengthAInt < lengthBInt) 
        a.insert(0, lengthBInt - lengthAInt, '0');
    else
        b.insert(0, lengthAInt - lengthBInt, '0');
    // add zeros to match the length of decimals 
    if (lengthADec < lengthBDec)
        a.append(lengthBDec - lengthADec, '0');
    else
        b.append(lengthADec - lengthBDec, '0');
}
// function to add two positive strings 
string add(const string &a, const string &b) {
    string result;
    // create copy
    string aa = a, bb = b;
    addZeros(aa, bb);
    int carry = 0;
    // process digits right to left 
    for (int i = aa.size() - 1; i >= 0; --i) {
        if (aa[i] == '.') {
            result.push_back('.');
            continue;
        }
        // find sum of digits found 
        int digitSum = (aa[i] - '0') + (bb[i] - '0') + carry;
        carry = digitSum / 10;
        // store digit 
        result.push_back((digitSum % 10) + '0');
    }
    // remaining carry
    if (carry > 0)
        result.push_back(carry + '0');
    // process digits left to right
    reverse(result.begin(), result.end());
    // remove excess zeros 
    while (result.back() == '0') result.pop_back();
    if (result.back() == '.') result.pop_back();
    return result;
}
// function to compare absolute values 
int compareAbsVal(const string &a, const string &b) {
    string aa = a, bb = b;
    // make same length and equal 
    addZeros(aa, bb);
    if (aa == bb) return 0;
    // compare strings 
    return (aa > bb) ? 1 : -1;
}
// function to subtract two positive strings 
string subtract(const string &a, const string &b) {
    string aa = a, bb = b;
    addZeros(aa, bb);
    bool negative = false;
    // make sure aa is bigger 
    if (compareAbsVal(aa, bb) < 0) {
        // otherwise swap to bb 
        swap(aa, bb);
        negative = true;
    }
    string result;
    int borrow = 0;
    // process right to left 
    for (int i = aa.size() - 1; i >= 0; --i) {
        if (aa[i] == '.') {
            result.push_back('.');
            continue;
        }
        // calculate difference 
        int diff = (aa[i] - '0') - (bb[i] - '0') - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        // store digit 
        result.push_back(diff + '0');
    }
    // process left to right 
    reverse(result.begin(), result.end());
    // remove unecessary zeros 
    while (result.size() > 1 && result[0] == '0' && result[1] != '.') result.erase(0, 1);
    while (result.back() == '0') result.pop_back();
    if (result.back() == '.') result.pop_back();
    // add negative sign if necessary 
    return negative ? "-" + result : result;
}
// function to add two strings 
string addDoubles(const string &a, const string &b) {
    char signA, signB;
    // remove signs
    string aa = stripSign(a, signA);
    string bb = stripSign(b, signB);
    // if the strings have the same sign, add
    // if the strings have different signs, subtract 
    if (signA == signB) {
        string sum = add(aa, bb);
        return (signA == '-') ? "-" + sum : sum;
    } else {
        string diff = subtract(aa, bb);
        return diff;
    }
}
// function that declares whether the double is valid or invalid 
bool isValidDouble(const string &s) {
    // if string is empty, return false 
    if (s.empty()) return false;
    int i = 0;
    // check sign 
    if (s[i] == '+' || s[i] == '-') i++;
    // check for digits before decimal 
    bool digitBeforeDec = false;
    while (i < s.size() && isdigit(s[i])) {
        digitBeforeDec = true;
        i++;
    }
    bool hasDec = false;
    // check for digits after decimal 
    bool digitAfterDec = false;
    if (i < s.size() && s[i] == '.') {
        hasDec = true;
        i++;
        // make sure there is a digit after the decimal 
        while (i < s.size() && isdigit(s[i])) {
            digitAfterDec = true;
            i++;
        }
    }
    // return false if there is no digit after the decimal 
    if (hasDec && !digitAfterDec) {
        return false;
    }
    // digits before or after decimal 
    if (i != s.size()) return false;
    return digitBeforeDec || digitAfterDec;
}

