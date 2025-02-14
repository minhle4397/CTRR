#include "postfix_prefix_funch.h"
int main () {
    string infix;
    cout << "Nhap bieu thuc toan hoc: ";
    getline(cin, infix);
    string infix_bool;
    cout << "Nhap bieu thuc logic: ";
    getline(cin, infix_bool);
    string varlue;
    cout << "Nhap gia tri logic cho cac bien: ";
    getline(cin, varlue);
    string postfix = infixToPostfix(infix);
    string prefix = infixToPrefix(infix);
    string res = PostfixPrefixCalculator(postfix);
    cout << "Infix: " << infix << endl;
    cout << "Postfix: " << postfix << endl;
    cout << "Prefix: " << prefix << endl;
    cout << "Result: " << res << endl;

    string postfix_bool = bool_infixToPostfix(infix);
    string prefix_bool = bool_infixToPrefix(infix);
    string res_bool = LogicPostfixPrefixCalculator(postfix_bool,varlue);
    cout << "Infix Logic: " << infix << endl;
    cout << "Postfix Logic: " << postfix_bool << endl;
    cout << "Prefix Logic: " << prefix_bool << endl;
    cout << "Result Logic: " << res_bool << endl;
    return 0;
}
