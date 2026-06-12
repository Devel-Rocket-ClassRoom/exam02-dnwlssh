#include "Main.h"

int main() 
{
   // 콘솔 창 크기 조절 및 제목 설정
   system("mode con cols=70 lines=70");
   
   Weapon MyWeapon;

   //메인 인터페이스
   MainViewer(MyWeapon);

   COORD finalPos = { 0, 68 };
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), finalPos);
}
