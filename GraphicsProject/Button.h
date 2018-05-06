#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include <graphics.h>
#include <conio.h>
#include <stdlib.h>

#define SIZE_BUTTON_X 60
#define SIZE_BUTTON_Y 40

#define COLER_BLACK 0
#define COLER_BLUE 1
#define COLER_GREEN 2
#define COLER_CYAN 3
#define COLER_RED 4
#define COLER_MAGENTA 5
#define COLER_BROWN 6
#define COLER_LIGHTGRAY 7
#define COLER_DARKGRAY 8
#define COLER_LIGHTBLUE 9
#define COLER_LIGHTGREEN 10
#define COLER_LIGHTCYAN 11
#define COLER_LIGHTRED 12
#define COLER_LIGHTMAGENTA 13
#define COLER_YELLOW 14
#define COLER_WHITE 15

//  Tạo ra đối tượng button có thông số tọa độ, chiều dài, rộng, độ sâu
struct Buttons{
    int x, y, size_x, size_y;
    char *name;
};
typedef struct Buttons Buttons;

Buttons InitButton(int x, int y){
    Buttons button;
    button.x = x;
    button.y = y;
    button.size_x = SIZE_BUTTON_X;
    button.size_y = SIZE_BUTTON_Y;
    return button;
}


int idKeyBoard(char *button){
    if (button == NULL) return -1;
    if (button[0] >= '0' && button[0] <= '9' && button[1] == '\0') return button[0] - '0';
    if (!strcmp(button, ".")) return 10;
    if (!strcmp(button, "+")) return 11;
    if (!strcmp(button, "-")) return 12;
    if (!strcmp(button, "*")) return 13;
    if (!strcmp(button, "/")) return 14;
    if (!strcmp(button, "^")) return 15;
    if (button[0] == '=') return 16;
    if (!strcmp(button, "Ans")) return 17;
    if (!strcmp(button, "CE")) return 18;
    if (!strcmp(button, "C")) return 19;
    if (!strcmp(button, "Del")) return 20;
    if (!strcmp(button, "M")) return 21;
    if (!strcmp(button, "M+")) return 22;
    if (!strcmp(button, "M-")) return 23;
    if (!strcmp(button, "Sin")) return 24;
    if (!strcmp(button, "Cos")) return 25;
    if (!strcmp(button, "Tan")) return 26;
    if (!strcmp(button, "1/n")) return 27;
    if (!strcmp(button, "log")) return 28;
    if (!strcmp(button, "^2")) return 29;
    if (!strcmp(button, "History")) return 102;
    if (!strcmp(button, "Mode")) return 101;
    if (!strcmp(button, "History")) return 102;
    return -1;
}



void DrawButtonHistory(Buttons button){
    line(button.x + 5, button.y + 10, button.x + button.size_x / 2, button.y + button.size_y / 2 +5);
    line(button.x + button.size_x - 6, button.y + 10, button.x + button.size_x / 2 - 1, button.y + button.size_y / 2 + 5);

    line(button.x + 6, button.y + 10, button.x + button.size_x / 2 + 1, button.y + button.size_y / 2 + 5);
    line(button.x + button.size_x - 5, button.y + 10, button.x + button.size_x / 2 , button.y + button.size_y / 2 + 5);

    line(button.x + 5, button.y + 11, button.x + button.size_x / 2, button.y + button.size_y / 2 + 6);
    line(button.x + button.size_x - 5, button.y + 11, button.x + button.size_x / 2 - 1, button.y + button.size_y / 2 + 6);

    line(button.x + 6, button.y + 11, button.x + button.size_x / 2 +1, button.y + button.size_y / 2 + 6);
    line(button.x + button.size_x - 5, button.y + 11, button.x + button.size_x / 2 , button.y + button.size_y / 2 + 6);
}

void DrawButtonMode(Buttons button){
    setfillstyle(SOLID_FILL, COLER_LIGHTRED);
    bar(button.x + 5, button.y + button.size_y / 4 - 3, button.x + button.size_x - 5, button.y + button.size_y / 4 + 3);
    bar(button.x + 5, button.y + button.size_y / 4 * 2 - 3, button.x + button.size_x - 5, button.y + button.size_y / 4 * 2 + 3);
    bar(button.x + 5, button.y + button.size_y / 4 * 3 - 3, button.x + button.size_x - 5, button.y + button.size_y / 4 * 3 + 3);
}

void DrawButton(Buttons button, int coler){
    if (idKeyBoard(button.name) < 0) return;
    setfillstyle(SOLID_FILL, coler);
    bar(button.x, button.y, button.x + button.size_x, button.y + button.size_y);
    setcolor(COLER_BLUE);
    rectangle(button.x, button.y, button.x + button.size_x - 1, button.y + button.size_y - 1);
    if (idKeyBoard(button.name) == 102) DrawButtonHistory(button);
    if (idKeyBoard(button.name) == 101) DrawButtonMode(button);
}

void DrawTextButton(Buttons button, int coler, int bkcoler){
    if (idKeyBoard(button.name) < 0) return;
    setbkcolor(bkcoler);
    setcolor(coler);
    settextstyle(0, 0, 2);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    moveto(button.x + button.size_x / 2 -1, button.y + button.size_y / 2 + 3);
    outtext(button.name);
}

void ClickButton(Buttons button){
    if (idKeyBoard(button.name) < 0) return;
    //ClearButton(button);
    DrawButton(button, COLER_LIGHTBLUE);
    if (idKeyBoard(button.name) < 100) DrawTextButton(button, COLER_RED, COLER_LIGHTBLUE);
    Sleep(70);
    //ClearButton(button);
    DrawButton(button, COLER_LIGHTGREEN);
    if (idKeyBoard(button.name) < 100) DrawTextButton(button, COLER_RED, COLER_LIGHTGREEN);
    return;
}

#endif // BUTTON_H_INCLUDED 0986945387 rep em co aos xanh nhuwng em se di
