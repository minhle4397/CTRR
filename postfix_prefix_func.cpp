#include "postfix_prefix_funch.h"
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool isBoolOperator(string str) {
    return str == "->" || str == "<->" || str == "|" || str == "&" || str == "~";
   
}
int getPriority(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '^') return 3;
    return 0;
}
int bool_Priority(const string& str) {
    if (str == "->") return 2;
    else if (str == "<->") return 1;
    else if (str == "|" || str == "&") return 3;
    else if (str == "~") return 4;
    else return -1;
    
}
bool isOperand(char c) {
    return isalnum(c) && !isOperator(c);
}
string removeExtraSpaces(string str) {
    string result = "";
    for (unsigned i = 0; i < str.length(); i++) {
        if (str[i] != ' ' || (i > 0 && str[i - 1] != ' ')) {
            result += str[i];
        }
    }
    return result;
}
double applyOperator(char op, double operand1, double operand2) {
    if (op == '+') return operand1 + operand2;
    if (op == '-') return operand1 - operand2;
    if (op == '*') return operand1 * operand2;
    if (op == '/') return operand1 / operand2;
    if (op == '^') return pow(operand1, operand2);
    return 0;
}
double roundToFourDecimalPlaces(double number) {
    double roundedNumber = round(number * 10000) / 10000; // Làm tròn đến 4 chữ số thập phân
    return roundedNumber;
}
bool hasOddDecimal(double number) {
    int integerPart = static_cast<int>(number); // Lấy phần nguyên của số
    double decimalPart = number - integerPart; // Lấy phần thập phân của số

    // Kiểm tra xem phần thập phân có chứa số lẻ hay không
    while (decimalPart > 0) {
        int digit = static_cast<int>(decimalPart * 10); // Lấy chữ số thập phân đầu tiên
        if (digit % 2 != 0) {
            return true; // Số lẻ thập phân được tìm thấy
        }
        decimalPart = decimalPart * 10 - digit; // Lấy phần thập phân còn lại
    }

    return false; // Không có số lẻ thập phân
}
string removeTrailingZeros(double number) {
    string numberString = to_string(number);

    size_t decimalPointPos = numberString.find('.');
    if (decimalPointPos != string::npos) {
        size_t lastNonZeroPos = numberString.find_last_not_of('0');

        if (lastNonZeroPos != string::npos && lastNonZeroPos > decimalPointPos) {
            numberString = numberString.substr(0, lastNonZeroPos + 1);
        }
        else {
            numberString = numberString.substr(0, decimalPointPos);
        }
    }

    return numberString;
}
bool bool_evaluate(bool operand1, bool operand2, string op) {
    if(op== "&") return operand1 && operand2;
    if(op== "|") return operand1 || operand2;
    if(op=="~") return !operand1;
    if(op=="->") return !operand1 || operand2;
    if (op == "<->") return (operand1 && operand2) || (!operand1 && !operand2);
    return false;
    
}
string infixToPostfix(string infix) {
    stack<char> s;
    string postfix = "";

    for (unsigned i = 0; i < infix.length(); i++) {
        char c = infix[i];

        // Nếu ký tự là toán hạng, thêm vào biểu thức hậu tố
        if (isOperand(c)) {
            postfix += c;
            if (i + 1 < infix.length() && !isOperand(infix[i + 1])) {
                postfix += " ";
            }
        }

        // Nếu ký tự là toán tử, đẩy vào ngăn xếp
        else if (isOperator(c)) {
            while (!s.empty() && getPriority(s.top()) >= getPriority(c)) {
                postfix += " ";
                postfix += s.top();
                s.pop();
                
            }
            s.push(c);
            postfix += " ";
            
        }

        // Nếu ký tự là dấu ngoặc trái, đẩy vào ngăn xếp
        else if (c == '(') {
            s.push(c);
        }

        // Nếu ký tự là dấu ngoặc phải, lấy toán tử ra khỏi ngăn xếp và thêm vào biểu thức hậu tố
        else if (c == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += " ";
                postfix += s.top();
                
                s.pop();
            }
            if (!s.empty()) {
                s.pop();
            }
        }
    }

    // Lấy toán tử còn lại trong ngăn xếp và thêm vào biểu thức hậu tố
    while (!s.empty()) {
        postfix += " ";
        postfix += s.top();
        
        s.pop();
    }
    return removeExtraSpaces(postfix);
    
}


string infixToPrefix(string infix) {
    stack<char> opStack;
    stack<string> expStack;
    string prefix = "";

    for (int i = infix.size() - 1; i >= 0; i--) {
        char c = infix[i];

        // Nếu là toán hạng, đưa vào stack biểu thức
        if (isOperand(c)) {
            string operand(1, c);
            while (i > 0 && isOperand(infix[i - 1])) {
                operand = infix[i - 1] + operand;
                i--;
            }
            expStack.push(operand);
        }

        // Nếu là dấu đóng ngoặc, đưa vào stack toán tử
        else if (c == ')') {
            opStack.push(c);
        }

        // Nếu là dấu mở ngoặc, đưa các toán tử từ stack vào biểu thức
        else if (c == '(') {
            while (!opStack.empty() && opStack.top() != ')') {
                string operand1 = expStack.top();
                expStack.pop();
                string operand2 = expStack.top();
                expStack.pop();
                string op(1, opStack.top());
                opStack.pop();
                string newExp = op + " " + operand1 + " " + operand2;
                expStack.push(newExp);
            }
            opStack.pop(); // Pop dấu đóng ngoặc
        }

        // Nếu là toán tử, đưa vào stack toán tử
        else if (isOperator(c)) {
            while (!opStack.empty() && getPriority(opStack.top()) > getPriority(c)) {
                string operand1 = expStack.top();
                expStack.pop();
                string operand2 = expStack.top();
                expStack.pop();
                string op(1, opStack.top());
                opStack.pop();
                string newExp = op + " " + operand1 + " " + operand2;
                expStack.push(newExp);
            }
            opStack.push(c);
        }
    }

    // Pop tất cả các toán tử còn lại trong stack
    while (!opStack.empty()) {
        string operand1 = expStack.top();
        expStack.pop();
        string operand2 = expStack.top();
        expStack.pop();
        string op(1, opStack.top());
        opStack.pop();
        string newExp = op + " " + operand1 + " " + operand2;
        expStack.push(newExp);
    }

    // Kết quả cuối cùng là biểu thức prefix
    prefix = expStack.top();
    return prefix;
}
string PostfixPrefixCalculator(string input) {
    stack<double> operandStack;

    if (input.empty()) {
        return "Invalid input!";
    }

    char firstChar = input[0];

    // Xác định xem input là postfix hay prefix
    if (isdigit(firstChar)) { // Postfix
        for (int i = 0; i < static_cast<int>(input.size()); i++) {
            char c = input[i];

            // Nếu là toán hạng, đưa vào stack toán hạng
            if (isdigit(c)) {
                string operandString(1, c);
                while (i < static_cast<int>(input.size()) - 1 && isdigit(input[i + 1])) {
                    operandString += input[i + 1];
                    i++;
                }
                double operand = stod(operandString);
                operandStack.push(operand);
            }

            // Nếu là toán tử, lấy 2 toán hạng từ stack và tính toán
            else if (isOperator(c)) {
                double operand2 = operandStack.top();
                operandStack.pop();
                double operand1 = operandStack.top();
                operandStack.pop();
                if (c == '/') {
                    if (operand2 == 0)
                        return "Invalid input!";
                    
                }
                double result = applyOperator(c, operand1, operand2);
                operandStack.push(result);
            }
        }
    }
    else if (isOperator(firstChar)) { // Prefix
        for (int i = static_cast<int>(input.size()) - 1; i >= 0; i--) {
            char c = input[i];

            // Nếu là toán hạng, đưa vào stack toán hạng
            if (isdigit(c)) {
                string operandString(1, c);
                while (i > 0 && isdigit(input[i - 1])) {
                    operandString = input[i - 1] + operandString;
                    i--;
                }
                double operand = stod(operandString);
                operandStack.push(operand);
            }

            // Nếu là toán tử, lấy 2 toán hạng từ stack và tính toán
            else if (isOperator(c)) {
                double operand1 = operandStack.top();
                operandStack.pop();
                double operand2 = operandStack.top();
                operandStack.pop();
                if (c == '/') {
                    if (operand2 == 0)
                        return "Invalid input!";
                }
                double result = applyOperator(c, operand1, operand2);
                operandStack.push(result);
            }
        }
    }
    else {
        return "Invalid input!";
    }

    // Kết quả cuối cùng là giá trị còn lại trên stack
    double result = operandStack.top();
    if (hasOddDecimal(result)) {
        result = roundToFourDecimalPlaces(result);
        return removeTrailingZeros(result);
       
    }
    else {
        int r = result;
        string s = to_string(r);
        return s;
        
    }
}
string removeParentheses(const string& input) {
    string result;

    for (char c : input) {
        if (c != '(' && c != ')') {
            result += c;
        }
    }

    return result;
}
string bool_infixToPostfix(string infix) {
    stack<string> s;
    string postfix = "";

    for (unsigned i = 0; i < infix.length(); i++) {
        string c;
        c.push_back(infix[i]);

        if (c == " ")
            continue;
        if (c == "-") {
            c.push_back(infix[i + 1]);
            i++;
        }
        if (c == "<") {
            c.push_back(infix[i + 1]);
            c.push_back(infix[i + 2]);
            i += 2;
        }
        // Nếu ký tự là toán hạng, thêm vào biểu thức hậu tố
        if (!isBoolOperator(c) && c!=")" && c!="(") {
            postfix += c;
           
        }

        // Nếu ký tự là toán tử, đẩy vào ngăn xếp
        else if (isBoolOperator(c)) {
            while (!s.empty() && bool_Priority(s.top()) >= bool_Priority(c)) {
                
                postfix += s.top();
                s.pop();

            }
            s.push(c);
            

        }

        // Nếu ký tự là dấu ngoặc trái, đẩy vào ngăn xếp
        else if (c == "(") {
            s.push(c);
        }

        // Nếu ký tự là dấu ngoặc phải, lấy toán tử ra khỏi ngăn xếp và thêm vào biểu thức hậu tố
        else if (c == ")") {
            while (!s.empty() && s.top() != "(") {
                
                postfix += s.top();

                s.pop();
            }
            if (!s.empty()) {
                s.pop();
            }
        }
    }

    // Lấy toán tử còn lại trong ngăn xếp và thêm vào biểu thức hậu tố
    while (!s.empty()) {
        
        postfix += s.top();

        s.pop();
    }
    return removeParentheses(postfix);
}
string bool_infixToPrefix(string infix) {
    stack<string> opStack;
    string prefix = "";

    for (int i = infix.length() - 1; i >= 0; i--) {
        string c;
        c.push_back(infix[i]);

        if (c == " ")
            continue;

        // Nếu là dấu trừ hoặc mũi tên, xử lý các ký tự liền kề
        if (c == "-" || c == ">") {
            if (i > 0) {
                c = infix.substr(i - 1, 2);
                i--;
            }
        }

        // Nếu là toán hạng, thêm vào kết quả
        if (!isBoolOperator(c) && c != "(" && c != ")") {
            prefix = c + prefix;
        }

        // Nếu là dấu đóng ngoặc, đưa vào stack toán tử
        else if (c == ")") {
            opStack.push(c);
        }

        // Nếu là dấu mở ngoặc, lấy các toán tử từ stack và thêm vào kết quả
        else if (c == "(") {
            while (!opStack.empty() && opStack.top() != ")") {
                prefix = opStack.top() + prefix;
                opStack.pop();
            }

            opStack.pop(); // Pop dấu đóng ngoặc
        }

        // Nếu là toán tử, đưa vào stack toán tử
        else if (isBoolOperator(c)) {
            while (!opStack.empty() && bool_Priority(opStack.top()) > bool_Priority(c)) {
                prefix = opStack.top() + prefix;
                opStack.pop();
            }
            opStack.push(c);
        }
    }

    // Lấy các toán tử còn lại trong stack và thêm vào kết quả
    while (!opStack.empty()) {
        prefix = opStack.top() + prefix;
        opStack.pop();
    }

    return prefix;
}
bool isVariable(const string& str) {
    for (char c : str) {
        if (!(c >= 'a' && c <= 'z')) {
            return false;
        }
    }
    return true;
}
string LogicPostfixPrefixCalculator(string input, string varlue) {
    stack<bool> operandStack;

    for (int i = input.size() - 1; i >= 0; --i) {
        string c = input.substr(i, 1);

        if (isBoolOperator(c)) {
            if (operandStack.size() < 2) {
                // Không đủ số lượng toán hạng để thực hiện phép toán
                return "FALSE";
            }

            bool operand2 = operandStack.top();
            operandStack.pop();

            bool operand1 = operandStack.top();
            operandStack.pop();

            bool result = bool_evaluate(operand1, operand2, c);
            operandStack.push(result);
        }
        else if (isVariable(c)) {
            size_t index = c[0] - 'a';
            if (index >= varlue.size()) {
                // Vị trí biến vượt quá kích thước chuỗi varlue
                return "FALSE";
            }

            bool value = varlue[index] == '1';
            operandStack.push(value);
        }
    }

    if (operandStack.size() != 1) {
        // Có thể còn các toán tử không được giải quyết
        return "FALSE";
    }

    if (operandStack.top())
        return "TRUE";
    else return "FALSE";
    
}

