#pragma once
#include "MainViewer.h"
#include "DrawBox.h"   
#include "PrintW.h"
#include "FlameStats.h"

class Weapon;

double GetStatValueSafe(const std::map<StatType, double>& statMap, StatType type);
void RenderWeaponStats(int startX, int startY, const Weapon& weapon);
void MainViewer(const Weapon& weapon);

// 추가옵션 인터페이스
void DrawBottomTabs();
void FlameOptionPage(Weapon& weapon, const WeaponStats& tempStats); // 추가옵션 페이지
void PotentialPage(Weapon& weapon, const WeaponStats& tempStats);	// 잠재능력 페이지
void AdditionalPotentialPage(Weapon& weapon, const WeaponStats& tempStats); // 에디셔널 페이지