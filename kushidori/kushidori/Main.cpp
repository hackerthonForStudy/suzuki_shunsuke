
#include"System\Informer.h"
#include"Chicken\Chicken.h"
#include"Ammo\Ammo.h"
#include"Rancer\Rancer.h"
#include"Goddess\Goddess.h"
#include"Castle\Castle.h"

# include <Siv3D.hpp>

#include<random>

struct GenTable
{
	unsigned int spawnMax = 0;
	unsigned int spawnSpeed = 0;
	unsigned int time = 0;
	int sound = -1;
};
enum class AmmoType
{
	Normal
	, Explode
	, Speed
};

void Main()
{
	Window::Resize(800, 800);

	const Texture bg(L"../Resource/bg.jpg");

	const Font font(30);
	const Font font15(15);

	std::vector<GenTable> stage = {
		{5, 1, 6540, 1}
		, {0, 0, 1200, -1}
		, {2, 2, 2400, 2}
		, {5, 4, 3780, -1}
		, {1, 10, 1200, -1}
		, {0, 0, 1200, -1}
		, {5, 8, 3600, 3}
		, {5, 16, 3600, -1} };
	unsigned int indexStage = 1000;
	const Sound bgm[] = {
	Sound(L"../Resource/9002.mp3")
	, Sound(L"../Resource/6563.mp3")
	, Sound(L"../Resource/4452.mp3") };
	const Sound fan(L"../Resource/4452.mp3");

	std::list<std::unique_ptr<Chicken>> ckn;
	std::list<std::unique_ptr<Ammo>> amm;

	Rancer rancer;
	rancer.Initialize(Point{ 100, 500 });

	Goddess goddess;
	goddess.Initialize(Point{ 680, 400 });

	Castle castle;
	castle.Initialize(Point{ 0, 100 });

	Informer informer(ckn, amm, rancer);

	int chickenTime = 100;
	int goddessTime = 100;
	unsigned int timeCount = 0;
	std::random_device rnd;

	int reloadCount = 100;
	int reloadSpeed = 1;

	//祝福
	int repairCost = 5;
	int boostReloadCost = 30;
	int boostBulletExplodeCost = 20;
	int boostBulletSpeedCost = 20;
	int levelSpeed = 0;
	int levelExplode = 0;
	AmmoType ammoType = AmmoType::Normal;

	//敵生成
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> rndInt0to10;

	const Sound sndLevelUp(L"../Resource/decision7.mp3");

	bool isStart = false;
	bool isClear = false;
	while (System::Update())
	{
		if (!isStart)
		{
			font(L"Press Space").draw({ 200, 200 });
			font15(L"A D：左右移動。+ Shift で低速移動").draw({ 200, 300 });
			font15(L"Q：高速弾を使用。女神ポイントで解放").draw({ 200, 370 });
			font15(L"E：炸裂弾を使用。女神ポイントで解放").draw({ 200, 440 });
			font15(L"1～4：女神ポイントを消費").draw({ 200, 510 });

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

		if (1000 == indexStage)
		{
			indexStage = 0;
			bgm[stage[indexStage].sound - 1].playMulti(0.5);
		}
		bg(1050, 0, 400, 400).mirror().resize(800, 400).draw(0, 100);

		font(Format(L"Castle HP：", castle.GetHP())).draw();
		font(Format(L"Goddess Smile : ", goddess.GetValue())).draw(400, 0);

		Circle(Mouse::Pos(), 30).drawArc(0, 360);
		Circle(Mouse::Pos(), 10).drawArc(0, 360);
		LineInt(Mouse::Pos() - Point(0, 50), Mouse::Pos() + Point(0, 50)).draw();
		LineInt(Mouse::Pos() - Point(50, 0), Mouse::Pos() + Point(50, 0)).draw();

		//砲弾生成
		if (Input::MouseL.clicked)
		{
			switch (ammoType)
			{
			case AmmoType::Normal:
				amm.emplace_back(new AmSimple());
				break;
			case AmmoType::Speed:
				amm.emplace_back(new AmSpeed(levelSpeed));
				break;
			case AmmoType::Explode:
				amm.emplace_back(new AmExplode(levelExplode));
				break;
			}
			if (amm.back()->GetCost() > reloadCount)
			{
				amm.pop_back();
			}
			else
			{
				reloadCount -= amm.back()->GetCost();
				amm.back()->Initialize(Point(200, 300), Mouse::Pos() - Point{ 200, 300 });
			}
		}
		reloadCount = std::min(100, reloadCount + reloadSpeed);
		LineInt(Point(0, 100), Point(100, 100)).draw();
		Rect(0, 70, reloadCount, 20).draw(Palette::Gray);
		//砲弾切り替え
		if (Input::KeyQ.clicked && 0 < levelSpeed)
		{
			ammoType = AmmoType::Speed == ammoType ? AmmoType::Normal : AmmoType::Speed;
		}
		if (Input::KeyE.clicked && 0 < levelExplode)
		{
			ammoType = AmmoType::Explode == ammoType ? AmmoType::Normal : AmmoType::Explode;
		}
		switch (ammoType)
		{
		case AmmoType::Normal:
			font15(L"通常弾").draw(150, 70);
			break;
		case AmmoType::Speed:
			font15(L"高速弾").draw(150, 70);
			break;
		case AmmoType::Explode:
			font15(L"炸裂弾").draw(150, 70);
			break;
		}

		//祝福
		if (Input::Key1.clicked && goddess.GetValue() >= repairCost)
		{
			goddess.ConsumeValue(repairCost);
			castle.Repair(10);
			repairCost *= 2;
			sndLevelUp.playMulti(0.7);
		}
		if (Input::Key2.clicked && goddess.GetValue() >= boostReloadCost)
		{
			goddess.ConsumeValue(boostReloadCost);
			reloadSpeed += 1;
			boostReloadCost *= 2;
			sndLevelUp.playMulti(0.7);
		}
		if (Input::Key3.clicked && goddess.GetValue() >= boostBulletSpeedCost)
		{
			goddess.ConsumeValue(boostBulletSpeedCost);
			levelSpeed += 1;
			boostBulletSpeedCost *= 2;
			sndLevelUp.playMulti(0.7);
		}
		if (Input::Key4.clicked && goddess.GetValue() >= boostBulletExplodeCost)
		{
			goddess.ConsumeValue(boostBulletExplodeCost);
			levelExplode += 1;
			boostBulletExplodeCost *= 2;
			sndLevelUp.playMulti(0.7);
		}
		font15(Format(L"[1]城壁の修理：", repairCost)).draw({ 50, 530 });
		font15(Format(L"[2]装填時間短縮：", boostReloadCost)).draw({ 400, 530 });
		font15(Format(L"[3]高速弾強化：", boostBulletSpeedCost)).draw({ 50, 580 });
		font15(Format(L"[4]炸裂弾強化：", boostBulletExplodeCost)).draw({ 400, 580 });

		//更新
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

		//描画
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

		//鶏生成
		if (100 < chickenTime && !isClear)
		{
			switch (rndInt0to10(mt) % stage[indexStage].spawnMax)
			{
			case 0:
				ckn.emplace_back(new CkWhite());
				break;
			case 1:
				ckn.emplace_back(new CkYellow());
				break;
			case 2:
				ckn.emplace_back(new CkBlack());
				break;
			case 3:
				ckn.emplace_back(new CkSwallow());
				break;
			case 4:
				ckn.emplace_back(new CkSwan());
				break;
			}
			chickenTime -= ckn.back()->GetSpawnCost();
			ckn.back()->Initialize(Point(799, 100 + rnd() % 250));
		}
		else
		{
			chickenTime += stage[indexStage].spawnSpeed;
		}
		//女神
		if (1800 < goddessTime && !isClear)
		{
			goddessTime = 0;
			goddess.ResetTaste(informer);
		}
		else
		{
			goddessTime += 1;
		}
		
		//消滅
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

		//ステージ管理
		for (int index = 0; stage.size() > index; ++index)
		{
			Rect(100 + static_cast<int>(static_cast<double>(index) / static_cast<double>(stage.size()) * 600.0)
				, 720 - stage[index].spawnSpeed * 5
				, static_cast<int>(600.0 / static_cast<double>(stage.size())), stage[index].spawnSpeed * 10).draw(
					Color(stage[index].spawnMax * 50, 100, 255 - stage[index].spawnMax * 25));
		}
		Rect(90, 690, 20, 60).draw();
		Rect(690, 690, 20, 60).draw();
		int x = static_cast<int>(static_cast<double>(indexStage) / static_cast<double>(stage.size()) * 600.0);
		x += static_cast<int>(static_cast<double>(timeCount) / static_cast<double>(stage[indexStage].time)
			* (600.0 / static_cast<double>(stage.size())));
		Circle(100 + x, 720, 10).draw();

		if (stage[indexStage].time < timeCount)
		{
			if (stage.size() == indexStage + 1)
			{
				if (!isClear)
				{
					isClear = true;
					fan.playMulti(0.7);
				}

			}
			else
			{
				timeCount = 0;
				indexStage += 1;
				if (0 <= stage[indexStage].sound)
				{
					bgm[stage[indexStage].sound - 1].playMulti(0.5);
				}
			}
		}
		else if(180 == stage[indexStage].time - timeCount)
		{
			if (0 <= stage[indexStage].sound)
			{
				bgm[stage[indexStage].sound - 1].pause(3.0s);
			}
		}
		if (isClear)
		{
			font(L"WINNER WINNER CHICKEN DINNER!").draw({ 50, 300 });
		}
		else
		{
			timeCount += 1;
		}
	}
}
