#include "PrintW.h"


void printW(int x, int y, const wchar_t* text)
{
    COORD pos = { (SHORT)x, (SHORT)y };
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // 1. 커서 위치 이동
    SetConsoleCursorPosition(hConsole, pos);

    // 2. 원래 콘솔 속성 정보 백업
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    WORD originalAttributes = csbi.wAttributes;

    // 3. 유니코드 텍스트 출력
    DWORD written;
    WriteConsoleW(hConsole, text, wcslen(text), &written, NULL);

    // 4. 콘솔 속성을 항상 원래 상태로 복구
    SetConsoleTextAttribute(hConsole, originalAttributes);
}
