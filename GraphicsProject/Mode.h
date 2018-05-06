#ifndef MODE_H_INCLUDED
#define MODE_H_INCLUDED

#include "Graphics.h"

#define SIZE_X_Mode 290
#define SIZE_Y_Mode 500

int DrawMode(){
    unsigned size;
    size = imagesize(0, 0, SIZE_X,  SIZE_Y);
    char *p = (char*)malloc(size);
    getimage(0, 0, SIZE_X, SIZE_Y, p);

//    setviewport(0, 0, SIZE_X, SIZE_Y, 0);

    setfillstyle(SOLID_FILL, COLER_LIGHTCYAN);
    bar(0, 40, SIZE_X_HISTORY, SIZE_Y_HISTORY);
    setcolor(COLER_BLUE);
    rectangle(0, 40, SIZE_X_HISTORY - 1, SIZE_Y_HISTORY - 1);

    settextstyle(0, 0, 2);
    settextjustify(CENTER_LINE, BOTTOM_TEXT);
    setbkcolor(COLER_LIGHTCYAN);
    setcolor(COLER_LIGHTRED);
    moveto(SIZE_X_HISTORY / 2 + 40, 60);
    outtext("Mode");

    setcolor(COLER_BLACK);
    setfillstyle(SOLID_FILL, COLER_LIGHTRED);
    bar(EXIT_X, EXIT_Y, EXIT_X + SIZE_EXIT_X, EXIT_Y + SIZE_EXIT_Y);
    rectangle(EXIT_X, EXIT_Y, EXIT_X + SIZE_EXIT_X - 1, EXIT_Y + SIZE_EXIT_Y - 1);

    setcolor(COLER_WHITE);
    line(EXIT_X + 2, EXIT_Y + 2, EXIT_X + SIZE_EXIT_X - 2, EXIT_Y + SIZE_EXIT_Y - 2);
    line(EXIT_X + SIZE_EXIT_X - 2, EXIT_Y + 2, EXIT_X + 2, EXIT_Y + SIZE_EXIT_Y - 2);

    moveto(15, 80);
    setcolor(COLER_LIGHTRED);
    settextjustify(LEFT_TEXT, TOP_TEXT);
    settextstyle(0, 0, 3);
    outtext("Standard");

    moveto(15,130);
    outtext("Scientific");


    int flag = -1;
    while (flag < 0){
        delay(0.0001);
        if (ismouseclick(WM_MOVE)){

        }
        if (ismouseclick(WM_LBUTTONDOWN)){
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);
            printf("%d %d\n", x, y);
            if (x > EXIT_X && x < EXIT_X + SIZE_EXIT_X && y > EXIT_Y  && y < EXIT_Y + SIZE_EXIT_Y) flag = EXIT;
            if (x > 0 && x < SIZE_X_Mode && y > 75 && y < 105) flag = STANDARD;
            if (x > 0 && x < SIZE_X_Mode && y > 125 && y < 155) flag = SCIENTIFIC;
        }
    }
 //   clearviewport();

    putimage(0, 0, p, COPY_PUT);
    free(p);
    return flag;
}

#endif // MODE_H_INCLUDED