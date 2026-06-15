#pragma once
#include <string>
#include <vector>
#include "StatType.h"

struct AdditionalRow {
    std::wstring name;
    StatType type;
    double value;
    double weight;
};

class AdditionalData {
public:
    // 첫 번째 옵션 풀
    static const std::vector<AdditionalRow>& GetFirstPool() {
        static const std::vector<AdditionalRow> pool = {
            { L"최대 HP : +12%", StatType::MaxHP, 12, 7.6923 }, { L"최대 MP : +12%", StatType::MaxMP, 12, 7.6923 },
            { L"공격력 : +13%", StatType::ATT, 13, 5.1282 }, { L"마력 : +13%", StatType::M_ATT, 13, 5.1282 },
            { L"크리티컬 확률 : +13%", StatType::CRate, 13, 5.1282 },
            { L"STR : +13%", StatType::STR, 13, 7.6923 }, { L"DEX : +13%", StatType::DEX, 13, 7.6923 },
            { L"INT : +13%", StatType::INT, 13, 7.6923 }, { L"LUK : +13%", StatType::LUK, 13, 7.6923 },
            { L"데미지 : +13%", StatType::Damage, 13, 2.5641 }, { L"올스탯 : +10%", StatType::AllStat, 10, 5.1282 },
            { L"캐릭터 기준 9레벨 당 STR : +2", StatType::STR, 55, 5.1282 }, { L"캐릭터 기준 9레벨 당 DEX : +2", StatType::DEX, 55, 5.1282 },
            { L"캐릭터 기준 9레벨 당 INT : +2", StatType::INT, 55, 5.1282 }, { L"캐릭터 기준 9레벨 당 LUK : +2", StatType::LUK, 55, 5.1282 },
            { L"공격력 : +32", StatType::ATT, 32, 2.5641 }, { L"마력 : +32", StatType::M_ATT, 32, 2.5641 },
            { L"몬스터 방어율 무시 : +7%", StatType::IDE, 7, 2.5641 }, { L"보스 몬스터 공격 시 데미지 : +20%", StatType::BossDMG, 20, 2.5641 }
        };
        return pool;
    }

    // 두 번째 옵션 풀
    static const std::vector<AdditionalRow>& GetSecondPool() {
        static const std::vector<AdditionalRow> pool = {
            { L"최대 HP : +9%", StatType::MaxHP, 9, 6.9420 }, { L"최대 MP : +9%", StatType::MaxMP, 9, 6.9420 },
            { L"공격력 : +10%", StatType::ATT, 10, 4.6280 }, { L"마력 : +10%", StatType::M_ATT, 10, 4.6280 },
            { L"크리티컬 확률 : +10%", StatType::CRate, 10, 4.6280 },
            { L"STR : +10%", StatType::STR, 10, 6.9420 }, { L"DEX : +10%", StatType::DEX, 10, 6.9420 },
            { L"INT : +10%", StatType::INT, 10, 6.9420 }, { L"LUK : +10%", StatType::LUK, 10, 6.9420 },
            { L"데미지 : +10%", StatType::Damage, 10, 2.3140 }, { L"올스탯 : +7%", StatType::AllStat, 7, 4.6280 },
            { L"캐릭터 기준 9레벨 당 STR : +1", StatType::STR, 27, 4.6280 }, { L"캐릭터 기준 9레벨 당 DEX : +1", StatType::DEX, 27, 4.6280 },
            { L"캐릭터 기준 9레벨 당 INT : +1", StatType::INT, 27, 4.6280 }, { L"캐릭터 기준 9레벨 당 LUK : +1", StatType::LUK, 27, 4.6280 },
            { L"공격 시 15% 확률로 100의 HP 회복", StatType::MaxHP, 0, 6.9420 }, { L"공격 시 15% 확률로 100의 MP 회복", StatType::MaxMP, 0, 6.9420 },
            { L"몬스터 방어율 무시 : +6%", StatType::IDE, 6, 2.3140 }, { L"보스 몬스터 공격 시 데미지 : +14%", StatType::BossDMG, 14, 2.3140 },
            // 이탈 옵션 (첫 번째 옵션 풀 일부가 매우 낮은 확률로 등장)
            { L"최대 HP : +12%", StatType::MaxHP, 12, 0.03827 }, { L"최대 MP : +12%", StatType::MaxMP, 12, 0.03827 },
            { L"공격력 : +13%", StatType::ATT, 13, 0.02551 }, { L"마력 : +13%", StatType::M_ATT, 13, 0.02551 },
            { L"크리티컬 확률 : +13%", StatType::CRate, 13, 0.02551 }, { L"STR : +13%", StatType::STR, 13, 0.03827 },
            { L"DEX : +13%", StatType::DEX, 13, 0.03827 }, { L"INT : +13%", StatType::INT, 13, 0.03827 },
            { L"LUK : +13%", StatType::LUK, 13, 0.03827 }, { L"데미지 : +13%", StatType::Damage, 13, 0.01276 },
            { L"올스탯 : +10%", StatType::AllStat, 10, 0.02551 }, { L"캐릭터 기준 9레벨 당 STR : +2", StatType::STR, 55, 0.02551 },
            { L"캐릭터 기준 9레벨 당 DEX : +2", StatType::DEX, 55, 0.02551 }, { L"캐릭터 기준 9레벨 당 INT : +2", StatType::INT, 55, 0.02551 },
            { L"캐릭터 기준 9레벨 당 LUK : +2", StatType::LUK, 55, 0.02551 }, { L"공격력 : +32", StatType::ATT, 32, 0.01276 },
            { L"마력 : +32", StatType::M_ATT, 32, 0.01276 }, { L"몬스터 방어율 무시 : +7%", StatType::IDE, 7, 0.01276 },
            { L"보스 몬스터 공격 시 데미지 : +20%", StatType::BossDMG, 20, 0.01276 }
        };
        return pool;
    }

    // 세 번째 옵션 풀 (두 번째 풀과 기본 구성 동일, 가중치 최하단 이탈 확률도 동일)
    static const std::vector<AdditionalRow>& GetThirdPool() {
        return GetSecondPool();
    }
};
