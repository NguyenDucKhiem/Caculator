#ifndef CALCULATOR_H_INCLUDED
#define CALCULATOR_H_INCLUDED

#include "Graphics.h"
#include <math.h>
//#include <graphics.h>

#define OPERAND_LENGTH_MAX 10

//kiem tra vi tri click co nam trong button hay ko
int CheckButtonClick(Buttons button, int x, int y){
    return (x > button.x) && (x < (button.size_x + button.x)) && (y > button.y) && (y < (button.size_y + button.y));
}
//kiem tra tat ca button co button click ko. Neu dung return button.name
char *FindButtonClick(Buttons **listButton, int x, int y){
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 6 ; j++)
            if (CheckButtonClick(listButton[i][j], x, y)){
                        return ClickButton(listButton[i][j]);
                    }
    return NULL;
}
void DrawScreen(char *operand, double result, char operator1){
    // vẽ nền cửa sổ
    setbkcolor(COLER_LIGHTGRAY);
    setfillstyle(SOLID_FILL, COLER_LIGHTGRAY);
    bar(SCREEN_X, SCREEN_Y, SIZE_SCREEN_X + SCREEN_X, SIZE_SCREEN_Y + SCREEN_Y);
    // vẽ số nhập vào
    settextstyle(1, 0, 2);
    settextjustify(RIGHT_TEXT, BOTTOM_TEXT);
    moveto(SIZE_SCREEN_X + SCREEN_X - 5, SIZE_SCREEN_Y / 2 - 12 + SCREEN_Y);
    if (operand[0] == '\0') outtext("0");
        else outtext(operand);
    // vẽ kết quả
    moveto(SIZE_SCREEN_X + SCREEN_X - 5, SIZE_SCREEN_Y + SCREEN_Y - 7);
    char s[20];
    sprintf(s, "%f", result);
    outtext(s);
    // vẽ dấu
    settextjustify(LEFT_TEXT, CENTER_TEXT);
    settextstyle(1, 0, 1);
    moveto(SCREEN_X + 3, SCREEN_Y + SIZE_SCREEN_Y / 2 + 6);
    sprintf(s, "%c", operator1);
    outtext(s);
}
//Chuyển đối string -> double
double ParseDouble(char *operand){
    double number = 0;
    int length = strlen(operand);
    int pointFloat = 0;
    for (int i = 0; i < length; ++i) {
        int x = operand[i] - '0';
//        Nếu dấu . thì đánh dấu
        if (operand[i] == '.') pointFloat = 1;
        else if (pointFloat){
//            x * 10 ^ - pointFloat
                number += x * pow(10, -pointFloat);
                pointFloat++;
            } else number = number * 10 + x;
    }
    return number;
}
// tinh ket qua
double Result(char *operand, double result, char operator1){
    switch (operator1){
        case '+':
            return result + ParseDouble(operand);
        case '-':
            return result - ParseDouble(operand);
        case 'X':
            return result * ParseDouble(operand);
        case '/':
            return result / ParseDouble(operand);
        case '^':
            return pow(result, ParseDouble(operand));
        default:
            return 0;
    }
}
char Operator1(int id){
    switch(id){
        case 11: return '+';
        case 12: return '-';
        case 13: return 'X';
        case 14: return '/';
        case 15: return '^';
        default: return ' ';
    }
}
int CheckExpression(char *operand, int *lengthOperand, double *result, char *operator1, double *M, int id){
    if (id <= 9 && *lengthOperand < OPERAND_LENGTH_MAX){
        operand[(*lengthOperand)++] = '0' + id;
        operand[*lengthOperand] = '\0';
        return 1;
    }
    // Nếu ấn dâu =
    if (id == 16){
        if (operand[0] == '\0') return 0;
        *result = Result(operand, *result, *operator1);
        operand[0] = '\0';
        *lengthOperand = 0;
        return 1;
    }
    // nếu ấn + - x / ^
    if (id >= 11 && id <= 15 && *lengthOperand < OPERAND_LENGTH_MAX){
        *operator1 = Operator1(id);
        return 1;
    }
    // nếu ấn .
    if (id == 10){
        for (int i = 0 ; i < *lengthOperand ; i++)
            if (operand[i] == '.') return 0;
        operand[(*lengthOperand)++] = '.';
        operand[*lengthOperand] = '\0';
        return 1;
    }
    //Nếu ấn Ans
    if (id == 17){
        sprintf(operand, "%f", *result);
        *lengthOperand = strlen(operand);
        return 1;
    }
    //Nếu ấn CE
    if (id == 18){
        operand[0] = '\0';
        *lengthOperand = 0;
        *result = 0;
        return 1;
    }
    //nếu ấn C
    if (id == 19){
        operand[0] = '\0';
        *lengthOperand = 0;
        return 1;
    }
    //Nếu ấn Del
    if (id == 20 && *lengthOperand > 0){
        (*lengthOperand)--;
        operand[*lengthOperand] = '\0';
        return 1;
    }
    //Nếu ấn M
    if (id == 21){
        sprintf(operand, "%f", *M);
        *lengthOperand = strlen(operand);
        return 1;
    }
    //Nếu ấn M+
    if (id == 22){
        *M += *result;
        return 0;
    }
    if (id == 23){
        *M -= *result;
        return 0;
    }
    return 0;
}
// xử lí màn hình
void Screen(Buttons **listButton){
    // tao so, ket qua, dau
    double result = 0, M = 0;;
    char *operand = (char *)malloc((OPERAND_LENGTH_MAX + 1)* sizeof(char));
    char operator1 = '+';
    int lengthOperand = 0;

    operand[lengthOperand] = '\0';
    // tin man hinh so, dau, ket qua
    DrawScreen(operand, result, operator1);
    while(1){readimagefile("button_1.jpg", 10, 10, 60, 40);
        printf("%d", graphresult());
        delay(0.0001);
        if (ismouseclick(WM_LBUTTONDOWN)){
            int x, y;
            int key;
            getmouseclick(WM_LBUTTONDOWN, x, y);
            // key la id cua button
            key = idKeyBoard(FindButtonClick(listButton, x, y));
            printf("%d\n", key);
            if (key > 0){
                if (CheckExpression(operand, &lengthOperand, &result, &operator1, &M, key)) DrawScreen(operand, result, operator1);
            }
        }
    }
    free(operand);
}

#endif // CALCULATOR_H_INCLUDED
