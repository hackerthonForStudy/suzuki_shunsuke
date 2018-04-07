#include"Chicken.h"

Chicken::~Chicken(void) = default;
void Chicken::Initialize(const Point& pos)
{
	z_pos = pos;

	OnInit();
}
void Chicken::Update(void)
{
	OnUpdate();

	z_pos += z_velocity;
}
void Chicken::Draw(const Point& base)
{
	OnDraw(base + z_pos);
}
bool Chicken::ShouldBeVanished(const Rect& area)const
{
	return z_isAtacked || z_isEaten || !area.contains(z_pos);
}
void Chicken::Sticked(void)
{
	z_velocity = Point();
}
void Chicken::Move(Point pos)
{
	z_pos = pos;
}

Circle White::GetHitCircle(void)const
{
	return Circle(GetPos(), 10);
}
void White::Hit(void)
{
	z_velocity.x = 0;
	z_velocity.y = 3;
}
Circle White::GetStickCircle(void)const
{
	Point pos = GetPos();
	return Circle(pos.x, pos.y - 8, 4);
}
int White::Attack(void)
{
	z_isAtacked = true;
	return 1;
}
void White::OnInit(void)
{
	z_velocity = { -3, 0 };
}
void White::OnUpdate(void)
{
}
void White::OnDraw(const Point& pos)const
{
	Circle(pos.x, pos.y, 10).draw(Palette::White);
}
std::unique_ptr<Chicken> White::GetNewChicken(void)
{
	return std::unique_ptr<Chicken>(new White);
}