#pragma once

#include"..\System\Informer.h"

#include<Siv3D.hpp>

#include<array>
#include<vector>

class Rancer
{
private:
	Point z_pos;
	bool z_isLeft = false;
	std::vector<Chicken*> z_chickenList;

public:
	void Initialize(const Point& pos);
	void Update(const Informer& informer, Rect area);
	void Draw(const Point& base);

	const Point& GetPos(void)const { return z_pos; }

	std::pair<bool, std::array<Chicken*, 3>> Offer(void);

	static const Texture& TexRancer(void);
	static const Texture& TexSpear(void);
	static const Sound& Voice(void);
};