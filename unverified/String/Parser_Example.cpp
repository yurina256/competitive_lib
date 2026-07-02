#include <iostream>
#include <string>
#include "Parser.cpp"

using namespace std;

int main() {
    cout << "=== Recursive Descent Parser Example ===" << endl;

    // 典型的な式の評価
    // 1+2*(3+4)-5 = 1 + 2*7 - 5 = 10
    string s = "1+2*(3+4)-5";
    Parser parser1(s);
    try {
        long long res = parser1.expr();
        cout << "Expression: " << s << endl;
        cout << "Result: " << res << " (Expected: 10)" << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    cout << endl;

    // ゼロ除算のテスト
    string s2 = "10/(2-2)";
    Parser parser2(s2);
    try {
        cout << "Expression: " << s2 << endl;
        long long res = parser2.expr();
        cout << "Result: " << res << endl;
    } catch (const exception& e) {
        cout << "Caught expected error: " << e.what() << endl;
    }
    cout << endl;

    // 不正な文法のテスト
    string s3 = "3+(4*5";
    Parser parser3(s3);
    try {
        cout << "Expression: " << s3 << endl;
        long long res = parser3.expr();
        cout << "Result: " << res << endl;
    } catch (const exception& e) {
        cout << "Caught expected error: " << e.what() << endl;
    }

    return 0;
}

/*
出力結果:
=== Recursive Descent Parser Example ===
Expression: 1+2*(3+4)-5
Result: 10 (Expected: 10)

Expression: 10/(2-2)
Caught expected error: Division by zero

Expression: 3+(4*5)
Caught expected error: Unexpected character: expected ')', got ''
*/
