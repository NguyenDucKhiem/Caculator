#ifndef HISTORY_H_INCLUDED
#define HISTORY_H_INCLUDED

#include "Graphics.h"
#include "LinkedList.h"
#include "Posfix.h"

#define SIZE_X_HISTORY 290
#define SIZE_Y_HISTORY 500

#define EXIT_X 260
#define EXIT_Y 45
#define SIZE_EXIT_X 25
#define SIZE_EXIT_Y 25

void printExpression(LinkedList *link, int x, int *y){
    int maxlength = 15;
    if (link == NULL || link->Head == NULL) return;
    List *l = link->Head;
    char *s = (char *) malloc (20 * sizeof(char));

    while (l != NULL){
        sprintf(s, "%s", l->item);
        if (maxlength > strlen(s)){
            outtext(s);
            maxlength -= strlen(s) + 1;
            sprintf(s, " ");
            outtext(s);
            l = l->next;
        } else if (maxlength == strlen(s)){
            outtext(s);
            break;
        } else{
            char *n;
            n = s + (strlen(s) - maxlength);
            outtext(n);
            n[0] = '\0';
            *y = *y + 20;
            moveto(x, *y);
            outtext(s);
            outtext(" ");
            maxlength = 15;
            l = l->next;
        }
    }
    free(s);
}

void initHistory(LinkedList **ListResult, int n){
    if (ListResult == NULL || n < 0)
        return;
    int y = 90;
    settextstyle(0, 0, 2);

    for (int i = n; i >= 0; i--) {
        if (ListResult[i] == NULL || ListResult[i]->Head == NULL)
            break;
        y = y + 20;
        char *ch = ListResult[i]->Head->item;
        int flag = idKeyBoard(ListResult[i]->Head->item);

        settextjustify(LEFT_TEXT, BOTTOM_TEXT);
        moveto(5, y);
        double result;

        char s[30];
        switch (flag){
            case 16:
                DeleteToHeadLL(ListResult[i]);
                result = Inffix_Posffix(ListResult[i]);
                printExpression(ListResult[i], 5, &y);
                AddToHeadLL(ListResult[i], ch);
                break;
            case 24:
                DeleteToHeadLL(ListResult[i]);
                result = sin(Inffix_Posffix(ListResult[i]));
                outtext("Sin(");
                printExpression(ListResult[i], 5, &y);
                outtext(")");
                AddToHeadLL(ListResult[i], ch);
                break;
            case 25:
                DeleteToHeadLL(ListResult[i]);
                result = cos(Inffix_Posffix(ListResult[i]));
                outtext("Cos(");
                printExpression(ListResult[i], 5, &y);
                outtext(")");
                AddToHeadLL(ListResult[i], ch);
                break;
            case 26:
                DeleteToHeadLL(ListResult[i]);
                result = tan(Inffix_Posffix(ListResult[i]));
                outtext("Tan(");
                printExpression(ListResult[i], 5, &y);
                outtext(")");
                AddToHeadLL(ListResult[i], ch);
                break;
            case 27:
                DeleteToHeadLL(ListResult[i]);
                result = 1 / Inffix_Posffix(ListResult[i]);
                outtext("1/(");
                printExpression(ListResult[i], 5, &y);
                outtext(")");
                AddToHeadLL(ListResult[i], ch);
                break;
            case 28:
                DeleteToHeadLL(ListResult[i]);
                result = log(Inffix_Posffix(ListResult[i]));
                outtext("Log(");
                printExpression(ListResult[i], 5, &y);
                outtext(")");
                AddToHeadLL(ListResult[i], ch);
                break;
            case 29:
                DeleteToHeadLL(ListResult[i]);
                result = pow(Inffix_Posffix(ListResult[i]), 2);
                outtext("(");
                printExpression(ListResult[i], 5, &y);
                outtext(")^2");
                AddToHeadLL(ListResult[i], ch);
                break;
            default: result = Inffix_Posffix(ListResult[i]);
                printExpression(ListResult[i], 5, &y);

        }

        y = y + 20;
        moveto(280, y);
        sprintf(s, "%f", result);
        FixResult(s);

        settextjustify(RIGHT_TEXT, BOTTOM_TEXT);
        if (s[0] == '\0') outtext("0");
        else outtext(s);
        outtext("= ");
    }
}

void DrawHistory(LinkedList **ListResult, int n){
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
    outtext("History");

    setcolor(COLER_BLACK);
    setfillstyle(SOLID_FILL, COLER_LIGHTRED);
    bar(EXIT_X, EXIT_Y, EXIT_X + SIZE_EXIT_X, EXIT_Y + SIZE_EXIT_Y);
    rectangle(EXIT_X, EXIT_Y, EXIT_X + SIZE_EXIT_X - 1, EXIT_Y + SIZE_EXIT_Y - 1);

    setcolor(COLER_WHITE);
    line(EXIT_X + 2, EXIT_Y + 2, EXIT_X + SIZE_EXIT_X - 2, EXIT_Y + SIZE_EXIT_Y - 2);
    line(EXIT_X + SIZE_EXIT_X - 2, EXIT_Y + 2, EXIT_X + 2, EXIT_Y + SIZE_EXIT_Y - 2);

    setcolor(COLER_LIGHTRED);
    setbkcolor(COLER_LIGHTCYAN);
    initHistory(ListResult, n);

    int flag = 1;
    while (flag){
        delay(0.0001);
        if (ismouseclick(WM_LBUTTONDOWN)){
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if (x > EXIT_X && x < EXIT_X + SIZE_EXIT_X && y > EXIT_Y  && y < EXIT_Y + SIZE_EXIT_Y ) flag = 0;
        }
    }
 //   clearviewport();

    putimage(0, 0, p, COPY_PUT);
    free(p);
}

#endif // HISTORY_H_INCLUDED
