#include "Weapon.h"   
#include "StatLine.h" 
#include "MainViewer.h"

//모두 추가옵션이 생성되었을 떄, 줄을 생성하고 그렇지 않으면 줄을 생성하지 않는다
double GetStatValueSafe(const std::map<StatType, double>& statMap, StatType type)
{
    auto it = statMap.find(type);
    if (it != statMap.end())
    {
        return it->second; // 키가 존재하면 그 값을 반환
    }
    return 0.0; // 키가 존재하지 않으면 에러를 내지 않고 안전하게 0 반환
}

double GetStatValueSafe(const std::map<StatType, std::vector<double>>& statMap, StatType type)
{
    auto it = statMap.find(type);
    if (it != statMap.end())
    {
        // vector 내부의 모든 요소(각 줄의 추가옵션 수치)를 더합니다.
        double sum = 0.0;
        for (double val : it->second) {
            sum += val;
        }
        return sum;
    }
    return 0.0; // 추가옵션 줄이 아예 없다면 안전하게 0.0 반환
}

void RenderWeaponStats(int startX, int startY, const Weapon& weapon)
{
    static const std::vector<StatLine> displayOrder = {
        { StatType::STR,         L"STR" },
        { StatType::DEX,         L"DEX" },
        { StatType::LUK,         L"LUK" },
        { StatType::INT,         L"INT" },
        { StatType::MaxHP,       L"최대 HP" },
        { StatType::MaxMP,       L"최대 MP" },
        { StatType::ReqLevel,    L"착용 레벨 감소" },
        { StatType::DEF,         L"방어력" },
        { StatType::ATT,         L"공격력" },
        { StatType::M_ATT,       L"마력" },
        { StatType::BossDMG,     L"보스 몬스터 공격 시 데미지", true },
        { StatType::IDE,         L"몬스터 방어율 무시", true },
        { StatType::Damage,      L"데미지", true },
        { StatType::AllStat,     L"올스탯", true }
    };

    int currentY = startY;
    const auto& stats = weapon.GetStats(); // const 참조로 안전하게 가져옴

    for (const auto& line : displayOrder) {
        StatType type = line.GetType();

        //.at() 대신 안전한 함수를 사용하여 기본값과 추가옵션을 가져옵니다.
        double base = GetStatValueSafe(stats.baseStats, type);
        double add = GetStatValueSafe(stats.addOptions, type);

        std::wstring textToPrint = line.GetFormattedText(base, add);

        if (!textToPrint.empty()) {
            printW(startX, currentY, textToPrint.c_str());
            currentY++;
        }
    }

    printW(startX, 39, L"강화불가");
}


// 메뉴 탭 함수
void DrawBottomTabs()
{
    // Y=42 위치에 메뉴 상자 생성
    DrawBox(2, 55, 55, 4);
    printW(4, 56, L"1. 추가옵션  2. 잠재능력  3. 에디셔널 잠재능력");
    printW(4, 57, L"4. 스펙 저장  5. 스펙 불러오기");
}

//------------------------------------------추가옵션-----------------------------------------------//
// 추가옵션 전용 페이지 화면 구현
// tempStats: 가챠 도중 실시간으로 바뀔 임시 추가옵션 상태를 보여주기 위함
void FlameOptionPage(Weapon& weapon, const WeaponStats& tempStats)
{
    // 화면 초기화를 위해 기존 UI 영역을 공백으로 덮거나 system("cls") 처리
    system("cls");

    // 기본 무기 정보 틀 재렌더링
    DrawBox(2, 2, 55, 15);
    printW(4, 3, L"무기분류 : 아대(두손무기)");
    printW(4, 4, L"공격속도 : 빠름(6단계)");

    // 현재 무기가 가진 오리지널 기본 스탯(baseStats)과 
    // 매개변수로 전달받은 가챠 진행 중인 임시 추가옵션(tempStats.addOptions)을 조합하여 화면에 동적 출력
    int currentY = 5;

    static const std::vector<StatLine> displayOrder = {
        { StatType::STR,         L"STR" }, { StatType::DEX,         L"DEX" },
        { StatType::LUK,         L"LUK" }, { StatType::INT,         L"INT" },
        { StatType::MaxHP,       L"최대 HP" }, { StatType::MaxMP,       L"최대 MP" },
        { StatType::ReqLevel,    L"착용 레벨 감소" }, { StatType::DEF,         L"방어력" },
        { StatType::ATT,         L"공격력" }, { StatType::M_ATT,       L"마력" },
        { StatType::BossDMG,     L"보스 몬스터 공격 시 데미지", true },
        { StatType::IDE,         L"몬스터 방어율 무시", true },
        { StatType::Damage,      L"데미지", true }, { StatType::AllStat,     L"올스탯", true }
    };

    const WeaponStats& originalStats = weapon.GetStats();

    for (const auto& line : displayOrder) {
        StatType type = line.GetType();
        double base = GetStatValueSafe(originalStats.baseStats, type);
        // 무기 원본이 아닌, 현재 가챠로 돌아간 임시 옵션 맵에서 가져옵니다.
        double add = GetStatValueSafe(tempStats.addOptions, type);

        std::wstring textToPrint = line.GetFormattedText(base, add);
        if (!textToPrint.empty()) {
            printW(4, currentY, textToPrint.c_str());
            currentY++;
        }
    }
    printW(4, 15, L"강화불가");

    // 하단 조작 버튼 탭 메뉴 출력
    DrawBox(2, 18, 55, 6);
    printW(4, 20, L"[추가옵션 설정]");
    printW(4, 22, L"1. 재설정하기  2. 현재 옵션 선택(적용)  3. 이전으로");
}

//------------------------------------------잠재능력-----------------------------------------------//
//잠재능력 설정용 전용 UI 페이지
void PotentialPage(Weapon& weapon, const WeaponStats& tempStats) {
    system("cls");
    DrawBox(2, 2, 55, 8);
    printW(4, 4, L"[현재 잠재능력 등급 : 레전더리]");

    int py = 6;
    if (tempStats.potential.empty()) {
        printW(6, py, L"옵션이 아직 설정되지 않았습니다.");
    }
    else {
        for (const auto& opt : tempStats.potential) {
            printW(6, py++, opt.OptionName.c_str());
        }
    }

    DrawBox(2, 15, 55, 6);
    printW(4, 17, L"[잠재능력 설정 모드]");
    printW(4, 19, L"1. 재설정하기  2. 현재 옵션 선택(적용)  3. 이전으로");
}

//------------------------------------------에디셔널-----------------------------------------------//
void AdditionalPotentialPage(Weapon& weapon, const WeaponStats& tempStats) {
    system("cls");
    DrawBox(2, 2, 55, 8);
    printW(4, 4, L"[현재 에디셔널 잠재능력 등급 : 레전더리]");

    int py = 6;
    if (tempStats.additionalPotential.empty()) {
        printW(6, py, L"옵션이 아직 설정되지 않았습니다.");
    }
    else {
        for (const auto& opt : tempStats.additionalPotential) {
            printW(6, py++, opt.OptionName.c_str());
        }
    }

    DrawBox(2, 15, 55, 6);
    printW(4, 17, L"[에디셔널 잠재능력 설정 모드]");
    printW(4, 19, L"1. 재설정하기  2. 현재 옵션 선택(적용)  3. 이전으로");
}

//메인 뷰어
void MainViewer(const Weapon& weapon)
{
    //[메인 화면] 창 틀 생성
    DrawBox(2,6,55,20);
    printW(13, 7, L"★★★★★  ★★★★★  ★★★★★");
    printW(22, 8, L"★★★★★  ★★");
    //printW(4, 6, L"위대한 최초의 대적자의");
    printW(23, 10, L"데스티니 가즈");
    printW(19, 11, L"고유 아이템,교환 불가");

    // 3. 점자 아트를 배열로 분리하여 줄바꿈 오작동 방지
    const wchar_t* monster[] = {
        L"⣿⣿⣿⡏⠀⠀⢹⣿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿",
        L"⣿⡟⠁⠀⠀⣤⠀⠀⡤⠤⣞⠛⠻⢿⣿⣿⣿⣿",
        L"⡟⠃⠀⠀⡆⠘⡯⣽⡮⣵⢋⣴⡿⠃⠙⣿⣿⣿",
        L"⡇⠀⢠⣄⣇⣰⣿⣸⣿⣿⣿⣯⣴⢩⢹⣼⡿⢿",
        L"⠀⢰⣭⡭⠭⣽⡏⠀⠐⣸⡯⠔⣛⢣⡿⠋⠀⠘",
        L"⡆⠀⢘⠬⡥⢚⣇⣀⣚⡿⣿⠓⠒⠚⢧⣀⠀⢰",
        L"⡧⠀⠸⡀⠉⠁⢸⣽⡟⢻⠜⣷⠤⠤⠒⠋⠀⣸",
        L"⡟⠀⠀⠑⣄⣀⣀⣨⣷⡼⠄⠸⠃⠀⠀⠀⣸⣿",
        L"⣇⣀⣀⣀⡀⠈⠉⠉⠁⣀⣀⣀⣀⣤⣤⣾⣿⣿"
    };

    // 점자 아트를 상자 내부 오른쪽(X=45, Y=5부터)에 차례대로 출력
    int startX = 4;
    int startY = 12;
    for (int i = 0; i < 9; i++) {
        printW(startX, startY + i, monster[i]);
    }
    printW(43, 12, L"공력력 증가량");
    printW(23, 18, L"◾REQ LEV : 250");
    printW(23, 19, L"◾REQ STR : 000"); printW(40, 19, L"◾REQ LUK : 600");
    printW(23, 20, L"◾REQ DEX : 000"); printW(40, 20, L"◾REQ INT : 000");
    DrawBox(3, 22, 53, 3);
    printW(5, 23, L"초보자"); printW(15, 23, L"전사"); printW(23, 23, L"마법사"); printW(34, 23, L"궁수"); printW(43, 23, L"도적"); printW(51, 23, L"해적");
    
    //줄 27~38 까지
    DrawBox(2, 26, 55, 15);
    printW(4, 27, L"무기분류 : 아대(두손무기)");
    printW(4, 28, L"공격속도 : 빠름(6단계)");

    // 추가옵션 설정
    RenderWeaponStats(4, 29, weapon);

    // ------------------------------- 잠재능력---------------------------------
    // 잠재 능력 탭 추가
    DrawBox(2, 41, 55, 7); // 잠재능력 박스

    // 등급 마크 강조 출력
    printW(4, 42, L"잠재능력 설정");
    printW(4, 43, L"[ 레전더리 등급 ]");

    const auto& pList = weapon.GetStats().potential;
 
    // 만약 잠재능력이 아직 재설정되지 않은 초기 상태라면 안내 텍스트 출력
    if (pList.empty()) {
        printW(4, 44, L"  - 잠재옵션이 존재하지 않습니다.");
        printW(4, 45, L"  - 잠재능력을 재설정해 주세요.");
    }
    else {
        // 확정 설정된 3줄의 옵션을 차례대로 출력
        int startY = 44;
        for (const auto& opt : pList) {
            printW(4, startY++, (L"  - " + opt.OptionName).c_str());
        }
    }

    // ------------------------------- 에디셔널---------------------------------
    DrawBox(2, 48, 55, 7);
    printW(4, 49, L" 에디셔널 잠재능력 설정");
    printW(4, 50, L" [ 레전더리 등급 ]");

    const std::vector<Option>& addPList = weapon.GetStats().additionalPotential;
    if (addPList.empty()) {
        printW(4, 51, L"  - 에디셔널 옵션이 존재하지 않습니다.");
        printW(4, 52, L"  - 에디셔널 잠재능력을 재설정해 주세요.");
    }
    else {
        int apy = 51;
        for (const auto& opt : addPList) printW(4, apy++, (L"  - " + opt.OptionName).c_str());
    }


    DrawBox(59, 2, 32, 10); // 우측 상단 배치
    printW(61, 3, L"[ 사용된 재화 ]");

    const WeaponStats& ws = weapon.GetStats();

    // 숫자를 문자열로 안전하게 조합하여 출력하기 위해 std::wstring 생성
    std::wstring flameStr = L"• 검은 환생의 불꽃  : " + std::to_wstring(ws.blackFlameCount) + L" 개";
    std::wstring cubeStr = L"• 블랙 큐브         : " + std::to_wstring(ws.blackCubeCount) + L" 개";
    std::wstring addStr = L"• 에디셔널 큐브     : " + std::to_wstring(ws.addCubeCount) + L" 개";

    printW(61, 5, flameStr.c_str());
    printW(61, 7, cubeStr.c_str());
    printW(61, 9, addStr.c_str());

    DrawBottomTabs();
}

