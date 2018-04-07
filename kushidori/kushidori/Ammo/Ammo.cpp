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
	return z_flagVanish || !area.contains(GetPos());
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
			z_flagVanish = true;
			break;
		}
	}
}
void AmSimple::OnDraw(const Point& pos)const
{
	Circle(pos.x, pos.y, 10).draw(Palette::Green);
}

double AmSpeed::ValueOfInitialVelocity(void)
{
	switch (z_level)
	{
	case 1:
		return 500.0;
	case 2:
		return 700.0;
	case 3:
		return 900.0;
	case 4:
		return 1100.0;
	}
	return 0.0;
}
void AmSpeed::OnInit(void)
{
}
void AmSpeed::OnUpdate(const Informer& informer)
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
void AmSpeed::OnDraw(const Point& pos)const
{
	Circle(pos.x, pos.y, 10).draw(Palette::Blue);
}


void AmExplode::OnInit(void)
{
}
void AmExplode::OnUpdate(const Informer& informer)
{
	if (!z_isExploding)
	{
		for (const auto& chicken : informer.GetListChicken())
		{
			if (!chicken->IsSticked()
				&& Circle(GetPos(), ExplodeRadius()).intersects(chicken->GetHitCircle()))
			{
				z_isExploding = true;
				z_velocity.x = 0;
				break;
			}
		}
	}
	if(z_isExploding)
	{
		z_explodingCount += 1;
		z_velocity.y = 0;
		for (const auto& chicken : informer.GetListChicken())
		{
			if (!chicken->IsSticked()
				&& Circle(GetPos(), ExplodeRadius()).intersects(chicken->GetHitCircle()))
			{
				chicken->Hit();
			}
		}
	}
	if (60 < z_explodingCount)
	{
		z_flagVanish = true;
	}
}
void AmExplode::OnDraw(const Point& pos)const
{
	if (z_isExploding)
	{
		Circle(pos.x, pos.y, ExplodeRadius()).draw(Palette::Crimson);
	}
	else
	{
		Circle(pos.x, pos.y, 10).draw(Palette::Red);
	}
}
double AmExplode::ExplodeRadius(void)const
{
	switch (z_level)
	{
	case 1:
		return 20.0;
	case 2:
		return 40.0;
	case 3:
		return 60.0;
	case 4:
		return 80.0;
	}
	return 0.0;
}