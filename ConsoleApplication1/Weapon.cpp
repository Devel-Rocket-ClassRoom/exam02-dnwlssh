#include "Weapon.h"

Weapon::Weapon() {
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
