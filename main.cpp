#include <iostream>
#include <fstream>
#include <string>
#include "calculator.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <test_file>" << endl;
        return 1;
    }
    // open file 
    ifstream file(argv[1]);
    if (!file) {
        cerr << "Error: Unable to open file: " << argv[1] << endl;
        return 1;
    }
    // set fixed number 
    const string fixedNum = "-123.456";
    string line;
    // process lines in file 
    while (getline(file, line)) {
        cout << "Input: " << line << endl;
        // declare valid or invalid 
        if (isValidDouble(line)) {
            string result = addDoubles(line, fixedNum);
            cout << "Double valid.\nResult: " << fixedNum << " = " << result << endl;
        } else {
            cout << "Error: Double invalid." << endl;
        }
    }
    return 0;
}
