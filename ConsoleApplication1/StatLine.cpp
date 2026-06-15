#include "StatLine.h"
#include <sstream>

std::wstring StatLine::GetFormattedText(double base, double add) const {
    double total = base + add;

    // 착용 레벨 감소의 경우 마이너스 수치이므로 음수일 때 줄을 생성해야 함
    if (type == StatType::ReqLevel) {
        if (add == 0) return L"";
        std::wstringstream wss;
        wss << name << L" : " << add; // 이미 음수이므로 그대로 출력
        return wss.str();
    }

    // 일반 스탯은 합산 총량이 0이면 줄을 그리지 않음
    if (total == 0) return L"";

    std::wstringstream wss;
    wss << name << L" : +" << total;
    if (isPercent) wss << L"%";

    // 추가 옵션이 존재할 때 괄호 툴팁 추가 표시 (예: LUK : +190 (+190 기본급 + 0 추가옵션))
    if (add > 0) {
        wss << L" (" << base << L" +" << add << L")";
    }
    return wss.str();
}