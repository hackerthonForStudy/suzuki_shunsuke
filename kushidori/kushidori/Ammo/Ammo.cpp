#include"Ammo.h"

#include"..\Chicken\Chicken.h"

Ammo::~Ammo(void) = default;
void Ammo::Initialize(const Point& pos, const Point& dir)
{
	z_pos.x = static_cast<double>(pos.x);
	z_pos.y = static_cast<double>(pos.y);
	double i = 1.0 / std::sqrt(static_cast<double>(dir.x * dir.x + dir.y * dir.y));
	z_velocity.x = static_cast<double>(dir.x) * i * std::sqrt(ValueOfInitialVelocity());
	z_velocity.y = static_cast<double>(dir.y) * i * std::sqrt(ValueOfInitialVelocity());
	OnInit();
}
void Ammo::Update(const Informer& informer)
{
	OnUpdate(informer);

	z_velocity.x *= 0.998;
	z_velocity.y += 0.2;
	z_pos.x += z_velocity.x;
	z_pos.y += z_velocity.y;
}
void Ammo::Draw(const Point& base)
{
	OnDraw(base + GetPos());
}
Point Ammo::GetPos(void)const
{
	return Point{ static_cast<Point::value_type>(z_pos.x), static_cast<Point::value_type>(z_pos.y) };
}
bool Ammo::ShouldBeVanished(const Rect& area)const
{
	return !area.contains(GetPos());
}

void AmSimple::OnInit(void)
{
}
void AmSimple::OnUpdate(const Informer& informer)
{
	for (const auto& chicken : informer.GetListChicken())
	{
		if (!chicken->IsSticked()
			&& Circle(GetPos(), 10).intersects(chicken->GetHitCircle()))
		{
			chicken->Hit();
		}
	}
}
void AmSimple::OnDraw(const Point& pos)const
{
	Circle(pos.x, pos.y, 10).draw(Palette::Green);
}