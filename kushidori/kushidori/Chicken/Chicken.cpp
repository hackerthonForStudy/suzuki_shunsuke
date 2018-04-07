#include"Chicken.h"

#include<random>

Chicken::~Chicken(void) = default;
void Chicken::Initialize(const Point& pos)
{
	z_pos.x = static_cast<double>(pos.x);
	z_pos.y = static_cast<double>(pos.y);

	OnInit();
}
void Chicken::Update(void)
{
	OnUpdate();

	z_pos.x += static_cast<double>(z_velocity.x);
	z_pos.y += static_cast<double>(z_velocity.y);
}
void Chicken::Draw(const Point& base)
{
	OnDraw(base + GetPos());
}
bool Chicken::ShouldBeVanished(const Rect& area)const
{
	return z_isAtacked || z_isEaten || !area.contains(GetPos());
}
void Chicken::Sticked(void)
{
	z_velocity.x = 0.0;
	z_velocity.y = 0.0;
}
void Chicken::Move(Point pos)
{
	z_pos.x = static_cast<double>(pos.x);
	z_pos.y = static_cast<double>(pos.y);
}
Point Chicken::GetPos(void)const
{
	return Point{ static_cast<Point::value_type>(z_pos.x), static_cast<Point::value_type>(z_pos.y) };
}

Circle CkWhite::GetHitCircle(void)const
{
	return Circle(GetPos(), 20);
}
void CkWhite::Hit(void)
{
	z_velocity.x = 0;
	z_velocity.y = 3;
	z_isHitten = true;
}
Circle CkWhite::GetStickCircle(void)const
{
	Point pos = GetPos();
	return Circle(pos.x, pos.y + 12, 8);
}
int CkWhite::Attack(void)
{
	z_isAtacked = true;
	return 1;
}
const Texture& CkWhite::Tex(void)
{
	static const Texture tex(L"../Resource/white.png");
	return tex;
}
void CkWhite::OnInit(void)
{
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::normal_distribution<> norm(0.2, 0.2);
	z_velocity = { -(norm(mt) + 1.0), 0.0 };
}
void CkWhite::OnUpdate(void)
{
}
void CkWhite::OnDraw(const Point& pos)const
{
	if (z_isHitten)
	{
		Tex().resize(40, 40).flip().draw(pos - Point(20, 20));
	}
	else
	{
		Tex().resize(40, 40).draw(pos - Point(20, 20));
	}
}
std::unique_ptr<Chicken> CkWhite::GetNewChicken(void)
{
	return std::unique_ptr<Chicken>(new CkWhite);
}

Circle CkYellow::GetHitCircle(void)const
{
	return Circle(GetPos(), 10);
}
void CkYellow::Hit(void)
{
	z_velocity.x = 0;
	z_velocity.y = 3;
	z_isHitten = true;
}
Circle CkYellow::GetStickCircle(void)const
{
	Point pos = GetPos();
	return Circle(pos.x, pos.y + 8, 8);
}
int CkYellow::Attack(void)
{
	z_isAtacked = true;
	return 1;
}
const Texture& CkYellow::Tex(void)
{
	static const Texture tex(L"../Resource/yellow.png");
	return tex;
}
void CkYellow::OnInit(void)
{
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::normal_distribution<> norm(0.2, 0.2);
	z_velocity = { -(norm(mt) + 0.5), 0.0 };
}
void CkYellow::OnUpdate(void)
{
}
void CkYellow::OnDraw(const Point& pos)const
{
	if (z_isHitten)
	{
		Tex().resize(20, 20).flip().draw(pos - Point(10, 10));
	}
	else
	{
		Tex().resize(20, 20).draw(pos - Point(10, 10));
	}
}
std::unique_ptr<Chicken> CkYellow::GetNewChicken(void)
{
	return std::unique_ptr<Chicken>(new CkYellow);
}

Circle CkBlack::GetHitCircle(void)const
{
	return Circle(GetPos(), 20);
}
void CkBlack::Hit(void)
{
	z_velocity.x = 0;
	z_velocity.y = 3;
	z_isHitten = true;
}
Circle CkBlack::GetStickCircle(void)const
{
	Point pos = GetPos();
	return Circle(pos.x, pos.y + 12, 8);
}
int CkBlack::Attack(void)
{
	z_isAtacked = true;
	return 1;
}
const Texture& CkBlack::Tex(void)
{
	static const Texture tex(L"../Resource/black.png");
	return tex;
}
void CkBlack::OnInit(void)
{
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::normal_distribution<> norm(0.2, 0.2);
	z_velocity = { -(norm(mt) + 1.0), 1.0 };
}
void CkBlack::OnUpdate(void)
{
	if (!z_isHitten)
	{
		z_count += 1;
	}
	if (90 == z_count)
	{
		z_velocity.y = -1.0;
	}
	else if(180 == z_count)
	{
		z_count = 0;
		z_velocity.y = 1.0;
	}
}
void CkBlack::OnDraw(const Point& pos)const
{
	if (z_isHitten)
	{
		Tex().resize(40, 40).flip().draw(pos - Point(20, 20));
	}
	else
	{
		Tex().resize(40, 40).draw(pos - Point(20, 20));
	}
}
std::unique_ptr<Chicken> CkBlack::GetNewChicken(void)
{
	return std::unique_ptr<Chicken>(new CkBlack);
}

Circle CkSwallow::GetHitCircle(void)const
{
	return Circle(GetPos(), 10);
}
void CkSwallow::Hit(void)
{
	z_velocity.x = 0;
	z_velocity.y = 3;
	z_isHitten = true;
}
Circle CkSwallow::GetStickCircle(void)const
{
	Point pos = GetPos();
	return Circle(pos.x, pos.y + 8, 8);
}
int CkSwallow::Attack(void)
{
	z_isAtacked = true;
	return 1;
}
const Texture& CkSwallow::Tex(void)
{
	static const Texture tex(L"../Resource/swallow.png");
	return tex;
}
void CkSwallow::OnInit(void)
{
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::normal_distribution<> norm(0.5, 0.2);
	z_velocity = { -(norm(mt) + 2.2), 0.0 };
}
void CkSwallow::OnUpdate(void)
{
}
void CkSwallow::OnDraw(const Point& pos)const
{
	if (z_isHitten)
	{
		Tex().resize(20, 20).flip().draw(pos - Point(10, 10));
	}
	else
	{
		Tex().resize(20, 20).draw(pos - Point(10, 10));
	}
}
std::unique_ptr<Chicken> CkSwallow::GetNewChicken(void)
{
	return std::unique_ptr<Chicken>(new CkSwallow);
}

Circle CkSwan::GetHitCircle(void)const
{
	return Circle(GetPos(), 20);
}
void CkSwan::Hit(void)
{
	z_velocity.x = 0;
	z_velocity.y = 3;
	z_isHitten = true;
}
Circle CkSwan::GetStickCircle(void)const
{
	Point pos = GetPos();
	return Circle(pos.x, pos.y + 12, 8);
}
int CkSwan::Attack(void)
{
	z_isAtacked = true;
	return 1;
}
const Texture& CkSwan::Tex(void)
{
	static const Texture tex(L"../Resource/crane.png");
	return tex;
}
void CkSwan::OnInit(void)
{
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::normal_distribution<> norm(1.0, 1.5);
	z_velocity = { -(norm(mt) + 4.0), 0.0 };
}
void CkSwan::OnUpdate(void)
{
}
void CkSwan::OnDraw(const Point& pos)const
{
	if (z_isHitten)
	{
		Tex().resize(40, 40).flip().draw(pos - Point(20, 20));
	}
	else
	{
		Tex().resize(40, 40).draw(pos - Point(20, 20));
	}
}
std::unique_ptr<Chicken> CkSwan::GetNewChicken(void)
{
	return std::unique_ptr<Chicken>(new CkSwan);
}