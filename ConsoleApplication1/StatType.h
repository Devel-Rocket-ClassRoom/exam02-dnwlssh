#pragma once

// 무기 스탯 종류 (추가옵션 줄 생성 및 UI 출력용)
enum class StatType
{
	STR, DEX, LUK, INT,
	MaxHP, MaxMP,
	ReqLevel,		// 착용 레벨 감소
	DEF,			// 방어력
	ATT, M_ATT,		// 공격력, 마력
	BossDMG, Damage,// 보스 몬스터 공격 시 데미지, 데미지
	IDE,			// 몬스터 방어율 무시
	AllStat,			// 올스탯%
	STR_DEX, STR_INT, STR_LUK, DEX_INT, DEX_LUK, INT_LUK, //추가옵션을 위해서 생성
	CRate // 크리티컬 확률 (잠재,에잠용)
};

// 잠재능력 등급 (현재는 레전더리 고정이지만 확장성을 위해)
enum class Grade
{
	Rare,Epic,Unique,Legendary
};
