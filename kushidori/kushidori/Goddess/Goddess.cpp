#include"Goddess.h"

#include"..\Chicken\Chicken.h"
#include"..\Rancer\Rancer.h"

#include<random>

void Goddess::Initialize(const Point& pos)
{
	z_pos = pos;
}
void Goddess::Update(const Informer& informer, Rancer& rancer)
{
	if (50 > std::abs(z_pos.x - rancer.GetPos().x))
	{
		auto [isDone, chickenList]= rancer.Offer();
		if (isDone)
		{
			int point = 0;
			for (const auto& pChicken : z_taste)
			{
				if (!pChicken)
				{
					point += 1;
					continue;
				}
				for (Chicken*& pChickenSticked : chickenList)
				{
					if (!pChickenSticked->IsEaten() && pChickenSticked->GetName() == pChicken->GetName())
					{
						point += 1;
						pChickenSticked->Eaten();
						break;
					}
				}
			}
			int value = 0;
			for (Chicken*& pChickenSticked : chickenList)
			{
				pChickenSticked->Eaten();
				if (0 == value)
				{
					value = pChickenSticked->GetValue();
					continue;
				}
				if (3 == point)
				{
					value *= pChickenSticked->GetValue();
				}
				else
				{
					value += pChickenSticked->GetValue();
				}
			}
			z_value += value;

			if (3 == point)
			{
				ResetTaste(informer);
			}
		}
	}
}
void Goddess::Draw(const Point& base)
{
	if (z_taste[0])
	{
		z_font(z_taste[0]->GetName()).draw(base.x + z_pos.x - 100, base.y + z_pos.y - 120);
	}
	if (z_taste[1])
	{
		z_font(z_taste[1]->GetName()).draw(base.x + z_pos.x - 100, base.y + z_pos.y - 90);
	}
	if (z_taste[2])
	{
		z_font(z_taste[2]->GetName()).draw(base.x + z_pos.x - 100, base.y + z_pos.y - 60);
	}

	Tex().resize(90, 120).draw(base + z_pos);
}
void Goddess::ResetTaste(const Informer& informer)
{
	std::random_device rnd;
	for (auto& upChicken : z_taste)
	{
		if (unsigned int index = rnd() % (informer.GetListChicken().size() + 3); informer.GetListChicken().size() > index)
		{
			auto itr = informer.GetListChicken().begin();
			for (unsigned int count = 0; index > count; ++count, ++itr);
			upChicken = itr->get()->GetNewChicken();
		}
		else
		{
			upChicken.reset(nullptr);
		}
	}
}
const Texture& Goddess::Tex(void)
{
	static const Texture tex(L"../Resource/goddess.png");
	return tex;
}