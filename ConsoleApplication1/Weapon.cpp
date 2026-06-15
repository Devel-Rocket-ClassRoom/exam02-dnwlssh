#include "Weapon.h"
#include "PotentialData.h"
#include "AdditionalData.h"

#include <fstream>
#include <codecvt>
#include <locale>
#include <sstream>

Weapon::Weapon() 
{
    // 무작위 시드 초기화 (Main에서 수행해도 좋으나 안전장치로 추가)
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(NULL)));
        seeded = true;
    }
    InitBaseStats(); // 생성자에서 자동으로 초기화하도록 호출
}

void Weapon::InitBaseStats()
{
    // 기존 데이터가 있을지 모르니 깔끔하게 비우고 시작
    stats.baseStats.clear();
    stats.addOptions.clear();

    // 데스티니 가즈 기본 스탯 설정
    stats.baseStats[StatType::DEX] = 190;
    stats.baseStats[StatType::LUK] = 190;
    stats.baseStats[StatType::ATT] = 189;         // 공격력
    stats.baseStats[StatType::BossDMG] = 30;   // 보스 몬스터 공격 시 데미지 (%)
    stats.baseStats[StatType::IDE] = 20;    // 몬스터 방어율 무시 (%)

    // 나머지 동적 UI 출력을 위해 쓰이는 스탯들은 0으로 초기화 (선택 사항)
    stats.baseStats[StatType::STR] = 0;
    stats.baseStats[StatType::INT] = 0;
    stats.baseStats[StatType::MaxHP] = 0;
    stats.baseStats[StatType::MaxMP] = 0;
    stats.baseStats[StatType::ReqLevel] = 0;
    stats.baseStats[StatType::DEF] = 0;
    stats.baseStats[StatType::M_ATT] = 0;
    stats.baseStats[StatType::Damage] = 0;
    stats.baseStats[StatType::AllStat] = 0;

}

void Weapon::RollAdditionalOptions() 
{
    // 1. 새로운 가챠를 위해 기존 추가옵션 데이터 클리어
    stats.addOptions.clear();

    // 2. 전체 19가지 추가옵션 타입 목록 구성 (이중 스탯 포함)
    std::vector<StatType> pool = 
    {
        StatType::STR, StatType::DEX, StatType::LUK, StatType::INT,
        StatType::STR_DEX, StatType::STR_INT, StatType::STR_LUK,
        StatType::DEX_INT, StatType::DEX_LUK, StatType::INT_LUK,
        StatType::MaxHP, StatType::MaxMP, StatType::ReqLevel, StatType::DEF,
        StatType::ATT, StatType::M_ATT, StatType::BossDMG, StatType::Damage, StatType::AllStat
    };

    // 3. rand()를 사용하여 중복 없이 4가지 옵션 추출 (피셔-예이츠 셔플 변형)
    for (size_t i = 0; i < 4; ++i) 
    {
        size_t r = i + rand() % (pool.size() - i);
        std::swap(pool[i], pool[r]);
    }

    // 4. 상위 4개 옵션에 대해 단계 확률 및 수치 테이블 매핑
    for (int i = 0; i < 4; ++i) 
    {
        StatType rolledType = pool[i];

        // 확률 설정: 4단계(0~28), 5단계(29~73), 6단계(74~98), 7단계(99)
        int rate = rand() % 100;
        int gradeIdx = 0; // 0: 4단계, 1: 5단계, 2: 6단계, 3: 7단계
        if (rate < 29)         gradeIdx = 0;
        else if (rate < 74)    gradeIdx = 1;
        else if (rate < 99)    gradeIdx = 2;
        else                   gradeIdx = 3;

        double value = 0.0;

        // 기획된 환생의 불꽃 수치 데이터 매칭
        switch (rolledType) {
        case StatType::STR:
        case StatType::DEX:
        case StatType::LUK:
        case StatType::INT:     value = (std::vector<double>{48, 60, 72, 84})[gradeIdx]; break;

        case StatType::STR_DEX:
        case StatType::STR_INT:
        case StatType::STR_LUK:
        case StatType::DEX_INT:
        case StatType::DEX_LUK:
        case StatType::INT_LUK: value = (std::vector<double>{26, 32, 39, 45})[gradeIdx]; break;

        case StatType::MaxHP:
        case StatType::MaxMP:   value = (std::vector<double>{1080, 1480, 1950, 2500})[gradeIdx]; break;
        case StatType::ReqLevel:value = (std::vector<double>{20, 25, 30, 35})[gradeIdx]; break;
        case StatType::DEF:     value = (std::vector<double>{24, 32, 40, 48})[gradeIdx]; break;
        case StatType::ATT:
        case StatType::M_ATT:   value = (std::vector<double>{59, 81, 106, 136})[gradeIdx]; break;
        case StatType::BossDMG: value = (std::vector<double>{8, 10, 12, 14})[gradeIdx]; break;
        case StatType::Damage:
        case StatType::AllStat: value = (std::vector<double>{4, 5, 6, 7})[gradeIdx]; break;
        }

        // 이중 스탯을 순수 단일 스탯의 벡터 공간으로 쪼개어 누적 분배
        if (rolledType == StatType::STR_DEX) {
            stats.addOptions[StatType::STR].push_back(value);
            stats.addOptions[StatType::DEX].push_back(value);
        }
        else if (rolledType == StatType::STR_INT) {
            stats.addOptions[StatType::STR].push_back(value);
            stats.addOptions[StatType::INT].push_back(value);
        }
        else if (rolledType == StatType::STR_LUK) {
            stats.addOptions[StatType::STR].push_back(value);
            stats.addOptions[StatType::LUK].push_back(value);
        }
        else if (rolledType == StatType::DEX_INT) {
            stats.addOptions[StatType::DEX].push_back(value);
            stats.addOptions[StatType::INT].push_back(value);
        }
        else if (rolledType == StatType::DEX_LUK) {
            stats.addOptions[StatType::DEX].push_back(value);
            stats.addOptions[StatType::LUK].push_back(value);
        }
        else if (rolledType == StatType::INT_LUK) {
            stats.addOptions[StatType::INT].push_back(value);
            stats.addOptions[StatType::LUK].push_back(value);
        }
        else if (rolledType == StatType::ReqLevel) {
            // 착용 레벨 감소 옵션은 마이너스로 처리
            stats.addOptions[rolledType].push_back(-value);
        }
        else {
            // 단일 옵션은 고유 스탯 키값 위치에 그대로 저장
            stats.addOptions[rolledType].push_back(value);
        }
    }
    stats.blackFlameCount++;
}
// ------------------------------잠재능력---------------------------------
Option PickOptionFromPool(const std::vector<PotentialRow>& pool) {
    double totalWeight = 0;
    for (const auto& row : pool) totalWeight += row.weight;

    double randVal = (static_cast<double>(rand()) / RAND_MAX) * totalWeight;

    double currentSum = 0;
    for (const auto& row : pool) {
        currentSum += row.weight;
        if (randVal <= currentSum) {
            Option opt;
            opt.Type = row.type;
            opt.Value = row.value;

            // 유니코드(wstring) 그대로 바로 대입
            opt.OptionName = row.name;

            return opt;
        }
    }
    return Option();
}

void Weapon::RollPotential() {
    stats.potential.clear();

    // 첫 번째, 두 번째, 세 번째 옵션 풀에서 독립적으로 각각 1줄씩 가챠 생성
    stats.potential.push_back(PickOptionFromPool(PotentialData::GetFirstPool()));
    stats.potential.push_back(PickOptionFromPool(PotentialData::GetSecondPool()));
    stats.potential.push_back(PickOptionFromPool(PotentialData::GetThirdPool()));

    stats.blackCubeCount++;
}


// ------------------------------에디셔널---------------------------------
Option PickOptionFromAdditionalPool(const std::vector<AdditionalRow>& pool) {
    double totalWeight = 0;
    for (const auto& row : pool) totalWeight += row.weight;

    double randVal = (static_cast<double>(rand()) / RAND_MAX) * totalWeight;
    double currentSum = 0;

    for (const auto& row : pool) {
        currentSum += row.weight;
        if (randVal <= currentSum) {
            Option opt;
            opt.Type = row.type;
            opt.Value = row.value;
            opt.OptionName = row.name; // 한글 깨짐 없는 wstring 대입
            return opt;
        }
    }
    return Option();
}

void Weapon::RollAdditionalPotential() {
    stats.additionalPotential.clear();

    // 1, 2, 3번째 줄을 독립 확률 테이블 풀에서 무작위 추출
    stats.additionalPotential.push_back(PickOptionFromAdditionalPool(AdditionalData::GetFirstPool()));
    stats.additionalPotential.push_back(PickOptionFromAdditionalPool(AdditionalData::GetSecondPool()));
    stats.additionalPotential.push_back(PickOptionFromAdditionalPool(AdditionalData::GetThirdPool()));

    stats.addCubeCount++;
}


//저장
bool Weapon::SaveToFile(const std::wstring& filename) const {
    // 유니코드(UTF-8/UTF-16) 저장을 위한 설정
    std::wofstream outFile(filename);
    if (!outFile.is_open()) return false;

    // 표준 기본 생성자
    outFile.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));

    // 1. 기본 스탯 저장 (baseStats)
    outFile << L"[BaseStats]\n";
    for (const auto& pair : stats.baseStats) {
        outFile << static_cast<int>(pair.first) << L" " << pair.second << L"\n";
    }

    // 2. 추가옵션 저장 (addOptions)
    outFile << L"[AddOptions]\n";
    for (const auto& pair : stats.addOptions) {
        outFile << static_cast<int>(pair.first) << L" " << pair.second.size();
        for (double val : pair.second) {
            outFile << L" " << val;
        }
        outFile << L"\n";
    }

    // 3. 잠재능력 저장 (potential)
    outFile << L"[Potential]\n";
    outFile << stats.potential.size() << L"\n";
    for (const auto& opt : stats.potential) {
        outFile << static_cast<int>(opt.Type) << L" " << opt.Value << L" " << opt.OptionName << L"\n";
    }

    // 4. 에디셔널 잠재능력 저장 (additionalPotential)
    outFile << L"[AdditionalPotential]\n";
    outFile << stats.additionalPotential.size() << L"\n";
    for (const auto& opt : stats.additionalPotential) {
        outFile << static_cast<int>(opt.Type) << L" " << opt.Value << L" " << opt.OptionName << L"\n";
    }


    outFile.close();
    return true;
}

// 로드
bool Weapon::LoadFromFile(const std::wstring& filename) {
    std::wifstream inFile(filename);
    if (!inFile.is_open()) return false;

    //표준 기본 생성자
    inFile.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));

    // 기존 데이터 초기화
    stats.baseStats.clear();
    stats.addOptions.clear();
    stats.potential.clear();
    stats.additionalPotential.clear();
     
    // 기존 세션 별 파싱
    std::wstring line;
    std::wstring currentSection = L"";

    while (std::getline(inFile, line)) {
        if (line.empty()) continue;

        // 섹션 확인
        if (line == L"[BaseStats]" || line == L"[AddOptions]" || line == L"[Potential]" || line == L"[AdditionalPotential]") {
            currentSection = line;
            continue;
        }

        std::wstringstream ss(line);

        if (currentSection == L"[BaseStats]") {
            int typeInt;
            double value;
            if (ss >> typeInt >> value) {
                stats.baseStats[static_cast<StatType>(typeInt)] = value;
            }
        }
        else if (currentSection == L"[AddOptions]") {
            int typeInt;
            size_t count;
            if (ss >> typeInt >> count) {
                std::vector<double> vals;
                double val;
                for (size_t i = 0; i < count; ++i) {
                    if (ss >> val) vals.push_back(val);
                }
                stats.addOptions[static_cast<StatType>(typeInt)] = vals;
            }
        }
  
        else if (currentSection == L"[Potential]" || currentSection == L"[AdditionalPotential]") {
            // 해당 섹션의 첫 라인은 개수이므로 숫자가 하나만 들어옵니다.
            if (line.find(L" ") == std::wstring::npos) continue;

            int typeInt;
            double value;
            ss >> typeInt >> value;

            // 나머지 문자열 전체를 OptionName으로 파싱 (공백 포함 공정 처리)
            std::wstring optionName;
            std::wstring temp;
            while (ss >> temp) {
                if (!optionName.empty()) optionName += L" ";
                optionName += temp;
            }

            Option opt;
            opt.Type = static_cast<StatType>(typeInt);
            opt.Value = value;
            opt.OptionName = optionName;

            if (currentSection == L"[Potential]") {
                stats.potential.push_back(opt);
            }
            else {
                stats.additionalPotential.push_back(opt);
            }
        }
    }
    inFile.close();
    return true;
}
