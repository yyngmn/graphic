#include <string>

using namespace std;

const double EPS = 0.000001;

struct Stack {
    double number;
    char znak;
    Stack* next;
};

void push(Stack*& top, double a, char b) {
    Stack *p = (Stack*)malloc(sizeof(Stack));
    (*p).number = a;
    (*p).znak = b;
    (*p).next = top;
    top = p;
}

Stack pop(Stack*& top) {
    Stack temp = *top;
    top = (*top).next;
    return temp;
}

Stack *top1 = nullptr, *top2 = nullptr;

int priority(char ch) {
    int prior;
    if (ch == '+' || ch == '-') {
        prior = 1;
    }
    if (ch == '/' || ch == '*') {
        prior = 2;
    }
    if (ch == '(') {
        prior = 0;
    }
    return prior;
}
int apply(char znak) {
    double a, b, c;
    b = pop(top1).number;
    a = pop(top1).number;
    if (znak == '+') {
        c = a + b;
    }
    if (znak == '-') {
        c = a - b;
    }
    if (znak == '/') {
        if (abs(b) < EPS) {
            return -1;

        } else {
            c = a / b;
        }
    }
    if (znak == '*') {
        c = a * b;
    }
    push(top1, c, '@');
}

bool error(string s) {
    int temp = 0;

    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
            temp++;
        }
        if (s[i] == ')') {
            temp--;
        }
        if (temp < 0) {
            return 1;
        }
    }

    if (temp != 0) {
        return 1;
    }
    if (s[0] == '*' || s[0] == '/' || s[0] == '+') {
        return 1;
    }
    if (s[s.length() - 1] == '+' || s[s.length() - 1] == '*' || s[s.length() - 1] == '/') {
        return 1;
    }

    for (int i = 0; i < s.length() - 1; i++) {
        if (s[i] == '(' && s[i + 1] == '+' ||
            s[i] == '(' && s[i + 1] == '*' ||
            s[i] == '(' && s[i + 1] == '/' ||
            s[i] == '-' && s[i + 1] == ')') {
            return 1;
        }
    }

    for (int i = 0; i < s.length(); i++) {
        if (s[i] <= '0' && s[i] >= '9' &&
            s[i] != '+' && s[i] != '-' && s[i] != '/' && s[i] != '*' && s[i] != '.') {
            return 1;
        }
    }

    for (int i = 0; i < s.length() - 1; i++) {
        if (s[i] == '+' && s[i + 1] == '+' ||
            s[i] == '-' && s[i + 1] == '+' ||
            s[i] == '*' && s[i + 1] == '+' ||
            s[i] == '/' && s[i + 1] == '+' ||
            s[i] == '+' && s[i + 1] == '-' ||
            s[i] == '-' && s[i + 1] == '-' ||
            s[i] == '*' && s[i + 1] == '-' ||
            s[i] == '/' && s[i + 1] == '-' ||
            s[i] == '+' && s[i + 1] == '/' ||
            s[i] == '-' && s[i + 1] == '/' ||
            s[i] == '/' && s[i + 1] == '/' ||
            s[i] == '*' && s[i + 1] == '/' ||
            s[i] == '+' && s[i + 1] == '*' ||
            s[i] == '-' && s[i + 1] == '+' ||
            s[i] == '*' && s[i + 1] == '*' ||
            s[i] == '/' && s[i + 1] == '*') {
            return 1;
        }
    }
    return 0;
}

int calculate(string s, double &ans) {
    string ss;
    if (s[0] == '-') {
        s = '0' + s;
        ss = '0';
    }

    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(' && s[i + 1] == '-') {
            ss = ss + s[i] + '0';
        } else {
            ss += s[i];
        }
    }

    s = ss;

    if (error(s)) {
        return -1;
    }

    for (int i = 0; i < s.length(); i++) {

        if (s[i] >= '0' && s[i] <= '9') {
            double temp = 0;
            while (i < s.length() && s[i] >= '0' && s[i] <= '9') {
                temp = temp * 10 + (s[i] - '0');
                i++;
            }
            if (s[i] == '.'){
                int temp_cnt = 1;
                i++;
                while (i < s.length() && s[i] >= '0' && s[i] <= '9') {
                    temp = temp * 10 + (s[i] - '0');
                    temp_cnt*=10;
                    i++;
                }
                temp/=temp_cnt;
            }

            i--;
            push(top1, temp, '@');
        }
        if (s[i] == '(') {
            push(top2, 0.0, s[i]);
        }
        if (s[i] == ')') {
            while ((*top2).znak != '(') {
                apply(pop(top2).znak);
            }
            pop(top2);
        }
        if (s[i] == '/' || s[i] == '*' || s[i] == '+' || s[i] == '-') {
            while (top2 != nullptr && priority(s[i]) <= priority((*top2).znak)) {
                apply(pop(top2).znak);
            }
            push(top2, 0.0, s[i]);
        }
    }

    while (top2 != nullptr) {
        apply(pop(top2).znak);
    }
    ans = pop(top1).number;
}
//poland.h
