#pragma once
#include <string>
#include <sstream>
#include "StatType.h"

class StatLine {
private:
    StatType type;          // 스탯 종류 (열거형)
    std::wstring name;      // 화면에 표시될 한글 이름 (예: L"LUK", L"올스탯")
    bool isPercent;         // % 기호 여부 (보공, 올스탯 등은 true)

public:
    StatLine(StatType t, const std::wstring& n, bool pct = false)
        : type(t), name(n), isPercent(pct) {
    }

    StatType GetType() const { return type; }

    // 현재 스탯 상태(기본값 + 추가옵션)를 받아 출력할 최종 문자열을 만들어주는 함수
    std::wstring GetFormattedText(double base, double add) const;
};