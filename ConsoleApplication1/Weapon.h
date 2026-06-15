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
    //std::string GetName() const { return name; }

    // 기본 스탯 초기화 (DEX, LUK +190, 공 +189, 보공 30%, 방무 20%)
    void InitBaseStats();
    // 추가옵션 가챠 함수
    void RollAdditionalOptions();
    const WeaponStats& GetStats() const{ return stats; }
    // 읽기/쓰기 가능 변경용 (일반 객체용 참조 반환)
    WeaponStats& GetStats() { return stats; }

    // 추가 옵션 초기화
    void InitAddOptions();


    // 최종 스탯 계산 (기본 스탯 + 추가옵션) 후 반환
    double GetTotalStat(StatType type , int OptionLevel) {
        return stats.baseStats[type] + stats.addOptions[type][OptionLevel];
    }
 
};

