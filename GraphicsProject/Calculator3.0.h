#ifndef CALCULATOR3_0_H_INCLUDED
#define CALCULATOR3_0_H_INCLUDED

#include "Calculator2.0.h"

int ScientificCalculator(){
    SIZE_SCREEN_X = 370;
    SIZE_X = 380;
    InitGraphics();


    Buttons **listButton;
    listButton = DrawScientific();

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
            if (flagMode != EXIT && flagMode != SCIENTIFIC) break;
        }
    }
    return flagMode;
}

void Calculator(){
    int flag = 1;
    while (flag){
        switch (flag){
            case STANDARD:{
                flag = StandardCalculator();
                closegraph();
            }
            case SCIENTIFIC:{
                flag = ScientificCalculator();
                closegraph();
            }
        }
    }
}

#endif // CALCULATOR3_0_H_INCLUDED
