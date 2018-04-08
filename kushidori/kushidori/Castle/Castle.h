#pragma once

#include"..\System\Informer.h"

#include<Siv3D.hpp>

class Castle
{
private:
	Rect z_area;
	int z_hp = 0;

public:
	int GetHP(void) { return z_hp; }
	void Repair(int hp) { z_hp = hp; }

	void Initialize(const Point& pos);
	void Update(const Informer& informer);
	void Draw(const Point& base);

	static const Sound& Voice(void);
};