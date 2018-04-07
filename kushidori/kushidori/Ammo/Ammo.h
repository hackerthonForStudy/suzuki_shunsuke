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
	bool z_flagVanish = false;

private:
	Coord z_pos;

public:
	virtual ~Ammo(void);

	void Initialize(const Point& pos, const Point& dir);
	void Update(const Informer& informer);
	void Draw(const Point& base);
	virtual bool ShouldBeVanished(const Rect& area)const;

	virtual int GetCost(void)const = 0;

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
public:

	int GetCost(void)const override { return 50; }

private:
	double ValueOfInitialVelocity(void)override { return 100.0; }

	void OnInit(void)override;
	void OnUpdate(const Informer& informer)override;
	void OnDraw(const Point& pos)const override;
};

class AmSpeed : public Ammo
{
private:
	int z_level = 0;

public:
	AmSpeed(int level) :z_level(level) {}

	int GetCost(void)const override { return 50; }

private:
	double ValueOfInitialVelocity(void)override;

	void OnInit(void)override;
	void OnUpdate(const Informer& informer)override;
	void OnDraw(const Point& pos)const override;
};

class AmExplode : public Ammo
{
private:
	int z_level = 0;
	bool z_isExploding = false;
	int z_explodingCount = 0;

public:
	AmExplode(int level) :z_level(level) {}

	int GetCost(void)const override { return 90; }

private:
	double ValueOfInitialVelocity(void)override { return 100.0; };

	void OnInit(void)override;
	void OnUpdate(const Informer& informer)override;
	void OnDraw(const Point& pos)const override;

	double ExplodeRadius(void)const;
};