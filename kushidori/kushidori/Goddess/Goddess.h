#pragma once

#include"..\System\Informer.h"

#include<Siv3D.hpp>

#include<array>

class Rancer;
class Goddess
{
private:
	Point z_pos;

	int z_value = 0;
	std::array<std::unique_ptr<Chicken>, 3> z_taste{nullptr, nullptr, nullptr};

public:
	int GetValue(void) { return z_value; }

	void Initialize(const Point& pos);
	void Update(const Informer& informer, Rancer& rancer);
	void Draw(const Point& base);

	void ResetTaste(const Informer& informer);
};