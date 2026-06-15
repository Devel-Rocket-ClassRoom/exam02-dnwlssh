#pragma once
#include "FlameStats.h"

class Weapon 
{
private:
	std::string name;
	WeaponStats stats;
public:
    Weapon();

    // 기본 스탯 초기화 (DEX, LUK +190, 공 +189, 보공 30%, 방무 20%)
    void InitBaseStats();
    // 추가옵션 초기화 및 랜덤 생성
    void RollAdditionalOptions();
    // 잠재능력 초기화 및 랜덤 생성
    void RollPotential();
    // 에디셔널 잠재능력 초기화 및 랜덤 생성
    void RollAdditionalPotential();


    const WeaponStats& GetStats() const{ return stats; }
    // 읽기/쓰기 가능 변경용 (일반 객체용 참조 반환)
    WeaponStats& GetStats() { return stats; }

    // 파일 저장 및 불러오기
    bool SaveToFile(const std::wstring& filename) const;
    bool LoadFromFile(const std::wstring& filename);
};

