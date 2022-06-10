/*
clang calculator.c -o calculator -lcs50
*/

#include<cs50.h>
#include<stdio.h>

double calculate(double n1, double n2, char op);

int main(void) 
{
    double num1 = get_double("Enter a number: ");
    double num2 = get_double("Enter a number: ");
    char operator = get_char("Enter an operator: ");

    printf("%f\n", calculate(num1,num2,operator));
}

double calculate(double n1, double n2, char op) {
    switch (op)
    {
    case '+':
        return n1 + n2;
    case '-':
        return n1-n2;
    case '*':
    case 'x':
        return n1 * n2;
    case '/':
        return n1 / n2;
    default:
        printf("Invalid Operator: program returns ");
        return 0;
    }
}