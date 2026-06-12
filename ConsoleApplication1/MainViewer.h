#pragma once
#include "MainViewer.h"
#include "DrawBox.h"   
#include "PrintW.h"
#include "FlameStats.h"

class Weapon;

void MainViewer(const Weapon& weapon);
double GetStatValueSafe(const std::map<StatType, double>& statMap, StatType type);
void RenderWeaponStats(int startX, int startY, const Weapon& weapon);