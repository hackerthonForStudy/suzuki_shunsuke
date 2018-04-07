#pragma once

#include"..\System\Informer.h"

#include<Siv3D.hpp>

class Ammo
{
public:
	struct Coord
	{
		double x;
		double y;
	};

protected:
	Coord z_velocity;

private:
	Coord z_pos;

public:
	virtual ~Ammo(void);

	void Initialize(const Point& pos, const Point& dir);
	void Update(const Informer& informer);
	void Draw(const Point& base);
	virtual bool ShouldBeVanished(const Rect& area)const;

protected:
	Point GetPos(void)const;

private:
	virtual double ValueOfInitialVelocity(void) = 0;

	virtual void OnInit() = 0;
	virtual void OnUpdate(const Informer& informer) = 0;
	virtual void OnDraw(const Point& pos)const = 0;
};

class AmSimple : public Ammo
{
private:
	double ValueOfInitialVelocity(void)override { return 100.0; }

	void OnInit(void)override;
	void OnUpdate(const Informer& informer)override;
	void OnDraw(const Point& pos)const override;
};