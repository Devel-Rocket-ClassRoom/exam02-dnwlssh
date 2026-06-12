#pragma once
#include "FlameStats.h"

class Weapon 
{
private:
	std::string name;
	WeaponStats stats;
public:
    Weapon();

    // Getter / Setter
    const WeaponStats& GetStats() const{ return stats; }
    std::string GetName() const { return name; }

    // 기본 스탯 초기화 (DEX, LUK +190, 공 +189, 보공 30%, 방무 20%)
    void InitBaseStats();

    // 최종 스탯 계산 (기본 스탯 + 추가옵션) 후 반환
    double GetTotalStat(StatType type) {
        return stats.baseStats[type] + stats.addOptions[type];
    }
 
};

