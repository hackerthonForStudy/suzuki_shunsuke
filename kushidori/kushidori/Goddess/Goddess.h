#pragma once

#include"..\System\Informer.h"

#include<Siv3D.hpp>

#include<array>

class Rancer;
class Goddess
{
private:
	const Font z_font{ 20 };
	Point z_pos;

	int z_value = 0;
	std::array<std::unique_ptr<Chicken>, 3> z_taste{nullptr, nullptr, nullptr};

public:
	int GetValue(void) { return z_value; }
	void ConsumeValue(int cost) { z_value -= cost; }

	void Initialize(const Point& pos);
	void Update(const Informer& informer, Rancer& rancer);
	void Draw(const Point& base);

	void ResetTaste(const Informer& informer);

	static const Texture& Tex(void);
	static const Sound& VoiceEat(void);
	static const Sound& Voice1(void);
	static const Sound& Voice2(void);
};