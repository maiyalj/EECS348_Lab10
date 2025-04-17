#include "calculator.hpp"
#include <cctype>
#include <algorithm>
using namespace std;

string stripSign(const string &s, char &sign) {
    if (s[0] == '+' || s[0] == '-') {
        sign = s[0];
        return s.substr(1);
    }
    sign = '+';
    return s;
}
void addZeros(string &a, string &b) {
    auto pointA = a.find('.');
    auto pointB = b.find('.');
    if (pointA == string::npos) {
        a += ".0";
        pointA = a.find('.');
    }
    if (pointB == string::npos) {
        b += ".0";
        pointB = b.find('.');
    }
    int lengthAInt = pointA;
    int lengthBInt = pointB;
    int lengthADec = a.size() - pointA - 1;
    int lengthBDec = b.size() - pointB - 1;
    if (lengthAInt < lengthBInt) 
        a.insert(0, lengthBInt - lengthAInt, '0');
    else
        b.insert(0, lengthAInt - lengthBInt, '0');
    if (lengthADec < lengthBDec)
        a.append(lengthBDec - lengthADec, '0');
    else
        b.append(lengthADec - lengthBDec, '0');
}
string add(const string &a, const string &b) {
    string result;
    string aa = a, bb = b;
    addZeros(aa, bb);
    int carry = 0;
    for (int i = aa.size() - 1; i >= 0; --i) {
        if (aa[i] == '.') {
            result.push_back('.');
            continue;
        }
        int digitSum = (aa[i] - '0') + (bb[i] - '0') + carry;
        carry = digitSum / 10;
        result.push_back((digitSum % 10) + '0');
    }
    if (carry > 0)
        result.push_back(carry + '0');
    reverse(result.begin(), result.end());
    while (result.back() == '0') result.pop_back();
    if (result.back() == '.') result.pop_back();
    return result;
}
int compareAbsVal(const string &a, const string &b) {
    string aa = a, bb = b;
    addZeros(aa, bb);
    if (aa == bb) return 0;
    return (aa > bb) ? 1 : -1;
}
string subtract(const string &a, const string &b) {
    string aa = a, bb = b;
    addZeros(aa, bb);
    bool negative = false;
    if (compareAbsVal(aa, bb) < 0) {
        swap(aa, bb);
        negative = true;
    }
    string result;
    int borrow = 0;
    for (int i = aa.size() - 1; i >= 0; --i) {
        if (aa[i] == '.') {
            result.push_back('.');
            continue;
        }
        int diff = (aa[i] - '0') - (bb[i] - '0') - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.push_back(diff + '0');
    }
    reverse(result.begin(), result.end());
    while (result.size() > 1 && result[0] == '0' && result[1] != '.') result.erase(0, 1);
    while (result.back() == '0') result.pop_back();
    if (result.back() == '.') result.pop_back();
    return negative ? "-" + result : result;
}
string addDoubles(const string &a, const string &b) {
    char signA, signB;
    string aa = stripSign(a, signA);
    string bb = stripSign(b, signB);
    if (signA == signB) {
        string sum = add(aa, bb);
        return (signA == '-') ? "-" + sum : sum;
    } else {
        string diff = subtract(aa, bb);
        return diff;
    }
}
bool isValidDouble(const string &s) {
    if (s.empty()) return false;
    int i = 0;
    if (s[i] == '+' || s[i] == '-') i++;
    bool digits = false;
    while (i < s.size() && isdigit(s[i])) {
        digits = true;
        i++;
    }
    if (i == s.size()) return digits;
    if (s[i] == '.') {
        i++;
    }
    if (i==s.size()) return digits;
    if (s[i] == '.') {
        i++;
        bool decimal = false;
        while (i < s.size() && isdigit(s[i])) {
            decimal = true;
            i++;
        }
        return digits && decimal && i == s.size();
    }
    return false;
}
