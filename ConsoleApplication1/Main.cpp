#include "Main.h"

int main() 
{
   // 콘솔 창 크기 조절 및 제목 설정
   system("mode con cols=70 lines=70");
   
   Weapon MyWeapon;

   // 프로그램 실행 상태 제어 변수
   // 0: 메인화면, 1: 추가옵션 페이지, 2: 잠재능력(미구현), 3: 에디셔널(미구현)
   int pageState = 0;

   // 가챠 도중 "이전 옵션"과 "새 옵션"을 비교하거나 임시 저장해둘 임시 구조체
	WeaponStats tempGachaStats;

   //추가옵션 무작위 롤링 실행 (기본 스탯에 추가옵션이 누적됨!)
   MyWeapon.RollAdditionalOptions();

   //메인 인터페이스
   MainViewer(MyWeapon);

   COORD finalPos = { 0, 68 };
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), finalPos);


   while (true)
   {
       if (pageState == 0) // [0: 메인 화면 루프]
       {
           system("cls");
           MainViewer(MyWeapon); // 메인 UI 렌더링

           // 입력 유도 문자 위치 지정
           printW(2, 48, L"원하는 메뉴의 번호를 입력하세요: ");
           int input;
           std::cin >> input;

           if (input == 1) {
               // 1번 추가옵션 선택 시: 현재 무기의 추가옵션 상태를 복사하여 임시 보관하고 가챠 페이지로 이동
               tempGachaStats.addOptions = MyWeapon.GetStats().addOptions;
               pageState = 1;
           }
           else if (input == 2) {
               // 잠재능력 (현재 미구현 안내)
               printW(2, 50, L"잠재능력 페이지는 현재 준비 중입니다.");
               Sleep(1000);
           }
           else if (input == 3) {
               // 에디셔널 잠재능력 (현재 미구현 안내)
               printW(2, 50, L"에디셔널 잠재능력 페이지는 현재 준비 중입니다.");
               Sleep(1000);
           }
       }
       else if (pageState == 1) // [1: 추가옵션 설정 페이지 루프]
       {
           FlameOptionPage(MyWeapon, tempGachaStats);

           printW(2, 25, L"원하는 작업의 번호를 입력하세요: ");
           int gachaInput;
           std::cin >> gachaInput;

           if (gachaInput == 1)
           {
               // 1. 추가옵션 재설정 눌렀을 시
               // 임시 객체나 MyWeapon의 내부 가챠 함수를 빌려 tempGachaStats의 addOptions를 계속 무작위 갱신
               // 임시로 옵션을 돌리기 위해 MyWeapon을 가챠 머신으로 활용합니다.
               MyWeapon.RollAdditionalOptions();

               // 새로 롤링된 무기 데이터를 임시 보관함에 빼내어 저장 (화면에 보여줄 용도)
               tempGachaStats.addOptions = MyWeapon.GetStats().addOptions;
           }
           else if (gachaInput == 2)
           {
               // 2. 현재 추가옵션 선택(확정) 눌렀을 시
               // 마지막으로 가챠 성공해서 tempGachaStats에 들어있는 추가옵션 데이터를 원본 무기에 덮어쓰기
               MyWeapon.GetStats().addOptions = tempGachaStats.addOptions;
            
               printW(2, 27, L"추가옵션이 무기에 성공적으로 적용되었습니다!");
               Sleep(1200);
               pageState = 0; // 메인 화면으로 복귀
           }
           else if (gachaInput == 3)
           {
               // 3. 이전으로 돌아가기 눌렀을 시
               // 원본 무기의 옵션은 그대로 유지한 채로 메인 화면으로 나감 (가챠 도중 나온 값 버림)
               pageState = 0;
           }
       }
   }

   return 0;
}
