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
    std::wstring GetFormattedText(double base, double add) const {
        double total = base + add;
        if (total == 0) return L""; // 값이 0이면 빈 문자열 반환

        std::wstringstream wss;
        wss << name << L" : +" << total;

        if (isPercent) wss << L"%";

        // 추가옵션이 있다면 괄호로 보너스 표시 (메이플 스타일: +190 (+0))
        if (add > 0) {
            wss << L" (" << base << L" +" << add << L")";
        }

        return wss.str();
    }
};