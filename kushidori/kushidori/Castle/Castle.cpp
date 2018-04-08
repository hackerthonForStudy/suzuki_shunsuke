#include"Castle.h"

#include"..\Chicken\Chicken.h"

void Castle::Initialize(const Point& pos)
{
	z_area = Rect{ pos.x, pos.y, 50, 400 };
	z_hp = 10;
}
void Castle::Update(const Informer& informer)
{
	for (const auto& pChicken : informer.GetListChicken())
	{
		if (pChicken->GetHitCircle().intersects(z_area))
		{
			z_hp -= pChicken->Attack();
			Voice().playMulti(0.5);
		}
	}
}
void Castle::Draw(const Point&)
{
}
const Sound& Castle::Voice(void)
{
	static const Sound tex(L"../Resource/bomb1.mp3");
	return tex;
}
