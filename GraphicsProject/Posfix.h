#ifndef POSFIX_H_INCLUDED
#define POSFIX_H_INCLUDED

#include <math.h>
#include <string.h>
#include "LinkedList.h"

//chan hóa kết quả
void FixResult(char *result){
    for (int i = strlen(result) - 1 ; i >= 0 ; i--){
        if (result[i] == '0'){
            result[i] = '\0';
        } else if (result[i] == '.'){
            result[i] = '\0';
            break;
        } else break;
    }
}

//Chuyển đối string -> double
double ParseDouble(char *operand){
    double number = 0;
    int length = strlen(operand);
    int pointFloat = 0;
    int i = 0;
    int flag = 0;
    if (operand[i] == '-'){
        flag = 1 ;
        i++;
    }
    for ( ; i < length; i++) {
        int x = operand[i] - '0';
//        Nếu dấu . thì đánh dấu
        if (operand[i] == '.') pointFloat = 1;
        else if (pointFloat){
//            x * 10 ^ - pointFloat
                number += x * pow(10, -pointFloat);
                pointFloat++;
            } else number = number * 10 + x;
    }
    if (flag) return -number;
    else return number;
}

double Result(char *operand, char *operand2, char operator1){
    switch (operator1){
        case '+':
            return ParseDouble(operand) + ParseDouble(operand2);
        case '-':
            return ParseDouble(operand) - ParseDouble(operand2);
        case '*':
            return ParseDouble(operand) * ParseDouble(operand2);
        case '/':
            return ParseDouble(operand) / ParseDouble(operand2);
        case '^':
            return pow(ParseDouble(operand), ParseDouble(operand2));
        default:
            return 0;
    }
}

int CheckOperator(char ch){
    if (ch == '+' || ch == '-') return 1;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '^') return 3;
    return 0;
}


void Stack(LinkedList *suffix, LinkedList *stacks, char *item){
    if (!CheckOperator(item[0])) AddToBottomLL(suffix, item);
        else {
            if (stacks->Head == NULL) AddToBottomLL(stacks, item);
            else {
                    if (CheckOperator(stacks->Bottom->item[0]) < CheckOperator(item[0])) AddToBottomLL(stacks, item);
                        else {
                            /*AddToBottomLinkedList(suffix, DeleteToBottomLL(stacks));
                            if (stacks->Head != NULL) Stack(suffix, stacks, item);
                            else AddToBottomLL(stacks, item);*/
                                while (stacks->Bottom != NULL && CheckOperator(stacks->Bottom->item[0]) >= CheckOperator(item[0]))
                            {
                                AddToBottomLL(suffix, DeleteToBottomLL(stacks));
                            }
                        AddToBottomLL(stacks, item);
                        }
                }
            }
}

double CalculatorSuffix(LinkedList *suffix){
    if (suffix->Head->next == NULL) return ParseDouble(suffix->Bottom->item);
    double result = 0;
    List *node = suffix->Head;
    LinkedList *stacks = InitLinkedList();
    while (node != NULL){
        if (!CheckOperator(node->item[0])) {
            AddToBottomLL(stacks, node->item);
                printf("\nAdd:");
                printLinkedList(stacks);
        }
        else {
            char *operand = DeleteToBottomLL(stacks);
            printf("\ndelete:");
            printLinkedList(stacks);
            char *operand2 = DeleteToBottomLL(stacks);
            printf("\ndelete:");
            printLinkedList(stacks);
            if (operand == NULL || operand2 == NULL) return result;
            result = Result(operand2, operand, node->item[0]);
            char *s = (char *) malloc (30 * sizeof(char));
            sprintf(s, "%f", result);
            AddToBottomLL(stacks, s);
            printf("\nAdd:");
            printLinkedList(stacks);
        }
        node = node->next;
    }
    free(stacks);
    return result;
}

//Chuyển trung tố sang hậu tố
LinkedList *Suffix(LinkedList *link){
    LinkedList *suffix = InitLinkedList();
    LinkedList *stacks = InitLinkedList();
    List *node = link->Head;
    while (node != NULL){
        Stack(suffix, stacks, node->item);
        node = node->next;
    }
    while (stacks->Head != NULL){
        AddToBottomLL(suffix, DeleteToBottomLL(stacks));
    }
    free(stacks);
    return suffix;
}
//Kiem tra dau
int checkOperator(char s){
    if (s == '/' || s == '*' || s == '-' || s == '+' || s == '^') return 1;
    return 0;
}

// Chuyen chuoi -> Inffix
LinkedList *Inffix(char *inffix){
    LinkedList *In = InitLinkedList();
    int length = strlen(inffix);
    int i = 0, j;
    while (i <= length){
        j = 1;
        while (!CheckOperator(inffix[i + j]) && (i + j < length)) j++;
        //Copy so
        char *s = (char *)malloc((j + 1) * sizeof(char));
        memcpy(s, inffix + i, j);
        s[j] = '\0';
        AddToBottomLL(In, s);
        //copy dau
        if (i + j < length){
            char *o = (char *)malloc(2 * sizeof(char));
            memcpy(o, inffix + i + j, 1);
            o[1] = '\0';
            AddToBottomLL(In, o);
        }
        i = i + j + 1;
    }
    return In;
}

double Inffix_Posffix(LinkedList *linkedList){
    printf("\nInffix: ");
    printLinkedList(linkedList);
    LinkedList *suffix = Suffix(linkedList);
    printf("\nPosffix: ");
    printLinkedList(suffix);
    printf("\n----------------------------------------------------------\n");
    return  CalculatorSuffix(suffix);
}

#endif // POSFIX_H_INCLUDED
