#include <iostream>
#include <fstream>
#include <string>
#include "calculator.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <testFile>" << endl;
        return 1;
    }
    ifstream file(argv[1]);
    if (!file) {
        cerr << "Error: Unable to open file: " << argv[1] << endl;
        return 1;
    }
    const string fixedNum = "-123.456";
    string line;
    while (getline(file, line)) {
        cout << "Input: " << line << endl;
        if (isValidDouble(line)) {
            string result = addDoubles(line, fixedNum);
            cout << "Double valid. Result sum: " << fixedNum << " = " << result << endl;
        } else {
            cout << "Error: Double invalid." << endl;
        }
    }
    return 0;
}
