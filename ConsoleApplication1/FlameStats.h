#pragma once
#include <string>
#include <map>
#include <vector>

#include "StatType.h"

#include "PrintW.h"
#include "DrawBox.h"

// 단일 옵션 정보를 담는 구조체 (잠재능력이나 추가옵션 한 줄을 표현)
struct Option
{
	std::string OptionName;	// UI 출력용 텍스트 (예: "공격력 : +12%")
    StatType Type;				// 내부 계산용 스탯 타입
	double Value;			// 수치 (정수, 실수 공용)
};

// 무기 내부 스탯을 일괄 관리하는 구조체
struct WeaponStats {
    // StatType을 키로 하여 수치를 저장 (기본 스탯 및 추가옵션 합산용)
    std::map<StatType, double> baseStats;
    std::map<StatType, double> addOptions; // 현재 적용된 추가옵션

    // 잠재 및 에디셔널 (각 3줄)
    std::vector<Option> potential;
    std::vector<Option> additionalPotential;
};

