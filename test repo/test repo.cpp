#include <iostream>
#include <stack>
#include <string>
#include <cctype>  // 用於isdigit函數
using namespace std;

// 函數來判斷是否為運算符
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// 函數來判斷運算符的優先級
int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}

// 函數來將中序表示法轉換為後序表示法
string infixToPostfix(const string& infix, bool& isBalanced) {
    stack<char> s;
    string postfix;
    int balance = 0; // 用來檢查括號對稱性
    for (char c : infix) {
        if (isdigit(c)) {
            postfix += c;
        }
        else if (c == '(') {
            s.push(c);
            balance++;
        }
        else if (c == ')') {
            balance--;
            if (balance < 0) {
                isBalanced = false;
                return "";
            }
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                s.pop();
            }
            s.pop(); // 移除 '('
        }
        else if (isOperator(c)) {
            while (!s.empty() && precedence(s.top()) >= precedence(c)) {
                postfix += s.top();
                s.pop();
            }
            s.push(c);
        }
    }
    if (balance != 0) {
        isBalanced = false;
        return "";
    }
    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }
    isBalanced = true;
    return postfix;
}

// 函數來計算後序表示法的結果
int evaluatePostfix(const string& postfix) {
    stack<int> s;
    for (char c : postfix) {
        if (isdigit(c)) {
            s.push(c - '0'); // 將字元轉換為整數並壓入堆疊
        }
        else if (isOperator(c)) {
            int operand2 = s.top(); s.pop(); // 第二個操作數
            int operand1 = s.top(); s.pop(); // 第一個操作數
            int result;
            switch (c) {
            case '+': result = operand1 + operand2; break;
            case '-': result = operand1 - operand2; break;
            case '*': result = operand1 * operand2; break;
            case '/': result = operand1 / operand2; break;
            }
            s.push(result); // 將結果壓入堆疊
        }
    }
    return s.top(); // 最終結果
}

int main() {
    char end;
    do {
        string infix;
        cout << "請輸入一個包含以下符號的運算式+, -, *, /, (, )，以及數字1~9 ex.(1+2)*(3+4): ";
        cin >> infix;

        // 檢查括號對稱性並將中序表示法轉換為後序表示法
        bool isBalanced;
        string postfix = infixToPostfix(infix, isBalanced);

        if (isBalanced) {
            cout << infix << " 運算式的左右括號對稱" << endl;
            cout << infix << " 運算式的後序表示法為: " << postfix << endl;

            // 計算後序表示法的結果
            int result = evaluatePostfix(postfix);
            cout << infix << " 運算式的運算結果為: " << result << endl;
        }
        else {
            cout << infix << " 運算式的左右括號不對稱" << endl;
        }

        cout << "是否繼續輸入運算式 (Y/y 繼續, N/n 離開): ";
        cin >> end;
    } while (end == 'Y' || end == 'y');

    return 0;
}
