#include "Weapon.h"   
#include "StatLine.h" 


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
    DrawBox(2, 42, 55, 5);
    printW(4, 44, L"1. 추가옵션   2. 잠재능력   3. 에디셔널 잠재능력");
}

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

    // 💡 현재 무기가 가진 오리지널 기본 스탯(baseStats)과 
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
    RenderWeaponStats(4, 29, weapon);

    DrawBottomTabs();
}

