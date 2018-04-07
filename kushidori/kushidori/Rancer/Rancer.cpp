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
		z_pos.x -= 5;
	}
	if (Input::KeyD.pressed && area.br.x > z_pos.x)
	{
		z_pos.x += 5;
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
	Rect(base.x + z_pos.x - 20, base.y + z_pos.y - 20, 40, 40).draw(Palette::Red);
	Rect(base.x + z_pos.x - 2, base.y + z_pos.y - 100, 4, 80).draw(Palette::Crimson);
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