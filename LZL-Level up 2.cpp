#include<iostream>
#include<cmath>
#include<stack>
#include<algorithm>
#include<cstring>
using namespace std;

// 计算10的(n-1)次方
double Count(int n) {
    int Bignumber = 1;
    for (int i = 1; i < n; i++) {
        Bignumber *= 10;
    }
    return Bignumber;
}

double calculate(string s, int start, int end) {
    double TemporarySum = 0;  // 当前数字的累加和
    int Number = 0;           // 当前数字的位数
    stack<double> NumStack;
    stack<char> OpStack;

    for (int i = start; i <= end; i++) {
        if (s[i] >= '0' && s[i] <= '9') {  // 解析数字
            Number++;
        } else {
            // 如果之前有未解析的数字，先压入栈
            if (Number != 0) {
                int tempCount = Number;
                for (int j = i - Number; j < i; j++) {
                    TemporarySum += (s[j] - '0') * Count(tempCount);
                    tempCount--;
                }
                NumStack.push(TemporarySum);
                TemporarySum = 0;
                Number = 0;
            }

            if (s[i] == '(') {  // 处理左括号：递归计算括号内
                int bracketCount = 1;
                int MarkTwo = i + 1;
                while (bracketCount > 0) {
                    if (s[MarkTwo] == '(') bracketCount++;
                    else if (s[MarkTwo] == ')') bracketCount--;
                    MarkTwo++;
                }
                MarkTwo--;  // 右括号位置
                double bracketResult = calculate(s, i + 1, MarkTwo - 1);
                NumStack.push(bracketResult);
                i = MarkTwo;  // 跳过整个括号（包括右括号）
            } else if (s[i] == ')') {  // 右括号：不处理，交给外层处理
                continue;
            } else {  // 处理运算符：+ - * /
                // 弹出栈中优先级更高或相等的运算符计算
                while (!OpStack.empty() && OpStack.top() != '(') {
                    char topOp = OpStack.top();
                    if ((topOp == '*' || topOp == '/') || 
                        ((topOp == '+' || topOp == '-') && (s[i] == '+' || s[i] == '-'))) {
                        double b = NumStack.top(); NumStack.pop();
                        double a = NumStack.top(); NumStack.pop();
                        double res;
                        switch (topOp) {
                            case '+': res = a + b; break;
                            case '-': res = a - b; break;
                            case '*': res = a * b; break;
                            case '/': res = a / b; break;
                        }
                        NumStack.push(res);
                        OpStack.pop();
                    } else {
                        break;
                    }
                }
                OpStack.push(s[i]);  // 当前运算符入栈
            }
        }
    }

    // 处理最后一个数字
    if (Number > 0) {
        int tempCount = Number;
        for (int j = end - Number + 1; j <= end; j++) {
            TemporarySum += (s[j] - '0') * Count(tempCount);
            tempCount--;
        }
        NumStack.push(TemporarySum);
    }

    // 处理栈中剩余的运算符
    while (!OpStack.empty()) {
        char op = OpStack.top(); OpStack.pop();
        double b = NumStack.top(); NumStack.pop();
        double a = NumStack.top(); NumStack.pop();
        double res;
        switch (op) {
            case '+': res = a + b; break;
            case '-': res = a - b; break;
            case '*': res = a * b; break;
            case '/': res = a / b; break;
        }
        NumStack.push(res);
    }

    return NumStack.top();
}

int main() {
    string s1;
    cout << "Please enter your mathematical expression: " << endl;
    cin >> s1;
    double result = calculate(s1, 0, s1.size() - 1);
    cout << "Here is your result: " << endl;
    cout << result << endl;
    return 0;
}