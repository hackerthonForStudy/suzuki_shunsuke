#include"Rancer.h"

#include"..\Chicken\Chicken.h"

void Rancer::Initialize(const Point& pos)
{
	z_pos = pos;
	z_chickenList.reserve(3);
	z_chickenList.clear();
}
void Rancer::Update(const Informer& informer, Rect area)
{
	for (const auto& chicken : informer.GetListChicken())
	{
		if (3 > z_chickenList.size()
			&& chicken->GetStickCircle().intersects(Circle(z_pos.x - 2, z_pos.y - 100, 2.0)))
		{
			chicken->Sticked();
			z_chickenList.emplace_back(chicken.get());
		}
	}

	if (Input::KeyA.pressed && area.bl.x < z_pos.x)
	{
		z_pos.x -= Input::KeyShift.pressed ? 1 : 5;
		z_isLeft = true;
	}
	if (Input::KeyD.pressed && area.br.x > z_pos.x)
	{
		z_pos.x += Input::KeyShift.pressed ? 1 : 5;
		z_isLeft = false;
	}
	int y = 40;
	for (const auto pChicken : z_chickenList)
	{
		pChicken->Move(Point(z_pos.x, z_pos.y - y));
		y += 20;
	}
}
void Rancer::Draw(const Point& base)
{
	if (z_isLeft)
	{
		TexRancer().resize(90, 80).draw(base + z_pos + Point(-5, -50));
	}
	else
	{
		TexRancer().resize(90, 80).mirror().draw(base + z_pos + Point(-85, -50));
	}
	TexSpear().resize(80, 30).rotate(-103_deg).draw(base + z_pos + Point(-39, -80));
}
std::pair<bool, std::array<Chicken*, 3>> Rancer::Offer(void)
{
	if (3 != z_chickenList.size())
	{
		return std::make_pair(false, std::array<Chicken*, 3>());
	}

	std::array<Chicken*, 3> rtn = { z_chickenList[0], z_chickenList[1], z_chickenList[2] };
	z_chickenList.clear();
	return std::make_pair(true, rtn);
}
const Texture& Rancer::TexRancer(void)
{
	static const Texture tex(L"../Resource/anzu.png");
	return tex;
}
const Texture& Rancer::TexSpear(void)
{
	static const Texture tex(L"../Resource/spear.png");
	return tex;
}