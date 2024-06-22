#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "calculator.h"

// ヘルパー関数：数式を解析して計算する
double evaluate(const char* expr, int* pos);

// ヘルパー関数：数を解析する
double parseNumber(const char* expr, int* pos) {
    double result = 0.0;
    while (isdigit(expr[*pos]) || expr[*pos] == '.') {
        if (expr[*pos] == '.') {
            (*pos)++;
            double frac = 1.0;
            while (isdigit(expr[*pos])) {
                frac /= 10.0;
                result += (expr[*pos] - '0') * frac;
                (*pos)++;
            }
        } else {
            result = result * 10.0 + (expr[*pos] - '0');
            (*pos)++;
        }
    }
    return result;
}

// ヘルパー関数：括弧を解析する
double parseFactor(const char* expr, int* pos) {
    double result;
    if (expr[*pos] == '(') {
        (*pos)++;
        result = evaluate(expr, pos);
        (*pos)++;
    } else {
        result = parseNumber(expr, pos);
    }
    return result;
}

// ヘルパー関数：乗算と除算を解析する
double parseTerm(const char* expr, int* pos) {
    double result = parseFactor(expr, pos);
    while (expr[*pos] == '*' || expr[*pos] == '/') {
        char op = expr[*pos];
        (*pos)++;
        double nextFactor = parseFactor(expr, pos);
        if (op == '*') {
            result *= nextFactor;
        } else {
            result /= nextFactor;
        }
    }
    return result;
}

// メインの評価関数
double evaluate(const char* expr, int* pos) {
    double result = parseTerm(expr, pos);
    while (expr[*pos] == '+' || expr[*pos] == '-') {
        char op = expr[*pos];
        (*pos)++;
        double nextTerm = parseTerm(expr, pos);
        if (op == '+') {
            result += nextTerm;
        } else {
            result -= nextTerm;
        }
    }
    return result;
}

// 主な計算関数
double calculate(const char* expression) {
    int pos = 0;
    return evaluate(expression, &pos);
}

// ヘルパー関数：方程式を解析して解く
void solveEquation(const char* equation) {
    // 方程式を左辺と右辺に分割する
    const char* equalSign = strchr(equation, '=');
    if (!equalSign) {
        printf("Invalid equation: %s\n", equation);
        return;
    }
    
    char leftExpr[256];
    char rightExpr[256];
    
    strncpy(leftExpr, equation, equalSign - equation);
    leftExpr[equalSign - equation] = '\0';
    
    strcpy(rightExpr, equalSign + 1);
    
    // 左辺と右辺を評価する
    double leftValue = calculate(leftExpr);
    double rightValue = calculate(rightExpr);
    
    // 単純な方程式の場合、解を表示する
    if (leftValue == rightValue) {
        printf("The equation %s is always true.\n", equation);
    } else {
        printf("The equation %s is false. Left side: %f, Right side: %f\n", equation, leftValue, rightValue);
    }
}
