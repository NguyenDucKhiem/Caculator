#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include "Button.h"


#define X 0
#define Y 0
int SIZE_X = 310;
int SIZE_Y = 500;

#define EXIT 0
#define STANDARD 1
#define SCIENTIFIC 2

#define SCREEN_X 5
#define SCREEN_Y 45
int SIZE_SCREEN_X = 300;
#define SIZE_SCREEN_Y 110

#define BUTTON_X 15
#define BUTTON_Y 190

void ClearScreen(){
    setfillstyle(SOLID_FILL, COLER_LIGHTGRAY);
    bar(SCREEN_X, SCREEN_Y, SIZE_SCREEN_X + SCREEN_X, SIZE_SCREEN_Y + SCREEN_Y);
}

void InitGraphics(){
    int mh = VGA, mode = VGAHI;
    //initgraph(&mh,&mode,"C:\\TC\\BGI");
    initwindow(SIZE_X + 8, SIZE_Y + 10);
    //setbkcolor(15);
    //setcolor(15);
//    settextstyle(0, 0, 2);
//    settextjustify(CENTER_TEXT, CENTER_TEXT);
//vẽ nền máy tính
    setfillstyle(SOLID_FILL, COLER_WHITE);
//    rectangle(X, Y, SIZE_X + X, SIZE_Y + Y);
    bar(X, Y, SIZE_X + X, SIZE_Y + Y);
    // vẽ nền màn hình
    setfillstyle(SOLID_FILL, COLER_LIGHTGRAY);
    bar(SCREEN_X, SCREEN_Y, SIZE_SCREEN_X + SCREEN_X, SIZE_SCREEN_Y + SCREEN_Y);
//    rectangle(SCREEN_X, SCREEN_Y, SIZE_SCREEN_X + SCREEN_X, SIZE_SCREEN_Y + SCREEN_Y);
}

Buttons **ListButtons(int numberx, int numbery){
    Buttons **ListButton = (Buttons**)malloc(numberx * sizeof(Buttons*));
    for (int x = 0 ; x < numberx ; x++){
        Buttons *List = (Buttons*)malloc(numbery * sizeof(Buttons));
        for (int y = 0 ; y < numbery ; y++){
            List[y] = InitButton(BUTTON_X + 72 * x, BUTTON_Y + 50 * y);
            }
        ListButton[x] = List;
    }
    return ListButton;
}

void DrawListBottons(Buttons **listButton, int numberx, int numbery){
    for (int x = 0 ; x < numberx ; x++)
        for (int y = 0 ; y < numbery ; y++)
            {
                DrawButton(listButton[x][y], COLER_LIGHTGREEN);
                if (idKeyBoard(listButton[x][y].name) < 100)
                    DrawTextButton(listButton[x][y], COLER_RED, COLER_LIGHTGREEN);
            }
}

Buttons **SetKeyBoard(int mode){
    Buttons **listButton = ListButtons(5, 7);
    listButton[0][0].name = "M";
    listButton[0][1].name = "CE";
    listButton[0][2].name = "7";
    listButton[0][3].name = "4";
    listButton[0][4].name = "1";
    listButton[0][5].name = "0";
    listButton[1][0].name = "M+";
    listButton[1][1].name = "C";
    listButton[1][2].name = "8";
    listButton[1][3].name = "5";
    listButton[1][4].name = "2";
    listButton[1][5].name = ".";
    listButton[2][0].name = "M-";
    listButton[2][1].name = "Del";
    listButton[2][2].name = "9";
    listButton[2][3].name = "6";
    listButton[2][4].name = "3";
    listButton[2][5].name = "Ans";
    listButton[3][0].name = "^";
    listButton[3][1].name = "/";
    listButton[3][2].name = "*";
    listButton[3][3].name = "-";
    listButton[3][4].name = "+";
    listButton[3][5].name = "=";
    listButton[0][6].name = "Mode";
    listButton[1][6].name = "History";
    listButton[2][6].name = "None";
    listButton[3][6].name = "None";
    if (mode == 2){
        listButton[4][0].name = "Sin";
        listButton[4][1].name = "Cos";
        listButton[4][2].name = "Tan";
        listButton[4][3].name = "1/n";
        listButton[4][4].name = "log";
        listButton[4][5].name = "^2";
        listButton[4][6].name = "None";
    } else {
        for (int i = 0 ; i < 7 ; i++)
            listButton[4][i].name = "None";
    }
    return listButton;
}

void ButtonHistory(Buttons *button){
    button->x = SIZE_X - 35;
    button->y = 5;
    button->size_x = 30;
    button->size_y = 30;
    DrawButton(*button, COLER_LIGHTGREEN);
}

void ButtonMode(Buttons *button){
    button->x = 0;
    button->y = 0;
    button->size_x = 40;
    button->size_y = 40;
    DrawButton(*button, COLER_LIGHTGREEN);
}

Buttons **DrawStandard(){
    Buttons **listButton = SetKeyBoard(STANDARD);
    DrawListBottons(listButton, 4, 6);

    setbkcolor(COLER_WHITE);
    setcolor(COLER_BLACK);
    settextstyle(0, 0, 3);
    settextjustify(LEFT_TEXT, TOP_TEXT);
    moveto(60, 10);
    outtext("STANDARD");
    ButtonMode(&listButton[0][6]);
    ButtonHistory(&listButton[1][6]);
    return listButton;
}

Buttons **DrawScientific(){
    Buttons **listButton = SetKeyBoard(SCIENTIFIC);
    DrawListBottons(listButton, 5, 6);

    setbkcolor(COLER_WHITE);
    setcolor(COLER_BLACK);
    settextstyle(0, 0, 3);
    settextjustify(LEFT_TEXT, TOP_TEXT);
    moveto(60, 10);
    outtext("Scientific");
    ButtonMode(&listButton[0][6]);
    ButtonHistory(&listButton[1][6]);
    return listButton;
}


#endif // GRAPHICS_H_INCLUDED
