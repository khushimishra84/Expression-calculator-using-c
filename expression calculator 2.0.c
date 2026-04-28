#include <stdio.h>
#include <ctype.h>

int values[100];
char ops[100];
int vtop = -1, otop = -1;

// push value stack
void pushValue(int x) {
    values[++vtop] = x;
}

// pop value stack
int popValue() {
    return values[vtop--];
}

// push operator stack
void pushOp(char x) {
    ops[++otop] = x;
}

// pop operator stack
char popOp() {
    return ops[otop--];
}

// precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// apply operation
int applyOp(int a, int b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

int main() {
    char exp[100];
    int i = 0;

    printf("Enter expression: ");
    scanf("%s", exp);

    while (exp[i] != '\0') {

        // if number (multi-digit support)
        if (isdigit(exp[i])) {
            int num = 0;
            while (isdigit(exp[i])) {
                num = num * 10 + (exp[i] - '0');
                i++;
            }
            pushValue(num);
            i--;
        }

        // opening bracket
        else if (exp[i] == '(') {
            pushOp(exp[i]);
        }

        // closing bracket
        else if (exp[i] == ')') {
            while (otop != -1 && ops[otop] != '(') {
                int b = popValue();
                int a = popValue();
                char op = popOp();
                pushValue(applyOp(a, b, op));
            }
            popOp(); // remove '('
        }

        // operator
        else {
            while (otop != -1 && precedence(ops[otop]) >= precedence(exp[i])) {
                int b = popValue();
                int a = popValue();
                char op = popOp();
                pushValue(applyOp(a, b, op));
            }
            pushOp(exp[i]);
        }

        i++;
    }

    // final evaluation
    while (otop != -1) {
        int b = popValue();
        int a = popValue();
        char op = popOp();
        pushValue(applyOp(a, b, op));
    }

    printf("Result = %d\n", popValue());

    return 0;
}