#ifndef CALCULATOR2_0_H_INCLUDED
#define CALCULATOR2_0_H_INCLUDED

#define OPERAND_LENGTH_MAX 50

#include "Graphics.h"
#include <math.h>
#include "LinkedList.h"
#include "Posfix.h"
#include "History.h"
#include "Mode.h"

int CheckButtonClick(Buttons button, int x, int y){
    return (x > button.x) && (x < (button.size_x + button.x)) && (y > button.y) && (y < (button.size_y + button.y));
}
//kiem tra tat ca button co button click ko. Neu dung return button.name
Buttons *FindButtonClick(Buttons **listButton, int x, int y){
    for (int i = 0 ; i < 5 ; i++)
        for (int j = 0 ; j < 7 ; j++)
            if (CheckButtonClick(listButton[i][j], x, y)){
                return &listButton[i][j];
                    }
    return NULL;
}

void DrawScreen(char *expression, double result){
    // vẽ nền
    setbkcolor(COLER_LIGHTGRAY);
    setfillstyle(SOLID_FILL, COLER_LIGHTGRAY);
    bar(SCREEN_X, SCREEN_Y, SIZE_SCREEN_X + SCREEN_X, SIZE_SCREEN_Y + SCREEN_Y);
    //set text
    settextstyle(1, 0, 2);
    settextjustify(RIGHT_TEXT, BOTTOM_TEXT);
    //vẽ biểu thức
    moveto(SIZE_SCREEN_X + SCREEN_X - 5, SIZE_SCREEN_Y / 2 - 12 + SCREEN_Y);
    if (strlen(expression) == 0){
        outtext("0");
    } else
    if (strlen(expression) > 14){
        outtext(expression + (strlen(expression) - 14));
    } else outtext(expression);
    //printExpression(expression);
    // vẽ kết quả
    moveto(SIZE_SCREEN_X + SCREEN_X - 5, SIZE_SCREEN_Y + SCREEN_Y - 7);
    char s[20];
    sprintf(s, "%f", result);
    FixResult(s);
    if (s[0] == '\0') outtext("0");
    else outtext(s);
}


int CheckExpression(char *operand, int *lengthOperand, char *key, double ans, double *M){
    if (idKeyBoard(key) < 0) return 0;
    if (idKeyBoard(key) == 27){
        return 7;
    }
    //nếu ấn =
    if (idKeyBoard(key) == 16) {
        return 3;
    }
    if (idKeyBoard(key) < 10){
        operand[(*lengthOperand)++] = key[0];
        operand[*lengthOperand] = '\0';
        return 1;
    }
    if (idKeyBoard(key) <= 15){
        if (*lengthOperand == 0){
            char s[20];
            sprintf(s, "%f", ans);
            FixResult(s);
            for (int i = 0 ; i < strlen(s) ; i++){
            operand[(*lengthOperand)++] = s[i];
            }
        }
        if (CheckOperator(operand[(*lengthOperand) - 1])){
            operand[(*lengthOperand) - 1] = key[0];
            return 1;
        } else {
            operand[(*lengthOperand)++] = key[0];
            operand[*lengthOperand] = '\0';
            return 1;
        }
    }
    if (idKeyBoard(key) == 17){
        if (ans == 0) return 0;
        char s[20];
        sprintf(s, "%f", ans);
        FixResult(s);
        for (int i = 0 ; i < strlen(s) ; i++){
            operand[(*lengthOperand)++] = s[i];
        }
        operand[*lengthOperand] = '\0';
        return 1;
    }
    //CE
    if (idKeyBoard(key) == 18){
        operand[0] = '\0';
        *lengthOperand = 0;
        return 2;
    }
    //C
    if (idKeyBoard(key) == 19){
        operand[0] = '\0';
        *lengthOperand = 0;
        return 1;
    }
    //Del
    if (idKeyBoard(key) == 20){
        if ((*lengthOperand) == 0) return 0;
        (*lengthOperand)--;
        operand[*lengthOperand] = '\0';
        return 1;
    }
    //Nếu ấn M
    if (idKeyBoard(key)== 21){
        char s[20];
        sprintf(s, "%f", *M);
        FixResult(s);
        for (int i = 0 ; i < strlen(s) ; i++){
            operand[(*lengthOperand)++] = s[i];
        }
        operand[*lengthOperand] = '\0';
        return 1;
    }
    //Nếu ấn M+
    if (idKeyBoard(key) == 22){
        *M += ans;
        return 0;
    }
    if (idKeyBoard(key) == 23){
        *M -= ans;
        return 0;
    }

    if (idKeyBoard(key) == 24){
        return 4;
    }

    if (idKeyBoard(key) == 25){
        return 5;
    }
    if (idKeyBoard(key) == 26){
        return 6;
    }
    if (idKeyBoard(key) == 28){
        return 8;
    }
    if (idKeyBoard(key) == 29){
        return 9;
    }

    //mode
    if (idKeyBoard(key) == 101){
        return 101;
    }
    //History
    if (idKeyBoard(key) == 102){
        return 102;
    }
    return 0;
}

LinkedList **LinkedResult(int n){
    LinkedList **pLinkedList = (LinkedList**)malloc(n * sizeof(LinkedList*));

    for (int i = 0; i < 10; ++i) {
        pLinkedList[i] = InitLinkedList();
    }

    return pLinkedList;
}

void ActionButtonMove(Buttons **lastButton, Buttons **listButton){
    int x, y;
    getmouseclick(WM_MOUSEMOVE, x, y);
    if (*lastButton != NULL){
        DrawButton(**lastButton, COLER_LIGHTGREEN);
        if (idKeyBoard((**lastButton).name) < 100) DrawTextButton(**lastButton, COLER_RED, COLER_LIGHTGREEN);
    }
    Buttons *b;
    b = FindButtonClick(listButton, x, y);
    if (b != NULL){
        *lastButton = b;
        DrawButton(**lastButton, COLER_LIGHTCYAN);
        if (idKeyBoard((**lastButton).name) < 100) DrawTextButton(**lastButton, COLER_RED, COLER_LIGHTCYAN);
    }
}

int ActionButtonClick(LinkedList **linkedList, int *numberHistory, Buttons **listButton, char *operand, int *lengthOperand, Buttons *button,
                       double *result, double *M, double *ans){
    int x, y;
    char *key;
    getmouseclick(WM_LBUTTONDOWN, x, y);
    // key la id cua button
    button = FindButtonClick(listButton, x, y);
    if (button == NULL) key = "None";
    else {
        key = button->name;
        ClickButton(*button);
        DrawButton(*button, COLER_LIGHTCYAN);
        if (idKeyBoard((*button).name) < 100) DrawTextButton(*button, COLER_RED, COLER_LIGHTCYAN);
    }
    int flag = CheckExpression(operand, lengthOperand, key, *ans, M);
    if (flag >= 3 && flag <=100 && lengthOperand > 0){
        if (idKeyBoard(operand + *lengthOperand) > 9){
            lengthOperand--;
            operand[*lengthOperand] = '\0';
        }

        if (*numberHistory > 10) {
            LinkedList *link = linkedList[0];
            FreeLinkedList(link);
            for (int i = 0 ; i < 9 ; i++)
                linkedList[i] = linkedList[i + 1];
        } else (*numberHistory)++;
        linkedList[*numberHistory] = Inffix(operand);
        switch (flag){
            case 3: *result = Inffix_Posffix(linkedList[*numberHistory]);
                AddToHeadLL(linkedList[*numberHistory], "=");
                break;
            case 4: *result = sin(Inffix_Posffix(linkedList[*numberHistory]));
                AddToHeadLL(linkedList[*numberHistory], "Sin");
                break;
            case 5: *result = cos(Inffix_Posffix(linkedList[*numberHistory]));
                AddToHeadLL(linkedList[*numberHistory], "Cos");
                break;
            case 6: *result = tan(Inffix_Posffix(linkedList[*numberHistory]));
                AddToHeadLL(linkedList[*numberHistory], "Tan");
                break;
            case 7: *result = 1 / Inffix_Posffix(linkedList[*numberHistory]);
                AddToHeadLL(linkedList[*numberHistory], "1/n");
                break;
            case 8: *result = log(Inffix_Posffix(linkedList[*numberHistory]));
                AddToHeadLL(linkedList[*numberHistory], "log");
                break;
            case 9: *result = pow(Inffix_Posffix(linkedList[*numberHistory]), 2);
                AddToHeadLL(linkedList[*numberHistory], "^2");
        }
        *ans = *result;
        operand[0] = '\0';
        *lengthOperand = 0;
    }
    if (flag == 2) *result = 0;
    if (flag > 0) DrawScreen(operand, *result);
    if (flag == 101) {
        return DrawMode();
    }
    if (flag == 102) DrawHistory(linkedList, *numberHistory);
    return EXIT;
}



int StandardCalculator(){
    SIZE_SCREEN_X = 290;
    SIZE_X = 300;
    InitGraphics();

    Buttons **listButton;
    listButton = DrawStandard();

    // tao so, ket qua, dau
    double result = 0, M = 0, ans = 0;
    char *operand = (char *)malloc((OPERAND_LENGTH_MAX + 1)* sizeof(char));
    int lengthOperand = 0;
    operand[lengthOperand] = '\0';
    // tin man hinh so, dau, ket qua
    DrawScreen(operand, result);

    LinkedList **linkedList = LinkedResult(10);
    int numberHistory = -1;
    Buttons *button = NULL;

    int flagMode = 1;

    while(1){
        delay(0.0001);
        if (ismouseclick(WM_MOUSEMOVE )){
            ActionButtonMove(&button, listButton);
        }

        if (ismouseclick(WM_LBUTTONDOWN)){
            flagMode = ActionButtonClick(linkedList, &numberHistory, listButton, operand, &lengthOperand, button, &result, &M, &ans);
            if (flagMode != EXIT && flagMode != STANDARD) break;
        }
    }
    return flagMode;
}
#endif // CALCULATOR2_0_H_INCLUDED
