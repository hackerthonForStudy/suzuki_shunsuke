#pragma once

#include"..\System\Informer.h"

#include<Siv3D.hpp>

#include<array>
#include<vector>

class Rancer
{
private:
	Point z_pos;
	std::vector<Chicken*> z_chickenList;

public:
	void Initialize(const Point& pos);
	void Update(const Informer& informer, Rect area);
	void Draw(const Point& base);

	const Point& GetPos(void)const { return z_pos; }

	std::pair<bool, std::array<Chicken*, 3>> Offer(void);
};