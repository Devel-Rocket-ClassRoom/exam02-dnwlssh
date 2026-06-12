#include "DrawBox.h"

void DrawBox(int startX, int startY, int width, int height)
{
    printW(startX, startY, L"┌─");
    printW(startX + width - 2, startY, L"─┐");
    printW(startX, startY + height - 1, L"└─");
    printW(startX + width - 2, startY + height - 1, L"─┘");

    // 가로 선 그리기
    for (int i = startX + 2; i < startX + width - 2; i += 2) 
    {
        printW(i, startY, L"──");
        printW(i, startY + height - 1, L"──");
    }

    // 세로 선 그리기
    for (int i = startY + 1; i < startY + height - 1; i++) 
    {
        printW(startX, i, L"│ ");
        printW(startX + width - 2, i, L" │");
    }
}
