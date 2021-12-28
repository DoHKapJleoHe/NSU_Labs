#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LENGTH 1004

void PushStack(stack* operator_stack, int symbol) // эта функция пихает операторы в стэк операторо
{
    operator_stack->mas[operator_stack->size] = symbol;
    operator_stack->size++;
}

int PopStack(stack* operator_stack) // эта функция вытаскивает оператор из стека операторов и уменьшает размер стэка
{
    if (operator_stack->size == 0)
    {
        printf("syntax error!");
        exit(0);
    }
    operator_stack->size--;
    return operator_stack->mas[operator_stack->size];
}

int PeekStack(stack* operator_stack) // эта функция просто берёт оператор, но не уменьшает размер стэка
{
    if (operator_stack->size <= 0) {
        printf("syntax error");
        exit(0);
    }
    return operator_stack->mas[operator_stack->size - 1];
}

int priority(char c)
{
    if (c == '(' || c == ')')
        return 0;
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    return -1;
}
int isOperator(char symbol)
{
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '(' || symbol == ')';
}

int proverka_simvolov(char symbol)
{
    return isOperator(symbol) || isdigit(symbol) || symbol == '\n';
}

void postfix(char* stroka, int size, char* postf)
{
    int postfix_size = 0;
    stack operator_stack;
    operator_stack.size = 0;
    for (int i = 0; i < size; ++i) // идём с начала выражения и проверяем число это или оператор
    {
        if (isdigit(stroka[i])) // если попалось число
        {
            while (!isOperator(stroka[i])) // пока идёт число, записываем его в массив postf
            {
                postf[postfix_size] = stroka[i];
                postfix_size++;
                i++;
                if (i == size) break; // если получилось, что длина числа равна длине строки, то заканчиваем
            }
            postf[postfix_size] = ' ';
            postfix_size++;
            i--;
        }
        if (isOperator(stroka[i])) // если попался оператор
        {
            if (stroka[i] == '(') // если попавшийся символ это открывающая скобка
            {
                PushStack(&operator_stack, (int)stroka[i]); // кидаем скобку в стек операторов
            }
            else if (stroka[i] == ')') // если попавшийся символ закрывающая скобка
            {
                if (i == 0 || stroka[i - 1] == '(') // тут мы проверяем, на первом месте не стоит закрывающая скобка или или предыдущий символ не является открывающей скобкой
                {
                    printf("syntax error!");
                    exit(0);
                }
                char s = (int)PopStack(&operator_stack); // вытащили из стека оператор
                while (s != '(')  // теперь из стека операторов выгружаем все операторы до открывающей скобки в постфиксную запись
                {
                    postf[postfix_size] = s;
                    postf[postfix_size + 1] = ' ';
                    postfix_size += 2;
                    s = (int)PopStack(&operator_stack);
                }
            }
            else
            {
                if (operator_stack.size > 0 && priority(stroka[i]) <= priority((char)PeekStack(&operator_stack)))
                {
                    postf[postfix_size] = (char)PopStack(&operator_stack);
                    postf[postfix_size + 1] = ' ';
                    postfix_size += 2;
                }
                PushStack(&operator_stack, (int)stroka[i]); // тут в стэк операторов грузятся осставшиеся операторы
            }
        }
    }
    while (operator_stack.size > 0) 
    {
        postf[postfix_size] = (char)PopStack(&operator_stack);
        postf[postfix_size + 1] = ' ';
        postfix_size += 2;
    }
    postf[postfix_size] = '\0';
}

int calculate(char* postf)
{
    int resultat = 0;
    stack resultat_stack;
    resultat_stack.size = 0;
    /*size_t*/int postf_size = strlen(postf);
    for (int i = 0; i < postf_size; ++i)
    {
        if (isdigit(postf[i]))
        {
            int x = 0;
            while (!isOperator(postf[i]) && postf[i] != ' ') {
                x *= 10;
                x += (int)(postf[i] - '0');
                i++;
                if (i == postf_size) {
                    break;
                }
            }
            PushStack(&resultat_stack, x);
            i--;
        }
        else if (isOperator(postf[i])) {
            int a = PopStack(&resultat_stack);
            int b = PopStack(&resultat_stack);
            if (postf[i] == '+') {
                resultat = b + a;
            }
            if (postf[i] == '-') {
                resultat = b - a;
            }
            if (postf[i] == '*') {
                resultat = b * a;
            }
            if (postf[i] == '/') {
                if (a == 0) {
                    printf("division by zero");
                    exit(0);
                }
                resultat = b / a;
            }
            PushStack(&resultat_stack, resultat);
        }
    }
    return PeekStack(&resultat_stack);
}

int main(void)
{
    char stroka[MAX_LENGTH];  // тут лежит выражение , которое мы должны посчитать
    while (!fgets(stroka, MAX_LENGTH, stdin))
    {
        printf("syntax error!");      // ввод строки которую нужно будет посчитать
        exit(0);
    }
     
    size_t ammount = strlen(stroka); // длина это строки которую мы считаем
    unsigned int i = 0;

    while (i < (ammount - 1))// тут как-то странно, вроде не надо отнимать, т.к. счютчик идёт с нуля
    {
        if (!proverka_simvolov(stroka[i]))
        { 
            printf("syntax error");   // проверяем символы, чтобы они не были какими-нибудь левыми
            return 0;
        }
        i++;
    }
    stroka[i] = '\0'; 
    char postf[MAX_LENGTH * 5]; // в этот массив будет записана постфиксная запись
    postfix(stroka, i, postf);
    printf("%d", calculate(postf));
    return 0;
}
