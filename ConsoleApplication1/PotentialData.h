#pragma once
#include <string>
#include <vector>
#include "StatType.h"
#include "FlameStats.h" // Option 구조체 사용 목적

// 잠재능력 단일 행 정의
struct PotentialRow {
    std::wstring name;
    StatType type;
    double value;
    double weight; // 확률 가중치
};

class PotentialData {
public:
    // 첫 번째 옵션 풀
    static const std::vector<PotentialRow>& GetFirstPool() {
        static const std::vector<PotentialRow> pool = {
            { L"STR : +13%", StatType::STR, 13, 9.7561 },
            { L"DEX : +13%", StatType::DEX, 13, 9.7561 },
            { L"LUK : +13%", StatType::LUK, 13, 9.7561 },
            { L"INT : +13%", StatType::INT, 13, 9.7561 },
            { L"공격력 : +13%", StatType::ATT, 13, 4.8780 },
            { L"마력 : +13%", StatType::M_ATT, 13, 4.8780 },
            { L"크리티컬 확률 : +13 % ", StatType::CRate, 13, 4.8780 },
            { L"데미지 : +13%", StatType::Damage, 13, 4.8780 },
            { L"올스탯 : +10%", StatType::AllStat, 10, 7.3171 },
            { L"공격력 : +32", StatType::ATT, 32, 4.8780 },
            { L"마력 : +32", StatType::M_ATT, 32, 4.8780 },
            { L"몬스터 방어율 무시 : +40%", StatType::IDE, 40, 4.8780 },
            { L"몬스터 방어율 무시 : +45%", StatType::IDE, 45, 4.8780 },
            { L"보스 몬스터 공격 시 데미지 : +40%", StatType::BossDMG, 40, 9.7561 },
            { L"보스 몬스터 공격 시 데미지 : +45%", StatType::BossDMG, 45, 4.8780 }
        };
        return pool;
    }

    // 두 번째 옵션 풀
    static const std::vector<PotentialRow>& GetSecondPool() {
        static const std::vector<PotentialRow> pool = {
            { L"STR : +10%", StatType::STR, 10, 9.3023 }, { L"DEX : +10%", StatType::DEX, 10, 9.3023 },
            { L"INT : +10%", StatType::INT, 10, 9.3023 }, { L"LUK : +10%", StatType::LUK, 10, 9.3023 },
            { L"공격력 : +10%", StatType::ATT, 10, 5.5814 }, { L"마력 : +10%", StatType::M_ATT, 10, 5.5814 },{ L"크리티컬 확률 : +10%", StatType::M_ATT, 10, 7.4419 },
            { L"데미지 : +10%", StatType::Damage, 10, 5.5814 }, { L"올스탯 : +7%", StatType::AllStat, 7, 7.4419 },
            { L"몬스터 방어율 무시 : +35%", StatType::IDE, 35, 5.5814 }, { L"보스 몬스터 공격 시 데미지 : +35%", StatType::BossDMG, 35, 5.5814 },\
            // 이탈
            { L"STR : +13%", StatType::STR, 13, 1.9512 }, { L"DEX : +13%", StatType::DEX, 13, 1.9512 },
            { L"INT : +13%", StatType::INT, 13, 1.9512 }, { L"LUK : +13%", StatType::LUK, 13, 1.9512 },
            { L"공격력 : +13%", StatType::ATT, 13, 0.9756 }, { L"마력 : +13%", StatType::M_ATT, 13, 0.9756 }, { L"크리티컬 확률 : +13%", StatType::M_ATT, 10, 0.9756 },
            { L"데미지 : +13%", StatType::Damage, 13, 0.9756 }, { L"올스탯 : +10%", StatType::AllStat, 10, 1.4634 },
            { L"공격력 : +32", StatType::ATT, 32, 0.9756 }, { L"마력 : +32", StatType::M_ATT, 32, 0.9756 },
            { L"몬스터 방어율 무시 : +40%", StatType::IDE, 40, 0.9756 }, { L"몬스터 방어율 무시 : +45%", StatType::IDE, 45, 0.9756 },
            { L"보스 몬스터 공격 시 데미지 : +40%", StatType::BossDMG, 40, 1.9512 }, { L"보스 몬스터 공격 시 데미지 : +45%", StatType::BossDMG, 45, 0.9756 }
        };
        return pool;
    }

    // 세 번째 옵션 풀
    static const std::vector<PotentialRow>& GetThirdPool() {
        static const std::vector<PotentialRow> pool = {
            { L"STR : +10%", StatType::STR, 10, 11.04651 }, { L"DEX : +10%", StatType::DEX, 10, 11.04651 },
            { L"INT : +10%", StatType::INT, 10, 11.04651 }, { L"LUK : +10%", StatType::LUK, 10, 11.04651 },
            { L"공격력 : +10%", StatType::ATT, 10, 6.6279 }, { L"마력 : +10%", StatType::M_ATT, 10, 6.6279 },{ L"크리티컬 확률 : +10%", StatType::M_ATT, 10, 8.8372 },
            { L"데미지 : +10%", StatType::Damage, 10, 6.6279 }, { L"올스탯 : +7%", StatType::AllStat, 7, 8.8372 },
            { L"몬스터 방어율 무시 : +35%", StatType::IDE, 35, 6.6279 }, { L"보스 몬스터 공격 시 데미지 : +35%", StatType::BossDMG, 35, 6.6279 },\
            // 이탈
            { L"STR : +13%", StatType::STR, 13, 0.4878 }, { L"DEX : +13%", StatType::DEX, 13, 0.4878 },
            { L"INT : +13%", StatType::INT, 13, 0.4878 }, { L"LUK : +13%", StatType::LUK, 13, 0.4878 },
            { L"공격력 : +13%", StatType::ATT, 13, 0.2439 }, { L"마력 : +13%", StatType::M_ATT, 13, 0.2439 }, { L"크리티컬 확률 : +13%", StatType::M_ATT, 10, 0.2439 },
            { L"데미지 : +13%", StatType::Damage, 13, 0.2439 }, { L"올스탯 : +10%", StatType::AllStat, 10, 0.3659 },
            { L"공격력 : +32", StatType::ATT, 32, 0.2439 }, { L"마력 : +32", StatType::M_ATT, 32, 0.2439 },
            { L"몬스터 방어율 무시 : +40%", StatType::IDE, 40, 0.2439 }, { L"몬스터 방어율 무시 : +45%", StatType::IDE, 45, 0.2439 },
            { L"보스 몬스터 공격 시 데미지 : +40%", StatType::BossDMG, 40, 0.4878 }, { L"보스 몬스터 공격 시 데미지 : +45%", StatType::BossDMG, 45, 0.4878 }
        };
        return pool;
    }
};
