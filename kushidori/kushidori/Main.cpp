
#include"System\Informer.h"
#include"Chicken\Chicken.h"
#include"Ammo\Ammo.h"
#include"Rancer\Rancer.h"
#include"Goddess\Goddess.h"
#include"Castle\Castle.h"

# include <Siv3D.hpp>

#include<random>

void Main()
{
	Window::Resize(800, 800);

	const Font font(30);

	std::list<std::unique_ptr<Chicken>> ckn;
	std::list<std::unique_ptr<Ammo>> amm;

	Rancer rancer;
	rancer.Initialize(Point{ 100, 500 });

	Goddess goddess;
	goddess.Initialize(Point{ 750, 500 });

	Castle castle;
	castle.Initialize(Point{ 0, 100 });

	Informer informer(ckn, amm, rancer);

	int chickenTime = 100;
	int goddessTime = 100;
	unsigned int timeCount = 0;
	const unsigned int timeClear = 3600;
	std::random_device rnd;

	bool isStart = false;
	while (System::Update())
	{
		if (!isStart)
		{
			font(L"Press Space").draw({200, 200});

			if (Input::KeySpace.clicked)
			{
				isStart = true;
			}

			continue;
		}
		if (0 >= castle.GetHP())
		{
			font(L"Castle falls...").draw({ 200, 200 });

			continue;
		}

		font(Format(L"Goddess Smile : ", goddess.GetValue(), L"      Castle HP：", castle.GetHP())).draw();

		Circle(Mouse::Pos(), 50).draw({ 255, 0, 0, 127 });

		if (Input::MouseL.clicked)
		{
			amm.emplace_back(new AmSimple());
			amm.back()->Initialize(Point(0, 300), Mouse::Pos() - Point{ 0, 300 });
		}

		rancer.Update(informer, Rect(100, 0, 650, 0));
		goddess.Update(informer, rancer);
		castle.Update(informer);
		for (auto& w : ckn)
		{
			w->Update();
		}
		for (auto& a : amm)
		{
			a->Update(informer);
		}

		rancer.Draw(Point());
		goddess.Draw(Point());
		castle.Draw(Point());
		for (auto& w : ckn)
		{
			w->Draw(Point());
		}
		for (auto& a : amm)
		{
			a->Draw(Point());
		}

		if (60 < chickenTime && timeCount < timeClear)
		{
			chickenTime = 0;
			ckn.emplace_back(new White());
			ckn.back()->Initialize(Point(799, 100 + rnd() % 250));
		}
		else
		{
			chickenTime += 1;
		}
		if (60 < goddessTime && timeCount < timeClear)
		{
			goddessTime = 0;
			goddess.ResetTaste(informer);
		}
		else
		{
			goddessTime += 1;
		}

		for (auto itr = ckn.begin(); ckn.end() != itr;)
		{
			if (itr->get()->ShouldBeVanished(Rect(0, 0, 800, 500)))
			{
				itr = ckn.erase(itr);
			}
			else
			{
				++itr;
			}
		}
		for (auto itr = amm.begin(); amm.end() != itr;)
		{
			if (itr->get()->ShouldBeVanished(Rect(0, 0, 800, 500)))
			{
				itr = amm.erase(itr);
			}
			else
			{
				++itr;
			}
		}

		Rect(90, 670, 20, 60).draw();
		Rect(690, 670, 20, 60).draw();
		Circle(100 + static_cast<int>(static_cast<double>(timeCount) / static_cast<double>(timeClear) * 600), 700, 10).draw();

		if (timeClear < timeCount)
		{
			font(L"WINNER WINNER CHICKEN DINNER!").draw({ 50, 300 });
		}
		else
		{
			timeCount += 1;
		}
	}
}
